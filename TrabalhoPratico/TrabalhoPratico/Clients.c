
#include "Headers.h"

#pragma region Save&Load

//loads data from a txt file into a list
int loadTxtClientData(pClientList* pClientList) {
	FILE* fp;

	fp = fopen(DATABASEFOLDERCLIENTTXT, "r"); //open file to read in txt

	//check if file was successfully opened
	if (fp == NULL)
		return -1;

	clientList* aux = NULL;
	while (true) {
		clientList* clients = (clientList*)malloc(sizeof(clientList));
		if (clients == NULL)
			return -2;

		//read the data from the file into the struct
		if (fscanf(fp, "%d;%d;%[^;];%[^\n]", &clients->c.nif, &clients->c.money, clients->c.name, clients->c.address) != 4)
		{
			free(clients);
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
			*pClientList = clients;
			aux = clients;
		}
		//else append the new node to the end of the list
		else
		{
			aux->next = clients;
			clients->previous = aux;
			aux = aux->next;
		}
		//make the list circular
		(*pClientList)->previous = clients;
		clients->next = *pClientList;
	}
}

//loads data from a binary file into a list
int loadBinClientData(pClientList* pClientList) {
	FILE* fp;

	fp = fopen(DATABASEFOLDERCLIENTBIN, "rb"); //open file to read in binary

	//check if file was successfully opened
	if (fp == NULL)
		return -1;

	clientList* aux = NULL;
	while (true) {
		clientList* clients = (clientList*)malloc(sizeof(clientList));
		if (clients == NULL)
			return -2;

		//read the data from the file into the current node
		fread(&clients->c, sizeof(clientList), 1, fp);
		if (clients == NULL || feof(fp))
		{
			free(clients);
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
			*pClientList = clients;
			aux = clients;
		}
		//else append the new node to the end of the list
		else
		{
			aux->next = clients;
			clients->previous = aux;
			aux = aux->next;
		}
		//make the list circular
		(*pClientList)->previous = clients;
		clients->next = *pClientList;
	}
}

//saves data from a bin file into a list
int saveClients(clientList* ClientList) {
	//check if list is empty
	if (ClientList == NULL)
		return -2;

	FILE* fp;

	fp = fopen(DATABASEFOLDERCLIENTBIN, "wb"); //open file to write in binary

	//check if file was successfully opened
	if (fp == NULL)
		return -1;

	clientList* aux = ClientList;

	do
	{
		//write the contents of the current node to the file
		fwrite(aux, sizeof(clientList), 1, fp);
		aux = aux->next;
	} while (aux != ClientList);

	fclose(fp);
	return 0;
}

#pragma endregion

#pragma region ClientsFunctions

//insert a client into the list
int insertClient(clientList** ClientList, int n, char nam[], int m, char addr[]) {
	//start at the head of the list
	clientList* aux = *ClientList;

	if ((*ClientList)->c.nif == n)
		return -4;

	while (aux != NULL && aux->next != *ClientList)
	{
		//if already exists, return false
		if (aux->c.nif == n)
			return -4;
		aux = aux->next;
	}

	//allocate memory
	clientList* v = (clientList*)malloc(sizeof(clientList));
	if (v == NULL)
		return -2;
	v->c.nif = n;
	v->c.money = m;
	strcpy(v->c.name, nam);
	strcpy(v->c.address, addr);

	//insert after the last node of the list
	if (aux != NULL) {
		aux->next = v;
		v->previous = aux;
	}
	//if list is empty, insert as the head of the list
	else {
		*ClientList = v;
	}

	//make the list circular
	v->next = *ClientList;
	(*ClientList)->previous = v;

	return 0;
}

//remove a client from the list
int removeClient(pClientList* pClientList, int n) {
	//start at the head of the list
	clientList* aux = *pClientList;
	clientList* aux2;

	//check if the list is empty
	if (aux == NULL)
		return -2;

	//search the list to find the node to be removed
	while (aux->c.nif != n)
	{
		aux = aux->next;
		//the node was not found
		if (aux == *pClientList)
			return -5;
	}

	//if the node to be deleted is the head of the list
	if (aux == *pClientList)
		//if the list only has one node
		if ((*pClientList)->next == *pClientList)
		{
			//deallocate memory for the list
			free(*pClientList);
			//set the pointer to the list to NULL
			*pClientList = NULL;
		}
		else
			//move head to the next node
			*pClientList = (*pClientList)->next;

	//uptade the links of the nods
	aux2 = aux->previous;
	aux2->next = aux->next;
	aux2 = aux->next;
	aux2->previous = aux->previous;

	//deallocate memory
	free(aux);
	return 0;
}

//chance a client from the list
int chanceClient(pClientList* pClientList, int nF, int n, char nam[], int m, char addr[]) {
	//start at the head of the list
	clientList* aux = *pClientList;
	clientList* aux2;

	//check if the list is empty
	if (aux == NULL)
		return -2;

	//search the list to find the node to be chanced
	while (aux->c.nif != nF)
	{
		aux = aux->next;
		//the node was not found
		if (aux == *pClientList)
			return -5;
	}

	aux->c.nif = n;
	aux->c.money = m;
	strcpy(aux->c.address, addr);
	strcpy(aux->c.name, nam);

	//deallocate memory
	return 0;
}

/**
 * finds a client based on the nif.
 * 
 * \param ClientList: List of Clients
 * \param n: nif
 * \param outClient: address of client to return
 * \return true if finded
 */
bool findClient(clientList* ClientList, int n, client* outClient){
	//start at the head of the list
	clientList* aux = ClientList;

	if (aux == NULL)
		return false;

	do
	{
		//if exists, return true
		if (aux->c.nif == n){
			*outClient = aux->c;
			return true;
		}
		aux = aux->next;
	} while (aux != ClientList);

	return false;
}

#pragma endregion
