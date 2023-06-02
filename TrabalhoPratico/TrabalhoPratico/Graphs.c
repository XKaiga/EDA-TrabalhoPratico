/*****************************************************************//**
 * \file   Graphs.c
 * \brief  Graph's Functions
 * 
 * \author Helder
 * \date   June 2023
 *********************************************************************/
#include "Headers.h"

#pragma region Save&Load
/**
 * \brief Loads graph data from a .txt file.
 *
 * \param pGraph Pointer to the graph.
 * \return True if data was loaded successfully, false otherwise.
 */
bool loadTxtGraphData(pLocalList* pGraph) {
	FILE* fp;

	fp = fopen(DATABASEFOLDERGRAPHTXT, "r"); //open file to read in txt

	//check if file was successfully opened
	if (fp == NULL)
		return false;

	int localCod = -1;
	int cod;
	char name[N];
	//read the data from the file into the struct
	while (fscanf(fp, "%d;%[^\n]", &cod, name) == 2)
	{
		//Is number?
		int distance = atoi(name);
		if (distance != 0 || name[0] == '0')
		{
			char* localName = findLocalNameByCod(*pGraph, localCod);
			if (strcmp(localName, "") == 0 || localCod == -1) {
				fclose(fp);
				return false;
			}
			//create adjacent local
			insertNewAdjLocalByCod(*pGraph, localName, cod, distance);
		}
		else
		{
			insertNewLocal(pGraph, cod, name);
			localCod = cod;
		}
	}
	fclose(fp);
	if (localCod == -1)
		return false;
	return true;
}

/**
 * \brief Loads all locals data from a .bin file.
 *
 * \param pGraph Pointer to the graph.
 * \return True if data was loaded successfully, false otherwise.
 */
bool loadBinLocalsData(pLocalList* pGraph) {
	FILE* fp;

	fp = fopen(DATABASEFOLDERLOCALBIN, "rb"); //open file to read in binary

	//check if file was successfully opened
	if (fp == NULL)
		return false;

	bool done = false;
	local newLocal;
	//read the data from the file into the struct
	while (fread(&newLocal, sizeof(local), 1, fp) == 1)
	{
		bool successful = insertNewLocal(pGraph, newLocal.cod, newLocal.name);
		if (!successful)
			return false;
		done = true;
	}
	fclose(fp);

	return done;
}

/**
 * \brief Loads all adjacent locals data from a .bin file.
 *
 * \param pGraph Pointer to the graph.
 * \return True if data was loaded successfully, false otherwise.
 */
bool loadBinAdjLocalsData(pLocalList* pGraph) {
	FILE* fp;

	fp = fopen(DATABASEFOLDERADJLOCALBIN, "rb"); //open file to read in binary

	//check if file was successfully opened
	if (fp == NULL)
		return false;

	bool done = false;
	//read the data from the file into the struct
	adjLocalFile newAdjLocalFile;
	while (fread(&newAdjLocalFile, sizeof(adjLocalFile), 1, fp) == 1)
	{
		char* localName = findLocalNameByCod(*pGraph, newAdjLocalFile.codLocal);
		if (strcmp(localName, "") == 0) {
			fclose(fp);
			return false;
		}

		//create adjacent local
		bool successful = insertNewAdjLocalByCod(*pGraph, localName, newAdjLocalFile.codAdj, newAdjLocalFile.distance);
		if (!successful)
			return false;
		done = true;
	}
	fclose(fp);

	return done;
}

/**
 * \brief Saves the locals data from the graph to a .bin file.
 *
 * \param graph Pointer to the graph data structure.
 * \return -2 if graph == null, or -1 if gives error when opening file, or 0 if data was successfully saved.
 */
int saveLocals(localList* graph) {
	//check if list is empty
	if (graph == NULL)
		return -2;

	FILE* fp = fopen(DATABASEFOLDERLOCALBIN, "wb"); //open file to write in binary

	//check if file was successfully opened
	if (fp == NULL)
		return -1;

	localList* aux = graph;
	do
	{
		//write the contents of the current node to the file
		fwrite(&(aux->l), sizeof(local), 1, fp);
		aux = aux->next;
	} while (aux != graph);

	fclose(fp);
	return 0;
}

/**
 * \brief Saves the adjacent locals data from the graph to a .bin file.
 *
 * \param graph Pointer to the graph data structure.
 * \return -2 if graph == null, or -1 if gives error when opening file, or 0 if data was successfully saved.
 */
