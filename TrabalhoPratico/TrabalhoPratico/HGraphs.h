

#ifndef hg
#define hg 1

#include "Headers.h"

#pragma region Structs

typedef struct {
	int cod;
	int distance;
	struct adjLocal* next;
}adjLocal;

typedef struct
{
	int cod;
	char name[N];
	struct adjLocal* adjLocals;
}local;

typedef struct {
	local l;
	struct localList* next;
	struct localList* previous;
}localList, *pLocalList;

#pragma endregion

#pragma region Save&Load

//loadTxtRecordData(pRecordList* pRecordList, clientList* ClientList, vehicleList* VehicleList);

//loadBinRecordData(struct pRecordList* pRecordList);

//saveRecords(struct recordList* RecordList);

#pragma endregion

#pragma region Functions

//create a local
local newLocal(int cod, char* name);
//insert a new local into the graph
bool insertNewLocal(pLocalList* graph, int cod, char* name);

//create a adjacent local
adjLocal* newAdjLocal(int cod, int dist);
//insert a adjacent local into a local
adjLocal* insertAdjLocal(adjLocal* ajdsLocal, adjLocal* adjL);

#pragma endregion

#endif
