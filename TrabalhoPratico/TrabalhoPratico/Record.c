/*****************************************************************//**
 * \file   Record.c
 * \brief  Record's Functions
 * 
 * \author Helder
 * \date   June 2023
 *********************************************************************/
#include "Headers.h"

#pragma region Save&Load

//loads data from a txt file into a list
int loadTxtRecordData(pRecordList* pRecordList, clientList* ClientList, vehicleList* VehicleList) {
	FILE* fp;

	fp = fopen(DATABASEFOLDERRECORDTXT, "r"); //open file to read in txt

	//check if file was successfully opened
	if (fp == NULL)
		return -1;

	recordList* aux = NULL;
	while (true) {
		recordList* records = (recordList*)malloc(sizeof(recordList));
		if (records == NULL)
			return -2;

		//read the data from the file into the struct
		if (fscanf(fp, "%d;%d;%d", &records->r.cod, &records->r.c.nif, &records->r.v.cod) != 3)
		{
			free(records);
			fclose(fp);
			//check if there's an error reading the file
			if (aux == NULL)
				return -3;
			else
				return 0;
		}

		findClient(ClientList, records->r.c.nif, &(records->r.c));
		findVehicleCircularList(VehicleList, records->r.v.cod, &(records->r.v));

		//if the list is empty, set the new node as the head of the list
		if (aux == NULL)
		{
			*pRecordList = records;
			aux = records;
		}
		//else append the new node to the end of the list
		else
		{
			aux->next = records;
			records->previous = aux;
			aux = aux->next;
		}
		//make the list circular
		(*pRecordList)->previous = records;
		records->next = *pRecordList;
	}
}

//loads data from a binary file into a list
int loadBinRecordData(pRecordList* pRecordList) {
	FILE* fp;

	fp = fopen(DATABASEFOLDERRECORDBIN, "rb"); //open file to read in binary

	//check if file was successfully opened
	if (fp == NULL)
		return -1;

	recordList* aux = NULL;
	while (true) {
		recordList* records = (recordList*)malloc(sizeof(recordList));
		if (records == NULL)
			return -2;

		//read the data from the file into the current node
		fread(&records->r, sizeof(record), 1, fp);
		if (records == NULL || feof(fp))
		{
			free(records);
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
			*pRecordList = records;
			aux = records;
		}
		//else append the new node to the end of the list
		else
		{
			aux->next = records;
			records->previous = aux;
			aux = aux->next;
		}
		//make the list circular
		(*pRecordList)->previous = records;
		records->next = *pRecordList;
	}
}

//saves data from a bin file into a list
int saveRecords(recordList* RecordList) {
	FILE* fp;

	fp = fopen(DATABASEFOLDERRECORDBIN, "wb"); //open file to write in binary

	//check if file was successfully opened
	if (fp == NULL)
		return -1;

	recordList* aux = RecordList;

	//check if list is empty
	if (aux == NULL)
		return -2;

	do
	{
		//write the contents of the current node to the file
		fwrite(&aux->r, sizeof(record), 1, fp);
		aux = aux->next;
	} while (aux != RecordList);

	fclose(fp);
	return 0;
}

#pragma endregion

#pragma region RecordsFunctions
//removes money from client based on the price of the vehicle
bool removeMoneyFromClient(int nif, int price, clientList* ClientList) {
	if (ClientList == NULL)
		return false;

	clientList* aux = ClientList;
	do
	{
		if (aux->c.nif == nif)
			if (aux->c.money < price)
				return false;
			else
			{
				aux->c.money -= price;
				return true;
			}
		aux = aux->next;
	} while (aux != ClientList);
	return false;
}

//creates a record and adds it into the list
int createRecord(recordList* RecordList, int c, vehicle veh, client cli, clientList* ClientList) {
	if (cli.money < veh.price)
		return -6;

	//start at the head of the list
	recordList* aux = RecordList;

	if (RecordList->r.cod == c)
		return -4;

	while (aux != NULL && aux->next != RecordList)
	{
		//if already exists, return false
		if (aux->r.cod == c)
			return -4;
		aux = aux->next;
	}

	//allocate memory
	recordList* rl = (recordList*)malloc(sizeof(recordList));
	if (rl == NULL)
		return -2;
	bool removed = removeMoneyFromClient(cli.nif, veh.price, ClientList);
	if (!removed) {
		free(rl);
		return -7;
	}
	rl->r.cod = c;
	rl->r.c = cli;
	rl->r.v = veh;

	//insert after the last node of the list
	if (aux != NULL) {
		aux->next = rl;
		rl->previous = aux;
	}
	//if list is empty, insert as the head of the list
	else {
		RecordList = rl;
		free(aux);
	}

	//make the list circular
	rl->next = RecordList;
	RecordList->previous = rl;

	return 0;
}

#pragma endregion

