
#ifndef DATABASEFOLDERRECORDTXT
#define DATABASEFOLDERRECORDTXT "DataBases/RecordDataBase.txt"
#define DATABASEFOLDERRECORDBIN "DataBases/RecordDataBase.bin"

#pragma region RecordsStructs

typedef struct {
	int cod;
	vehicle v;
	client c;
}record;

typedef struct {
	record r;
	struct recordList* next;
	struct recordList* previous;
}recordList, * pRecordList;

#pragma endregion

#pragma region Save&Load

int loadTxtRecordData(pRecordList* pRecordList, clientList* ClientList, vehicleList* VehicleList);

int loadBinRecordData(struct pRecordList* pRecordList);

int saveRecords(struct recordList* RecordList);

#pragma endregion

#pragma region RecordsFunctions

int createRecord(recordList* RecordList, int c, vehicle veh, client cli);

#pragma endregion

#endif