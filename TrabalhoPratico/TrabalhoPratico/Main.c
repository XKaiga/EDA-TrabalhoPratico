/*****************************************************************//**
 * \file   Main.c
 * \brief  Contains the Main function
 *
 * \author Helder
 * \date   March 2023
 *********************************************************************/

#include "Headers.h"

main() {
	vehicleList* VehicleList = NULL;
	clientList* ClientList = NULL;
	recordList* RecordList = NULL;

	loadBinVehicleData(&VehicleList);
	loadBinClientData(&ClientList);
	loadBinRecordData(&RecordList);

	vehicleList* aux = VehicleList;
	int i = 0;
	do
	{
		printf("%d\n", aux->v.cod);
		i++;
		aux = aux->next;
	} while (aux != VehicleList);





	printf("\n\n\n");
	aux = VehicleList;
	i = 0;
	do
	{
		printf("%d\n", aux->v.cod);
		i++;
		aux = aux->next;
	} while (aux != VehicleList);
}
