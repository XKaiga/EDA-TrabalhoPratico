
#include "Headers.h"

#pragma region Save&Load

//int loadTxtLocalData(pLocalList* pLocalList) {
//	FILE* fp;
//
//	fp = fopen(DATABASEFOLDERVEHICLETXT, "r"); //open file to read in txt
//
//	//check if file was successfully opened
//	if (fp == NULL)
//		return -1;
//
//	localList* aux = NULL;
//	while (true) {
//		localList* locals = (localList*)malloc(sizeof(localList));
//		if (locals == NULL)
//			return -2;
//
//		//read the data from the file into the struct
//		if (fscanf(fp, "%[^;];%d", ) != 2)
//		{
//			free(locals);
//			fclose(fp);
//			//check if there's an error reading the file
//			if (aux == NULL)
//				return -3;
//			else
//				return 0;
//		}
//		//if the list is empty, set the new node as the head of the list
//		if (aux == NULL)
//		{
//			*pLocalList = locals;
//			aux = locals;
//		}
//		//else append the new node to the end of the list
//		else
//		{
//			aux->next = locals;
//			locals->previous = aux;
//			aux = aux->next;
//		}
//		//make the list circular
//		(*pLocalList)->previous = locals;
//		locals->next = *pLocalList;
//	}
//}

//loadBinRecordData(struct pLocalList* pLocalList);

//saveRecords(struct recordList* RecordList);

#pragma endregion

#pragma region Functions

//create a local
local newLocal(int cod, char* name) {
	local newlocal;
	newlocal.adjLocals = NULL;
	strcpy(newlocal.name, name);
	newlocal.cod = cod;
	return newlocal;
}

//insert a new local into the graph
bool insertNewLocal(pLocalList* graph, int cod, char* name) {
	if (*graph == NULL) {
		*graph = (localList*)malloc(sizeof(localList));
		(*graph)->l = newLocal(cod, name);
		(*graph)->previous = NULL;
		(*graph)->next = *graph;
		return true;
	}

	localList* aux = *graph;
	while (aux->next != *graph)
		aux = aux->next;

	aux->next = (localList*)malloc(sizeof(localList));
	localList* aux2 = aux;
	aux = aux->next;
	aux->l = newLocal(cod, name);
	aux->previous = aux2;
	aux->next = *graph;
	(*graph)->previous = aux;
	return true;
}

//create a adjacent local
adjLocal* newAdjLocal(int cod, int dist) {
	adjLocal* adjL = (adjLocal*)malloc(sizeof(adjLocal));
	if (!adjL)
		return NULL;

	adjL->cod = cod;
	adjL->distance = dist;
	adjL->next = NULL;
	return adjL;
}

//insert a adjacent local into a local
adjLocal* insertAdjLocal(adjLocal* adjsLocal, adjLocal* adjL) {
	if (adjL == NULL)
		return NULL;
	
	adjLocal* aux = adjsLocal;

	while (aux)
		aux = aux->next;

	if (adjsLocal == NULL)
	{
		aux = adjL;
		return adjsLocal;
	}

	adjL->next = adjsLocal;
	adjsLocal = adjL;
	return adjsLocal;
}

#pragma endregion

