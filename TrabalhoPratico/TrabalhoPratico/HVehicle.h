
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
}vehicleList, * pVehicleList;

#pragma endregion

#pragma region Save&Load

int loadTxtVehicleData(struct pVehicleList* pVehicleList);

int loadBinVehicleData(struct pVehicleList* pVehicleList);

int saveVehicles(struct vehicleList* VehicleList);

#pragma endregion

#pragma region vehiclesFunctions

int insertVehicle(struct vehicleList* VehicleList, int c, char typ[], int bat, int pri, int ys, char local[], char bran[]);

int removeVehicle(struct pVehicleList* pVehicleList, int c);

int chanceVehicle(struct pVehicleList* pVehicleList, int cF, int c, char typ[], int bat, int pri, int ys, char local[], char bran[]);

int vehiclesDescendingOrder(pVehicleList* VehicleList);

int vehiclesFromLocal(vehicleList* VehicleList, char local[], vehicleList** out);

bool findVehicle(vehicleList* VehicleList, int c, vehicle* outVehicle);
#pragma endregion

#endif 