
#include "Headers.h"

#pragma region Save&Load

int loadTxtLocalData(pLocalList* pLocalList) {
	FILE* fp;

	fp = fopen(DATABASEFOLDERVEHICLETXT, "r"); //open file to read in txt

	//check if file was successfully opened
	if (fp == NULL)
		return -1;

	localList* aux = NULL;
	while (true) {
		localList* locals = (localList*)malloc(sizeof(localList));
		if (locals == NULL)
			return -2;

		//read the data from the file into the struct
		if (fscanf(fp, "%[^;];%d", ) != 2)
		{
			free(locals);
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
			*pLocalList = locals;
			aux = locals;
		}
		//else append the new node to the end of the list
		else
		{
			aux->next = locals;
			locals->previous = aux;
			aux = aux->next;
		}
		//make the list circular
		(*pLocalList)->previous = locals;
		locals->next = *pLocalList;
	}
}

//loadBinRecordData(struct pLocalList* pLocalList);

//saveRecords(struct recordList* RecordList);

#pragma endregion

#pragma region Functions

//create a vertice

#pragma endregion