int saveAdjLocals(localList* graph) {
	//check if list is empty
	if (graph == NULL)
		return -2;

	FILE* fp = fopen(DATABASEFOLDERADJLOCALBIN, "wb"); //open file to write in binary

	//check if file was successfully opened
	if (fp == NULL)
		return -1;

	localList* aux = graph;
	do
	{
		adjLocalList* aux2 = aux->adjLocals;
		while (aux2)
		{
			adjLocalFile AdjLocalFile;
			AdjLocalFile.codLocal = aux->l.cod;
			AdjLocalFile.codAdj = aux2->adjL.cod;
			AdjLocalFile.distance = aux2->adjL.distance;
			//write the contents of the current node to the file
			fwrite(&AdjLocalFile, sizeof(adjLocalFile), 1, fp);
			aux2 = aux2->next;
		}
		aux = aux->next;
	} while (aux != graph);

	fclose(fp);
	return 0;
}

#pragma region Graph
/**
 * \brief Loads all graph data from a .bin file.
 *
 * \param pGraph Pointer to the graph.
 * \return True if data was loaded successfully, false otherwise.
 */
bool loadBinGraphData(pLocalList* pGraph) {
	FILE* fp;

	fp = fopen(DATABASEFOLDERGRAPHBIN, "rb"); //open file to read in binary

	//check if file was successfully opened
	if (fp == NULL)
		return false;

	int num = 0;
	local newLocal;
	int numOfAdjs;
	adjLocal newAdjLocal;
	//read the data from the file into the struct
	while (fread(&newLocal, sizeof(local), 1, fp) == 1 && fread(&numOfAdjs, sizeof(int), 1, fp) == 1)
	{
		insertNewLocal(pGraph, newLocal.cod, newLocal.name);
		num++;
		for (int i = 0; i < numOfAdjs; i++)
		{
			if (fread(&newAdjLocal, sizeof(adjLocal), 1, fp) != 1)
				return false;
			char* localName = findLocalNameByCod(*pGraph, num - 1);
			if (strcmp(localName, "") == 0 || num == 0) {
				fclose(fp);
				return false;
			}

			//create adjacent local
			insertNewAdjLocalByCod(*pGraph, localName, newAdjLocal.cod, newAdjLocal.distance);
		}
	}
	fclose(fp);
	if (num == 0)
		return false;
	return true;
}

/**
 * \brief Saves all graph data to a .bin file.
 *
 * \param graph Pointer to the graph data structure.
 * \return -2 if graph == null, or -1 if gives error when opening file, or 0 if data was successfully saved.
 */
int saveGraph(localList* graph) {
	//check if list is empty
	if (graph == NULL)
		return -2;

	FILE* fp = fopen(DATABASEFOLDERGRAPHBIN, "wb"); //open file to write in binary

	//check if file was successfully opened
	if (fp == NULL)
		return -1;

	localList* aux = graph;
	do
	{
		//write the contents of the current node to the file
		fwrite(&(aux->l), sizeof(local), 1, fp);
		adjLocalList* aux2 = aux->adjLocals;

		int numOfAdjs = countAdjLocals(aux2);
		fwrite(&numOfAdjs, sizeof(int), 1, fp);
		while (aux2)
		{
			//write the contents of the current node to the file
			fwrite(&aux2->adjL, sizeof(adjLocal), 1, fp);
			aux2 = aux2->next;
		}
		aux = aux->next;
	} while (aux != graph);

	fclose(fp);
	return 0;
}

#pragma endregion

#pragma endregion


#pragma region Path
/**
 * \brief Display the path with its total distance and the price to pay.
 *
 * \param path The path to be displayed.
 * \param kms A pointer to the total distance of the path, and hepls calculate the price.
 * \return True if successful, false otherwise.
 */
bool showPath(localList* path, int* kms) {
	if (path == NULL)
		return false;

	printf("\n Path: %dKms - %d$\n", *kms, *kms * PRICEPERKM);
	localList* aux = path;
	do
	{
		if (aux->next != path)
			printf("   %s   ->", aux->l.name);
		else
			printf("   %s", aux->l.name);
		aux = aux->next;
	} while (aux != path);
	return true;
}

/**
 * \brief Find the shortest path between two locations in the graph.
 *
 * \param graph The graph.
 * \param nameOrigin The name of the origin location.
 * \param nameDest The name of the destination location.
 * \param kms Array to store the fastest distance [0] and updated distance [1] of the path.
 * \param path Pointer to store the shortest path.
 * \return True if successful, false otherwise.
 */
