

#ifndef hg
#define hg 1

#include "Headers.h"

#pragma region Structs

typedef struct
{
	char name[N];
	localList nextLocals;
}local;

typedef struct {
	local l;
	int distance;
	localList* next;
	localList* previous;
}localList, *pLocalList;

#pragma endregion

#pragma region Save&Load

//loadTxtRecordData(pRecordList* pRecordList, clientList* ClientList, vehicleList* VehicleList);

//loadBinRecordData(struct pRecordList* pRecordList);

//saveRecords(struct recordList* RecordList);

#pragma endregion

#pragma region Functions

//create a local

//?

#pragma endregion

#endif
