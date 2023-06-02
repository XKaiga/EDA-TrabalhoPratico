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
	localList* graph = NULL;

	loadBinVehicleData(&VehicleList);
	loadBinClientData(&ClientList);
	loadBinRecordData(&RecordList);
	
	//loadBinGraphData(&graph);
	loadBinLocalsData(&graph);
	loadBinAdjLocalsData(&graph);

#pragma region findShortestPath
	///*localList* aux3 = graph;
	//do
	//{
	//	if (strcmp(aux3->l.name, "Braga") == 0)
	//	{
	//		adjLocalList* a = aux3->adjLocals;
	//		do
	//		{
	//			char* b = findLocalNameByCod(graph, a->adjL.cod);
	//			if (strcmp(b, "Vila Real") == 0) {
	//				a->adjL.distance = 10;
	//				break;
	//			}
	//			a = a->next;
	//		} while (a != aux3->adjLocals);
	//		break;
	//	}
	//	aux3 = aux3->next;
	//} while (aux3 != graph);*/


	//localList* path2[2] = { NULL };
	//localList* path = NULL;
	//int kms[2] = { 0,0 };
	//bool finded = findShortestPath(graph, "Braga", "Viseu", kms, (localList * [2]) { &path, NULL }/*&path*/);
	//printf("km to be done: %d\n\n", kms[0]);


	//localList* aux = path;
	//printf("Path: ");
	//do
	//{
	//	printf("\n\t%s", aux->l.name);
	//	aux = aux->next;
	//} while (aux != path);
#pragma endregion

	char nameOrigin[N] = "Braga";
	travelingSalesman(VehicleList, 2, graph, nameOrigin) ? printf("\n\n\t True\n") : printf("\n\n\t False\n");
}