bool findShortestPath(localList* graph, char* nameOrigin, char* nameDest, int kms[2], localList** path) {
	if (graph == NULL) {
		resetVisitedLocals(graph);
		return false;
	}

	bool finded = false;
	localList* aux = graph;
	do
	{
		if (strcmp(aux->l.name, nameOrigin) == 0) {
			finded = true;
			break;
		}
		aux = aux->next;
	} while (aux != graph);

	if (!finded) {
		resetVisitedLocals(graph);
		return false;
	}

	insertNewLocal(&path[1], aux->l.cod, aux->l.name);

	if (strcmp(nameOrigin, nameDest) == 0) {
		if (kms[0] == 0 || kms[1] < kms[0]) {
			kms[0] = kms[1];
			bool copied = localListCopy(path[0], path[1]);
			if (!copied)
			{
				resetVisitedLocals(graph);
				return false;
			}
		}
		return true;
	}

	aux->visited = true;

	adjLocalList* auxAdjs = aux->adjLocals;
	while (auxAdjs)
	{
		localList* local = findLocalByCod(graph, auxAdjs->adjL.cod);
		if (local == NULL) {
			resetVisitedLocals(graph);
			return false;
		}

		if (!local->visited) {
			kms[1] += auxAdjs->adjL.distance;
			if (!findShortestPath(graph, local->l.name, nameDest, kms, path))
				return false;
			kms[1] -= auxAdjs->adjL.distance;
			bool removed = removeLastLocalList(&path[1]);
			if (!removed)
			{
				resetVisitedLocals(graph);
				return false;
			}
			local->visited = false;
		}
		auxAdjs = auxAdjs->next;
	}
	if (kms[1] == 0)
		resetVisitedLocals(graph);
	return true;
}

/**
 * \brief Count the number of paths between two locations in the graph.
 *
 * \param graph The graph.
 * \param nameOrigin The name of the origin location.
 * \param nameDest The name of the destination location.
 * \param pCountPaths Pointer to store the count of paths.
 * \return True if successful, false otherwise.
 */
bool countPaths(localList* graph, char* nameOrigin, char* nameDest, int* pCountPaths) {
	if (graph == NULL) {
		resetVisitedLocals(graph);
		return false;
	}

	bool finded = false;
	localList* aux = graph;
	do
	{
		if (strcmp(aux->l.name, nameOrigin) == 0) {
			finded = true;
			break;
		}
		aux = aux->next;
	} while (aux != graph);

	if (!finded) {
		resetVisitedLocals(graph);
		return false;
	}

	if (strcmp(nameOrigin, nameDest) == 0) {
		(*pCountPaths)++;
		return true;
	}

	aux->visited = true;

	adjLocalList* auxAdjs = aux->adjLocals;
	while (auxAdjs)
	{
		localList* local = findLocalByCod(graph, auxAdjs->adjL.cod);
		if (local == NULL) {
			resetVisitedLocals(graph);
			return false;
		}

		if (!local->visited && !countPaths(graph, local->l.name, nameDest, pCountPaths))
			return false;
		local->visited = false;
		auxAdjs = auxAdjs->next;
	}
	return true;
}

/**
 * \brief Reset the visited variable of all locals in the graph.
 *
 * \param graph The graph.
 * \return True if successful, false otherwise.
 */
bool resetVisitedLocals(localList* graph) {
	if (graph == NULL)
		return false;

	localList* aux = graph;
	do
	{
		aux->visited = false;
		aux = aux->next;
	} while (aux != graph);
	return true;
}

#pragma endregion


#pragma region Traveling Salesman
/**
 * \brief Find the closest vehicle with batery below 50% from a given origin location.
 *
 * \param VehicleList Pointer to the list of vehicles with batery below 50% from the origin location.
 * \param capacity The available capacity for picking up vehicles.
 * \param graph The graph.
 * \param nameOrigin The name of the origin location.
 * \return True if successful, false otherwise.
 */
