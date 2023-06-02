/*****************************************************************//**
 * \file   Vehicle.c
 * \brief  Vehicle's Functions
 * 
 * \author Helder
 * \date   June 2023
 *********************************************************************/
#include "Headers.h"

#pragma region Save&Load

//loads data from a txt file into a list
int loadTxtVehicleData(pVehicleList* pVehicleList) {
	FILE* fp;

	fp = fopen(DATABASEFOLDERVEHICLETXT, "r"); //open file to read in txt

	//check if file was successfully opened
	if (fp == NULL)
		return -1;

	vehicleList* aux = NULL;
	while (true) {
		vehicleList* vehicles = (vehicleList*)malloc(sizeof(vehicleList));
		if (vehicles == NULL)
			return -2;

		//read the data from the file into the struct
		if (fscanf(fp, "%d;%[^;];%[^;];%[^;];%d;%d;%d", &vehicles->v.cod, vehicles->v.brand, vehicles->v.type, vehicles->v.location, &vehicles->v.batery, &vehicles->v.price, &vehicles->v.years) != 7)
		{
			free(vehicles);
			fclose(fp);
			//check if there's an error reading the file
			if (aux == NULL)
				return -3;
			else
				return 0;
		}
		//if the list is empty, set the new node as the head of the list
		if (aux == NULL)
		{
			*pVehicleList = vehicles;
			aux = vehicles;
		}
		//else append the new node to the end of the list
		else
		{
			aux->next = vehicles;
			vehicles->previous = aux;
			aux = aux->next;
		}
		//make the list circular
		(*pVehicleList)->previous = vehicles;
		vehicles->next = *pVehicleList;
	}
}

//loads data from a binary file into a list
int loadBinVehicleData(pVehicleList* pVehicleList) {
	FILE* fp;

	fp = fopen(DATABASEFOLDERVEHICLEBIN, "rb"); //open file to read in binary

	//check if file was successfully opened
	if (fp == NULL)
		return -1;

	vehicleList* aux = NULL;
	while (true) {
		vehicleList* vehicles = (vehicleList*)malloc(sizeof(vehicleList));
		if (vehicles == NULL)
			return -2;

		//read the data from the file into the current node
		fread(&vehicles->v, sizeof(vehicle), 1, fp);
		if (vehicles == NULL || feof(fp))
		{
			free(vehicles);
			fclose(fp);
			//check if there's an error reading the file
			if (aux == NULL)
				return -3;
			else
				return 0;
		}
		//if the list is empty, set the new node as the head of the list
		if (aux == NULL)
		{
			*pVehicleList = vehicles;
			aux = vehicles;
		}
		//else append the new node to the end of the list
		else
		{
			aux->next = vehicles;
			vehicles->previous = aux;
			aux = aux->next;
		}
		//make the list circular
		(*pVehicleList)->previous = vehicles;
		vehicles->next = *pVehicleList;
	}
}

//saves data from a bin file into a list
int saveVehicles(vehicleList* VehicleList) {
	FILE* fp;

	fp = fopen(DATABASEFOLDERVEHICLEBIN, "wb"); //open file to write in binary

	//check if file was successfully opened
	if (fp == NULL)
		return -1;

	vehicleList* aux = VehicleList;

	//check if list is empty
	if (aux == NULL)
		return -2;

	do
	{
		//write the contents of the current node to the file
		fwrite(&aux->v, sizeof(vehicle), 1, fp);
		aux = aux->next;
	} while (aux != VehicleList);

	fclose(fp);
	return 0;
}

#pragma endregion


#pragma region VehiclesFunctions
vehicleList* createNewVehicle(int c, char typ[], int bat, int pri, int ys, char local[], char bran[]) {
	//allocate memory
	vehicleList* v = (vehicleList*)malloc(sizeof(vehicleList));
	if (v == NULL)
		return NULL;
	v->v.cod = c;
	strcpy(v->v.type, typ);
	strcpy(v->v.location, local);
	strcpy(v->v.brand, bran);
	v->v.batery = bat;
	v->v.price = pri;
	v->v.years = ys;
	v->next = NULL;
	v->previous = NULL;
	return v;
}

