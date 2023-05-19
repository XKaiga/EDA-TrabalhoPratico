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

	localList* graph = NULL;
	int localCod = 1;

	//insert new locals into the graph
	insertNewLocal(&graph, localCod, "Braga");
	localCod++;
	insertNewLocal(&graph, localCod, "Faro");
	localCod++;
	insertNewLocal(&graph, localCod, "Barcelos");
	localCod++;

	localList* aux = graph->next;
	while (aux != graph)
	{
		printf("%s\n", aux->l.name);
		aux = aux->next;
		if (aux == graph)
			printf("%s\n", aux->l.name);
	}

	//create a adjacent local
	//insert a adjacent local into a local

	//create
	//show
	/*
		Vertice* CriaVertice(char* cidade, int tot);
		Vertice* InsereVertice(Vertice* g, Vertice* novo, bool*res);
		void MostraGrafo(Vertice* g);
		int ProcuraCodigoVertice(Vertice* g, char* cidade);
		Vertice* ProcuraVertice(Vertice* g, char* cidade);
		Vertice* ProcuraVerticeCod(Vertice* g, int cod);

		Vertice* InsereAdjacenteVertice(Vertice* g, char* origem, char* dest, float peso, bool* res);
		Adj* CriaAdj(int cod, float peso);
		Adj* InsereAdj(Adj* h, Adj* novo, bool* res);
		bool ExisteAdjacentes(Adj* h, int cod);
		void MostraAdjacencias(Adj* h);

		int CountPaths(Vertice* g, int src, int dst, int pathCount);
		int CountPathsVerticesName(Vertice* g, char* src, char* dest, int pathCount);
		bool DepthFirstSearchRec(Vertice* g, int origem, int dest);
		bool DepthFirstSearchNamesRec(Vertice* g, char* src, char* dest);
		Vertice* ResetVerticesVisitados(Vertice* g);
	*/
}
