
#ifndef DATABASEFOLDERVEHICLETXT
#define DATABASEFOLDERVEHICLETXT "DataBases/VehicleDataBase.txt"
#define DATABASEFOLDERVEHICLEBIN "DataBases/VehicleDataBase.bin"

#pragma region VehiclsStructs

typedef struct {
	int cod;
	char brand[N];
	char type[N];
	char location[N];
	int batery, price, years;
}vehicle;

typedef struct {
	vehicle v;
	struct vehicleList* next;
	struct vehicleList* previous;
}vehicleList, *pVehicleList;

#pragma endregion


#pragma region Save&Load

int loadTxtVehicleData(struct pVehicleList* pVehicleList);

int loadBinVehicleData(struct pVehicleList* pVehicleList);

int saveVehicles(struct vehicleList* VehicleList);

#pragma endregion


#pragma region vehiclesFunctions
vehicleList* createNewVehicle(int c, char typ[], int bat, int pri, int ys, char local[], char bran[]);

int insertVehicle(struct pVehicleList* pVehicleList, vehicle v, bool listCircular);
int insertVehicleList(struct pVehicleList* pVehicleList, vehicleList* v, bool listCircular);

int removeVehicle(struct pVehicleList* pVehicleList, int c);

int chanceVehicle(struct pVehicleList* pVehicleList, int cF, int c, char typ[], int bat, int pri, int ys, char local[], char bran[]);

int vehiclesDescendingOrder(pVehicleList* VehicleList);

int vehiclesFromLocal(vehicleList* VehicleList, char local[], vehicleList** out);

bool findVehicle(vehicleList* VehicleList, int c, vehicle* outVehicle);
bool findVehicleCircularList(vehicleList* VehicleList, int c, vehicle* outVehicle);

int findHowManyVehiclesWithType(vehicleList* VehiclesList, char* type);
bool removeVehicleFromVehicleList(pVehicleList* VehicleList, int cod);
bool findVehiclesBelow50(vehicleList* VehicleList, pVehicleList* pFindedVehicles);

#pragma endregion


#pragma region LocalFunctions

bool findVehiclesInLocal(vehicleList* VehicleList, char* localName, pVehicleList* pFindedVehicles, bool withType, char* type);
bool findVehiclesInLocalCircularList(vehicleList* VehicleList, char* localName, pVehicleList* pFindedVehicles, bool withType, char* type);
bool findVehiclesInRadius(struct localList* graph, vehicleList* VehicleList, char* nameOrigin, int radius, pVehicleList* pFindedVehicles, bool withType, char* type);

#pragma endregion


#endif 