bool TS_GrabCar(pVehicleList* VehiclesBelow50, int* capacity, localList* graph, char* nameOrigin) {
	//find the closest vehicle
	int fastestPathKms = 0;
	localList* fastestPath = NULL; //path to go to the closest vehicle
	int vehicleFindedCod = -1;
	bool shortestPathExecuted = false;
	vehicleList* auxPath = *VehiclesBelow50;
	while (auxPath)
	{
		int kms[2] = { 0,0 };
		localList* path = NULL;
		shortestPathExecuted = findShortestPath(graph, nameOrigin, auxPath->v.location, kms, (localList* [2]) { &path, NULL });
		if (!shortestPathExecuted)
			return false;

		//exists a path to it?
		if (path != NULL)
		{
			vehicle vei;
			bool findedVeh = findVehicle(*VehiclesBelow50, auxPath->v.cod, &vei);
			if (!findedVeh)
				return false;
			//has space to take vehicle?
			int aux = (strcmp(vei.type, "Eletrico") == 0) ? 2 : 1;
			if (*capacity - aux >= 0)
			{
				if (fastestPathKms == 0 || kms[0] < fastestPathKms)
				{
					bool copySucceded = localListCopy(&fastestPath, path);
					if (!copySucceded)
						return false;
					fastestPathKms = kms[0];
					vehicleFindedCod = auxPath->v.cod;
					if (kms[0] == 0)
						break;
				}
			}
			//if has only space for Combustivel Vehicles verifies if exists Combustivel Vehicles
			else if (findHowManyVehiclesWithType(*VehiclesBelow50, "Combustivel") == 0)
			{
				*capacity = 0;
				return true;
			}
			auxPath = auxPath->next;
		}
		//if it's impossible to reach remove from list
		else
		{
			int tempCod = auxPath->v.cod;
			auxPath = auxPath->next;
			bool removed = removeVehicleFromVehicleList(VehiclesBelow50, tempCod);
			if (!removed)
				return false;
		}
	}

	bool showed = showPath(fastestPath, &fastestPathKms);
	if (!showed)
		return false;

	vehicle vei;
	bool findedVeh = findVehicle(*VehiclesBelow50, vehicleFindedCod, &vei);
	if (!findedVeh)
		return false;

	//updating truck position
	vehicleList* vehiclesInLocal = NULL;
	bool findedVehiclesInLocal = false;
	localList* lastLocal = NULL;
	if (fastestPath->previous != NULL)
	{
		lastLocal = fastestPath->previous;
		strcpy(nameOrigin, lastLocal->l.name);

		findedVehiclesInLocal = findVehiclesInLocal(*VehiclesBelow50, lastLocal->l.name, &vehiclesInLocal, false, "");
	}
	else
		findedVehiclesInLocal = findVehiclesInLocal(*VehiclesBelow50, fastestPath->l.name, &vehiclesInLocal, false, "");

	//quando chega em um local, verifica quantos veiculos tem e pega o maximo que consegue ou até acabar
	if (!findedVehiclesInLocal)
		return false;

	vehicleList* auxVehiclesInLocal = vehiclesInLocal;
	while (auxVehiclesInLocal)
	{
		int aux = (strcmp(auxVehiclesInLocal->v.type, "Eletrico") == 0) ? 2 : 1;
		if (*capacity - aux >= 0)
		{
			(*capacity) -= aux;
			bool removed = removeVehicleFromVehicleList(VehiclesBelow50, auxVehiclesInLocal->v.cod);
			if (!removed)
				return false;
		}
		auxVehiclesInLocal = auxVehiclesInLocal->next;
	}

	//se estiver no mesmo sitio que começou reinicia a capacidade
	if (lastLocal == NULL)
		*capacity = 0;

	return true;
}

/**
 * \brief Find the shortest path for traveling salesman problem.
 *
 * \param VehicleList Pointer to a list of all available vehicles.
 * \param capacity Initial available capacity for picking up vehicles.
 * \param graph The graph.
 * \param nameOrigin The name of the origin location.
 * \return True if successful, false otherwise.
 */
bool travelingSalesman(vehicleList* VehicleList, int capacity, localList* graph, char* nameOrigin) {
	if (VehicleList == NULL || graph == NULL || capacity < 1 || strcmp(nameOrigin, "") == 0)
		return false;

	vehicleList* VehiclesBelow50;
	bool finded = findVehiclesBelow50(VehicleList, &VehiclesBelow50);
	if (!finded)
		return false;

	int inicialCapacity = capacity;
	char originalOriginLocalName[N];
	strcpy(originalOriginLocalName, nameOrigin);

	do
	{
		if (!TS_GrabCar(&VehiclesBelow50, &capacity, graph, nameOrigin))
			return false;

		if (capacity == 0 || strcmp(nameOrigin, originalOriginLocalName) == 0) {
			capacity = inicialCapacity;
			strcpy(nameOrigin, originalOriginLocalName);
		}

	} while (VehiclesBelow50 != NULL);

	return true;
}

