
#ifndef DATABASEFOLDERCLIENTTXT
#define DATABASEFOLDERCLIENTTXT "DataBases/ClientDataBase.txt"
#define DATABASEFOLDERCLIENTBIN "DataBases/ClientDataBase.bin"

#pragma region ClientsStructs

typedef struct {
	int nif;
	int money;
	char name[N];
	char address[N];
}client;

typedef struct {
	client c;
	struct clientList* next;
	struct clientList* previous;
}clientList, * pClientList;

#pragma endregion

#pragma region Save&Load

int loadTxtClientData(pClientList* pClientList);

int loadBinClientData(pClientList* pClientList);

int saveClients(clientList* ClientList);

#pragma endregion

#pragma region ClientsFunctions

int insertClient(clientList* ClientList, int n, char nam[], int m, char addr[]);

int removeClient(pClientList* pClientList, int n);

int chanceClient(pClientList* pClientList, int nF, int n, char nam[], int m, char addr[]);

bool findClient(clientList* ClientList, int n, client* outClient);

#pragma endregion

#endif