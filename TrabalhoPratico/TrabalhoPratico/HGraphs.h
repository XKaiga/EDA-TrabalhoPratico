

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
	bool visited;
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
//insert a local into the graph
insertLocal(pLocalList* graph, local braga);

//create a adjacent local
adjLocal* newAdjLocal(int cod, int dist);

#pragma endregion

#endif