#pragma endregion



#pragma region LocalListFunctions
/**
 * \brief Copies the localList pointed by source to the destination.
 *
 * \param dest Pointer to the destination localList.
 * \param sour Pointer to the source localList.
 * \return True if successful, false otherwise.
 */
bool localListCopy(pLocalList* dest, localList* sour) {
	if (sour == NULL)
		return false;

	*dest = NULL;
	localList* aux = sour;
	do
	{
		insertNewLocal(dest, aux->l.cod, aux->l.name);
		aux = aux->next;
	} while (aux != sour);

	return true;
}

/**
 * \brief Remove the last localList from a local list.
 *
 * \param pLocalList Pointer to a local list.
 * \return True if successful, false otherwise.
 */
bool removeLastLocalList(pLocalList* pLocalList) {
	if (*pLocalList == NULL)
		return false;

	localList* aux = (*pLocalList)->previous;
	localList* aux2 = aux->previous;

	(*pLocalList)->previous = aux2;
	aux2->next = *pLocalList;
	free(aux);

	return true;
}

/**
 * \brief Count the number of adjacent locals in a adjacency list.
 *
 * \param adjList The adjacency list.
 * \return The count of adjacent locals.
 */
int countAdjLocals(adjLocalList* adjList) {
	int numOfAdjs = 0;

	adjLocalList* aux = adjList;
	while (aux)
	{
		numOfAdjs++;
		aux = aux->next;
	}
	return numOfAdjs;
}

#pragma endregion

#pragma region LocalsFunctions
/**
 * \brief Create a new local with the given code and name.
 *
 * \param cod The code of the local.
 * \param name The name of the local.
 * \return The created local.
 */
local newLocal(int cod, char* name) {
	local newlocal;
	strcpy(newlocal.name, name);
	newlocal.cod = cod;
	return newlocal;
}

/**
 * \brief Insert a new local into the graph with the given code and name.
 *
 * \param graph Pointer to the graph.
 * \param cod The code of the local.
 * \param name The name of the local.
 * \return True if successful, false otherwise.
 */
bool insertNewLocal(pLocalList* graph, int cod, char* name) {
	if (*graph == NULL) {
		*graph = (localList*)malloc(sizeof(localList));
		if (*graph == NULL)
			return false;
		(*graph)->l = newLocal(cod, name);
		(*graph)->visited = false;
		(*graph)->adjLocals = NULL;
		(*graph)->previous = NULL;
		(*graph)->next = *graph;
		return true;
	}

	localList* aux = *graph;
	while (aux->next != *graph)
		aux = aux->next;

	aux->next = (localList*)malloc(sizeof(localList));
	if (aux->next == NULL)
		return false;
	localList* aux2 = aux;
	aux = aux->next;
	aux->l = newLocal(cod, name);
	aux->visited = false;
	aux->adjLocals = NULL;
	aux->previous = aux2;
	aux->next = *graph;
	(*graph)->previous = aux;
	return true;
}

#pragma endregion

#pragma region AdjLocalsFunctions
/**
 * \brief Create a new adjacent local with the given code and distance.
 *
 * \param cod The code of the adjacent local.
 * \param dist The distance to the adjacent local.
 * \return Pointer to the created adjacent local.
 */
adjLocalList* newAdjLocal(int cod, int dist) {
	adjLocalList* adjL = (adjLocalList*)malloc(sizeof(adjLocalList));
	if (adjL == NULL)
		return NULL;

	adjL->adjL.cod = cod;
	adjL->adjL.distance = dist;
	return adjL;
}

/**
 * \brief Insert a new adjacent local into a local in the graph by name.
 *
 * \param graph Pointer to the graph.
 * \param localName The name of a local to insert the adjacent local into.
 * \param adjName The name of the adjacent local.
 * \param dist The distance to the adjacent local.
 * \return True if successful, false otherwise.
 */
bool insertNewAdjLocalByName(localList* graph, char* localName, char* adjName, int dist) {
#pragma region Validations

	if (graph == NULL)
		return false;

	localList* local = findLocalByName(graph, localName);
	if (local == NULL)
		return false;

	int adjCod = findLocalCodByName(graph, adjName);
	if (adjCod == -1)
		return false;

#pragma endregion

	return insertNewAdjLocal(&local->adjLocals, adjCod, dist);
}

