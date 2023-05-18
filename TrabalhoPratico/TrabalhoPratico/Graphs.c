
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
	newlocal.visited = false;
	strcpy(newlocal.name, name);
	newlocal.cod = cod;
	return newlocal;
}

//insert a local into the graph
bool insertLocal(pLocalList* graph, local braga) {
	if (!*graph) {
		*graph = (localList*)malloc(sizeof(localList));
		(*graph)->l = braga;
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
	aux->previous = aux2;
	aux->next = *graph;
	(*graph)->previous = aux;

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

#pragma endregion