int insertVehicle(pVehicleList* pVehicleList, vehicle v, bool listCircular) {
	vehicleList* vehicle = (vehicleList*)malloc(sizeof(vehicleList));
	if (vehicle == NULL)
		return NULL;

	vehicle->v = v;

	return insertVehicleList(pVehicleList, vehicle, listCircular);
}
//insert a vehicle into the list
int insertVehicleList(pVehicleList* pVehicleList, vehicleList* v, bool listCircular) {
	//start at the head of the list
	vehicleList* aux = *pVehicleList;

	//if list is empty, insert as the head of the list
	if (*pVehicleList == NULL)
		*pVehicleList = v;
	else
	{
		if ((*pVehicleList)->v.cod == v->v.cod)
			return -4;

		while (aux->next != NULL && aux->next != *pVehicleList)
		{
			//if already exists, return false
			if (aux->v.cod == v->v.cod)
				return -4;
			aux = aux->next;
		}

		//insert after the last node of the list
		aux->next = v;
		v->previous = aux;
	}
	if (listCircular)
	{
		//make the list circular
		v->next = *pVehicleList;
		(*pVehicleList)->previous = v;
	}
	else
		v->next = NULL;

	return 0;
}

//remove a vehicle from the list
int removeVehicle(pVehicleList* pVehicleList, int c) {
	//start at the head of the list
	vehicleList* aux = *pVehicleList;
	vehicleList* aux2;

	//check if the list is empty
	if (aux == NULL)
		return -2;

	//search the list to find the node to be removed
	while (aux->v.cod != c)
	{
		aux = aux->next;
		//the node was not found
		if (aux == *pVehicleList)
			return -5;
	}

	//if the node to be deleted is the head of the list
	if (aux == *pVehicleList)
		//if the list only has one node
		if ((*pVehicleList)->next == *pVehicleList)
		{
			//deallocate memory for the list
			free(*pVehicleList);
			//set the pointer to the list to NULL
			*pVehicleList = NULL;
		}
		else
			//move head to the next node
			*pVehicleList = (*pVehicleList)->next;

	//uptade the links of the nods
	aux2 = aux->previous;
	aux2->next = aux->next;
	aux2 = aux->next;
	aux2->previous = aux->previous;

	//deallocate memory
	free(aux);
	return 0;
}

//chance a vehicle from the list
int chanceVehicle(pVehicleList* pVehicleList, int cF, int c, char typ[], int bat, int pri, int ys, char local[], char bran[]) {
	//start at the head of the list
	vehicleList* aux = *pVehicleList;
	vehicleList* aux2;

	//check if the list is empty
	if (aux == NULL)
		return -2;

	//search the list to find the node to be chanced
	while (aux->v.cod != cF)
	{
		aux = aux->next;
		//the node was not found
		if (aux == *pVehicleList)
			return -5;
	}

	aux->v.cod = c;
	strcpy(aux->v.type, typ);
	strcpy(aux->v.location, local);
	strcpy(aux->v.brand, bran);
	aux->v.batery = bat;
	aux->v.price = pri;
	aux->v.years = ys;

	//deallocate memory
	return 0;
}

//order vehicles by descending order
int vehiclesDescendingOrder(pVehicleList* VehicleList) {
	vehicleList* aux = *VehicleList;
	vehicleList* aux2;

	if ((*VehicleList)->next != NULL)
		aux2 = (*VehicleList)->next;
	else
		return 0;

	bool end = false;
	do
	{
		end = false;
		vehicle temp;
		while (aux2 != *VehicleList)
		{
			if (aux->v.batery < aux2->v.batery)
			{
				temp = aux->v;
				aux->v = aux2->v;
				aux2->v = temp;
				end = true;
			}
			aux2 = aux2->next;
		}
		aux = aux->next;
		aux2 = aux->next;
	} while (end && aux2 != VehicleList);
	return 0;
}

