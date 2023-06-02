
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
//removes money from client based on the price of the vehicle
bool removeMoneyFromClient(int nif, int price, clientList* ClientList);

int createRecord(recordList* RecordList, int c, vehicle veh, client cli, clientList* ClientList);

#pragma endregion

#endif