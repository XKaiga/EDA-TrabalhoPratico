/*****************************************************************//**
 * \file   Main.c
 * \brief  Contains the Main function
 *
 * \author Helder
 * \date   March 2023
 *********************************************************************/

#include "Headers.h"

main() {
	setlocale(LC_ALL, "Portuguese");	//para escrever caracteres portugueses
	vehicleList* VehicleList = NULL;
	clientList* ClientList = NULL;
	recordList* RecordList = NULL;

	loadBinVehicleData(&VehicleList);
	loadBinClientData(&ClientList);
	loadBinRecordData(&RecordList);

	localList* graph = NULL;
	int localCod = 1;

	local braga = newLocal(localCod, "Braga");
	localCod++;

	//insert a local into the graph
	insertLocal(&graph, braga);

	adjLocal* c = newAdjLocal(braga.cod, 2);
	adjLocal* c2 = newAdjLocal(braga.cod, 4);

	//insert a adjacent local into a local's adjacents list


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