//returns a list with only the vehicls from a given location
int vehiclesFromLocal(vehicleList* VehicleList, char local[], vehicleList** out) {
	vehicleList* aux = VehicleList;
	vehicleList* LocalList = NULL;
	vehicleList* aux2 = NULL;

	if (aux == NULL)
		return -2;
	do
	{
		if (strcmp(aux->v.location, local) == 0)
		{
			vehicleList* node = (struct vehicleList*)malloc(sizeof(vehicleList));
			if (node == NULL)
				return -2;
			node->v = aux->v;
			node->previous = aux2;
			if (LocalList != NULL)
				aux2->next = node;
			else
				LocalList = node;
			aux2 = node;
			node->next = LocalList;
			LocalList->previous = node;
		}
		aux = aux->next;
	} while (aux != VehicleList);
	*out = LocalList;
}

/**
 * finds a vehicle based on the code.
 *
 * \param VehicleList: List of Vehicles
 * \param c: code of the Vehicle
 * \param outVehicle: address of vehicle to return
 * \return true if finded
 */
bool findVehicle(vehicleList* VehicleList, int c, vehicle* outVehicle) {
	//start at the head of the list
	vehicleList* aux = VehicleList;

	while (aux)
	{
		//if exists, return true
		if (aux->v.cod == c) {
			*outVehicle = aux->v;
			return true;
		}
		aux = aux->next;
	}

	return false;
}

/**
 * finds a vehicle in a circular list based on the code.
 *
 * \param VehicleList: List of Vehicles
 * \param c: code of the Vehicle
 * \param outVehicle: address of vehicle to return
 * \return true if finded
 */
bool findVehicleCircularList(vehicleList* VehicleList, int c, vehicle* outVehicle) {
	//start at the head of the list
	vehicleList* aux = VehicleList;

	if (aux == NULL)
		return false;

	do
	{
		//if exists, return true
		if (aux->v.cod == c) {
			*outVehicle = aux->v;
			return true;
		}
		aux = aux->next;
	} while (aux != VehicleList);

	return false;
}

/**
 * \brief Find the number of vehicles with a specific type.
 *
 * \param VehiclesList Pointer to a vehicle list.
 * \param type The type of vehicle to search for.
 * \return The count of vehicles with the specified type.
 */
int findHowManyVehiclesWithType(vehicleList* VehiclesList, char* type) {
	int numVehiclesOfType = 0;

	vehicleList* aux = VehiclesList;
	while (aux)
	{
		if (strcmp(aux->v.type, type) == 0)
			numVehiclesOfType++;
		aux = aux->next;
	}

	return numVehiclesOfType;
}

/**
 * \brief Remove a vehicle from a vehicle list.
 *
 * \param VehicleList Pointer to a vehicle list.
 * \param cod The code of the vehicle to be removed.
 * \return True if successful, false otherwise.
 */
bool removeVehicleFromVehicleList(pVehicleList* VehicleList, int cod) {
	if (*VehicleList == NULL)
		return false;

	vehicleList* aux = *VehicleList;
	while (aux)
	{
		if (aux->v.cod == cod)
		{
			if (aux == *VehicleList)
				*VehicleList = aux->next;
			else
			{
				vehicleList* auxPrevious = aux->previous;
				auxPrevious->next = aux->next;

				vehicleList* auxNext = aux->next;
				if (auxNext != NULL)
					auxNext->previous = auxPrevious;
			}
			free(aux);
			break;
		}
		aux = aux->next;
	}

	return true;
}

/**
 * \brief Find vehicles with batery below 50%.
 *
 * \param VehicleList Pointer to a vehicle list.
 * \param pFindedVehicles Pointer to store the found vehicles.
 * \return True if successful, false otherwise.
 */
bool findVehiclesBelow50(vehicleList* VehicleList, pVehicleList* pFindedVehicles) {
	if (VehicleList == NULL)
		return false;

	*pFindedVehicles = NULL;

	vehicleList* auxVehicles = VehicleList;
	do
	{
		if (auxVehicles->v.batery < 50)
			insertVehicle(pFindedVehicles, auxVehicles->v, false);
		auxVehicles = auxVehicles->next;
	} while (auxVehicles != VehicleList);

	if (pFindedVehicles == NULL)
		return false;
	return true;
}