/**
 * \brief Insert a new adjacent local into a local in the graph by code.
 *
 * \param graph Pointer to the graph.
 * \param localName The name of a local to insert the adjacent local into.
 * \param adjCod The code of the adjacent local.
 * \param dist The distance to the adjacent local.
 * \return True if successful, false otherwise.
 */
bool insertNewAdjLocalByCod(localList* graph, char* localName, int adjCod, int dist) {
#pragma region Validations

	if (graph == NULL)
		return false;

	localList* local = findLocalByName(graph, localName);
	if (local == NULL)
		return false;

#pragma endregion

	return insertNewAdjLocal(&local->adjLocals, adjCod, dist);
}

/**
 * \brief Insert a new adjacent local into a adjacency list.
 *
 * \param adjLocals Pointer to the adjacency list.
 * \param adjCod The code of the adjacent local.
 * \param dist The distance to the adjacent local.
 * \return True if successful, false otherwise.
 */
bool insertNewAdjLocal(pAdjLocalList* adjLocals, int adjCod, int dist) {
	adjLocalList* newAdj = newAdjLocal(adjCod, dist);
	if (newAdj == NULL)
		return false;


	newAdj->next = *adjLocals;
	*adjLocals = newAdj;
	return true;
}

#pragma endregion



#pragma region FindFunctions
/**
 * \brief Find a local in the graph by code.
 *
 * \param graph Pointer to the graph.
 * \param cod The code of the local to find.
 * \return Pointer to the found local, or NULL if not found.
 */
localList* findLocalByCod(localList* graph, int cod) {
	if (graph == NULL)
		return NULL;

	localList* aux = graph;
	do
	{
		if (aux->l.cod == cod)
			return aux;
		aux = aux->next;
	} while (aux != graph);
	return NULL;
}

/**
 * \brief Find a local in the graph by name.
 *
 * \param graph Pointer to the graph.
 * \param name The name of the local to find.
 * \return Pointer to the found local, or NULL if not found.
 */
localList* findLocalByName(localList* graph, char* name) {
	if (graph == NULL)
		return NULL;

	localList* aux = graph;
	do
	{
		if (strcmp(aux->l.name, name) == 0)
			return aux;
		aux = aux->next;
	} while (aux != graph);
	return NULL;
}

/**
 * \brief Find the code of a local in the graph by name.
 *
 * \param graph Pointer to the graph.
 * \param name The name of the local to find.
 * \return The code of the found local, or -1 if not found.
 */
int findLocalCodByName(localList* graph, char* name) {
	if (graph == NULL)
		return -1;

	localList* aux = graph;
	do
	{
		if (strcmp(aux->l.name, name) == 0)
			return aux->l.cod;
		aux = aux->next;
	} while (aux != graph);
	return -1;
}

/**
 * \brief Find the name of a local in the graph by code.
 *
 * \param graph Pointer to the graph.
 * \param cod The code of the local to find.
 * \return The name of the found local, or "" if not found.
 */
char* findLocalNameByCod(localList* graph, int cod) {
	if (graph == NULL)
		return "";

	localList* aux = graph;
	do
	{
		if (aux->l.cod == cod)
			return aux->l.name;
		aux = aux->next;
	} while (aux != graph);
	return "";
}

#pragma endregion


#pragma region ShowFunctions
/**
 * \brief Show the graph, printing it.
 *
 * \param graph Pointer to the graph.
 * \return True if successful, false otherwise.
 */
bool showGraph(localList* graph) {
	if (graph == NULL)
		return false;
	printf("\n\tGraph:");
	showLocalsAndAdjs(graph);
	printf("\n");
	return true;
}

/**
 * \brief Show the list of locals and their adjacent locals.
 *
 * \param graph Pointer to the graph.
 * \return True if successful, false otherwise.
 */
bool showLocalsAndAdjs(localList* graph) {
	if (graph == NULL)
		return false;

	localList* aux = graph;
	do
	{
		printf("\n\n%s", aux->l.name);
		showAdjs(aux->adjLocals);
		aux = aux->next;
	} while (aux != graph);

	return true;
}

/**
 * \brief Show the adjacent locals of a local.
 *
 * \param adjLocals Pointer to the adjacency list.
 * \return True if successful, false otherwise.
 */
bool showAdjs(adjLocalList* adjLocals) {
	while (adjLocals)
	{
		printf("\n%d - %dKm", adjLocals->adjL.cod, adjLocals->adjL.distance);
		adjLocals = adjLocals->next;
	}
	return true;
}

#pragma endregion