#pragma endregion


#pragma region LocalFunctions
/**
 * \brief Find vehicles in a specific local.
 *
 * \param VehicleList Pointer to a vehicle list.
 * \param localName The name of the local to search in.
 * \param pFindedVehicles Pointer to store the found vehicles.
 * \param withType Variable indicating whether to filter by vehicle type.
 * \param type The vehicle type to filter by.
 * \return True if successful, false otherwise.
 */
bool findVehiclesInLocal(vehicleList* VehicleList, char* localName, pVehicleList* pFindedVehicles, bool withType, char* type) {
	if (VehicleList == NULL)
		return false;

	vehicleList* auxVehicles = VehicleList;
	while (auxVehicles)
	{
		if (strcmp(auxVehicles->v.location, localName) == 0)
			if (withType) {
				if (strcmp(auxVehicles->v.type, type) == 0)
					insertVehicle(pFindedVehicles, auxVehicles->v, false);
			}
			else
				insertVehicle(pFindedVehicles, auxVehicles->v, false);
		auxVehicles = auxVehicles->next;
	}
	return true;
}

/**
 * \brief Find vehicles in a specific local using a circular list.
 *
 * \param VehicleList Pointer to a vehicle list.
 * \param localName The name of the local to search in.
 * \param pFindedVehicles Pointer to store the found vehicles.
 * \param withType Variable indicating whether to filter by vehicle type.
 * \param type The vehicle type to filter by.
 * \return True if successful, false otherwise.
 */
bool findVehiclesInLocalCircularList(vehicleList* VehicleList, char* localName, pVehicleList* pFindedVehicles, bool withType, char* type) {
	if (VehicleList == NULL)
		return false;

	vehicleList* auxVehicles = VehicleList;
	do
	{
		if (strcmp(auxVehicles->v.location, localName) == 0)
			if (withType) {
				if (strcmp(auxVehicles->v.type, type) == 0)
					insertVehicle(pFindedVehicles, auxVehicles->v, false);
			}
			else
				insertVehicle(pFindedVehicles, auxVehicles->v, false);
		auxVehicles = auxVehicles->next;
	} while (auxVehicles != VehicleList);
	return true;
}

/**
 * \brief Find vehicles within a given radius of a specific local in the graph.
 *
 * \param graph The graph.
 * \param VehicleList Pointer to the vehicle list.
 * \param nameOrigin The name of the origin location.
 * \param radius The radius in kilometers.
 * \param pFindedVehicles Pointer to store the found vehicles.
 * \param withType Variable indicating whether to filter by vehicle type.
 * \param type The vehicle type to filter by.
 * \return True if successful, false otherwise.
 */
bool findVehiclesInRadius(localList* graph, vehicleList* VehicleList, char* nameOrigin, int radius, pVehicleList* pFindedVehicles, bool withType, char* type) {
	if (graph == NULL || VehicleList == NULL)
		return false;

	localList* aux = graph;
	do
	{
		if (strcmp(aux->l.name, nameOrigin) == 0)
			break;
		aux = aux->next;
	} while (aux != graph);

	findVehiclesInLocalCircularList(VehicleList, aux->l.name, pFindedVehicles, withType, type);
	aux->visited = true;

	adjLocalList* auxAdjs = aux->adjLocals;
	while (auxAdjs)
	{
		if (auxAdjs->adjL.distance <= radius)
		{
			localList* local = findLocalByCod(graph, auxAdjs->adjL.cod);
			if (local == NULL)
				return false;

			if (!local->visited && auxAdjs->adjL.distance < radius)
				findVehiclesInRadius(graph, VehicleList, local->l.name, radius - auxAdjs->adjL.distance, pFindedVehicles, withType, type);
		}
		auxAdjs = auxAdjs->next;
	}
	return true;
}

#pragma endregion
