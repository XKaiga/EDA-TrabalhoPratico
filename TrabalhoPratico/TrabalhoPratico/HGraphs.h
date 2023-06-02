

#ifndef DATABASEFOLDERGRAPHTXT
#define DATABASEFOLDERGRAPHTXT "DataBases/GraphDataBase.txt"
#define DATABASEFOLDERGRAPHBIN "DataBases/GraphDataBase.bin"
#define DATABASEFOLDERLOCALBIN "DataBases/LocalDataBase.bin"
#define DATABASEFOLDERADJLOCALBIN "DataBases/AdjLocalDataBase.bin"
#define PRICEPERKM 3

#include "Headers.h"

#pragma region Structs
typedef struct {
	int codLocal;
	int codAdj;
	int distance;
}adjLocalFile;

typedef struct {
	int cod;
	int distance;
}adjLocal;

typedef struct {
	adjLocal adjL;
	struct adjLocalList* next;
}adjLocalList, * pAdjLocalList;

typedef struct
{
	int cod;
	char name[N];
}local;

typedef struct {
	local l;
	bool visited;
	struct adjLocalList* adjLocals;
	struct localList* next;
	struct localList* previous;
}localList, * pLocalList;

#pragma endregion


#pragma region Save&Load
/**
 * \brief Loads graph data from a .txt file.
 *
 * \param pGraph Pointer to the graph.
 * \return True if data was loaded successfully, false otherwise.
 */
bool loadTxtGraphData(pLocalList* pGraph);

/**
 * \brief Loads all locals data from a .bin file.
 *
 * \param pGraph Pointer to the graph.
 * \return True if data was loaded successfully, false otherwise.
 */
bool loadBinLocalsData(pLocalList* pGraph);

/**
 * \brief Loads all adjacent locals data from a .bin file.
 *
 * \param pGraph Pointer to the graph.
 * \return True if data was loaded successfully, false otherwise.
 */
bool loadBinAdjLocalsData(pLocalList* pGraph);

/**
 * \brief Saves the locals data from the graph to a .bin file.
 *
 * \param graph Pointer to the graph data structure.
 * \return -2 if graph == null, or -1 if gives error when opening file, or 0 if data was successfully saved.
 */
int saveLocals(localList* graph);

/**
 * \brief Saves the adjacent locals data from the graph to a .bin file.
 *
 * \param graph Pointer to the graph data structure.
 * \return -2 if graph == null, or -1 if gives error when opening file, or 0 if data was successfully saved.
 */
int saveAdjLocals(localList* graph);

#pragma region Graph
/**
 * \brief Loads all graph data from a .bin file.
 *
 * \param pGraph Pointer to the graph.
 * \return True if data was loaded successfully, false otherwise.
 */
bool loadBinGraphData(pLocalList* pGraph);

/**
 * \brief Saves all graph data to a .bin file.
 *
 * \param graph Pointer to the graph data structure.
 * \return -2 if graph == null, or -1 if gives error when opening file, or 0 if data was successfully saved.
 */
int saveGraph(localList* graph);

#pragma endregion

#pragma endregion


#pragma region Path
/**
 * \brief Display the path with its total distance and the price to pay.
 *
 * \param path The path to be displayed.
 * \param kms A pointer to the total distance of the path, and hepls calculate the price.
 * \return True if successful, false otherwise.
 */
bool showPath(localList* path, int* kms);

/**
 * \brief Find the shortest path between two locations in the graph.
 *
 * \param graph The graph.
 * \param nameOrigin The name of the origin location.
 * \param nameDest The name of the destination location.
 * \param kms Array to store the fastest distance [0] and updated distance [1] of the path.
 * \param path Pointer to store the shortest path.
 * \return True if successful, false otherwise.
 */
bool findShortestPath(localList* graph, char* nameOrigin, char* nameDest, int kms[2], localList** path);

/**
 * \brief Count the number of paths between two locations in the graph.
 *
 * \param graph The graph.
 * \param nameOrigin The name of the origin location.
 * \param nameDest The name of the destination location.
 * \param pCountPaths Pointer to store the count of paths.
 * \return True if successful, false otherwise.
 */
bool countPaths(localList* graph, char* nameOrigin, char* nameDest, int* pCountPaths);

/**
 * \brief Reset the visited variable of all locals in the graph.
 *
 * \param graph The graph.
 * \return True if successful, false otherwise.
 */
bool resetVisitedLocals(localList* graph);

#pragma endregion


#pragma region Traveling Salesman
/**
 * \brief Find the closest vehicle with batery below 50% from a given origin location.
 *
 * \param VehicleList Pointer to the list of vehicles with batery below 50% from the origin location.
 * \param capacity The available capacity for picking up vehicles.
 * \param graph The graph.
 * \param nameOrigin The name of the origin location.
 * \return True if successful, false otherwise.
 */
bool TS_GrabCar(pVehicleList* VehiclesBelow50, int* capacity, localList* graph, char* nameOrigin);

/**
 * \brief Find the shortest path for traveling salesman problem.
 *
 * \param VehicleList Pointer to a list of all available vehicles.
 * \param capacity Initial available capacity for picking up vehicles.
 * \param graph The graph.
 * \param nameOrigin The name of the origin location.
 * \return True if successful, false otherwise.
 */
bool travelingSalesman(vehicleList* VehicleList, int capacity, localList* graph, char* nameOrigin);

#pragma endregion


#pragma region LocalListFunctions
/**
 * \brief Copies the localList pointed by source to the destination.
 *
 * \param dest Pointer to the destination localList.
 * \param sour Pointer to the source localList.
 * \return True if successful, false otherwise.
 */
bool localListCopy(pLocalList* dest, localList* sour);

/**
 * \brief Remove the last localList from a local list.
 *
 * \param pLocalList Pointer to a local list.
 * \return True if successful, false otherwise.
 */
bool removeLastLocalList(pLocalList* pLocalList);

/**
 * \brief Count the number of adjacent locals in a adjacency list.
 *
 * \param adjList The adjacency list.
 * \return The count of adjacent locals.
 */
int countAdjLocals(adjLocalList* adjList);

#pragma endregion


#pragma region LocalsFunctions
/**
 * \brief Create a new local with the given code and name.
 *
 * \param cod The code of the local.
 * \param name The name of the local.
 * \return The created local.
 */
local newLocal(int cod, char* name);

/**
 * \brief Insert a new local into the graph with the given code and name.
 *
 * \param graph Pointer to the graph.
 * \param cod The code of the local.
 * \param name The name of the local.
 * \return True if successful, false otherwise.
 */
bool insertNewLocal(pLocalList* graph, int cod, char* name);

#pragma endregion


#pragma region AdjLocalsFunctions
/**
 * \brief Create a new adjacent local with the given code and distance.
 *
 * \param cod The code of the adjacent local.
 * \param dist The distance to the adjacent local.
 * \return Pointer to the created adjacent local.
 */
adjLocalList* newAdjLocal(int cod, int dist);

/**
 * \brief Insert a new adjacent local into a local in the graph by name.
 *
 * \param graph Pointer to the graph.
 * \param localName The name of a local to insert the adjacent local into.
 * \param adjName The name of the adjacent local.
 * \param dist The distance to the adjacent local.
 * \return True if successful, false otherwise.
 */
bool insertNewAdjLocalByName(localList* graph, char* localName, char* adjName, int dist);

/**
 * \brief Insert a new adjacent local into a local in the graph by code.
 *
 * \param graph Pointer to the graph.
 * \param localName The name of a local to insert the adjacent local into.
 * \param adjCod The code of the adjacent local.
 * \param dist The distance to the adjacent local.
 * \return True if successful, false otherwise.
 */
bool insertNewAdjLocalByCod(localList* graph, char* localName, int adjCod, int dist);

/**
 * \brief Insert a new adjacent local into a adjacency list.
 *
 * \param adjLocals Pointer to the adjacency list.
 * \param adjCod The code of the adjacent local.
 * \param dist The distance to the adjacent local.
 * \return True if successful, false otherwise.
 */
bool insertNewAdjLocal(pAdjLocalList* adjLocals, int adjCod, int dist);

#pragma endregion


#pragma region FindFunctions
/**
 * \brief Find a local in the graph by code.
 *
 * \param graph Pointer to the graph.
 * \param cod The code of the local to find.
 * \return Pointer to the found local, or NULL if not found.
 */
localList* findLocalByCod(localList* graph, int cod);

/**
 * \brief Find a local in the graph by name.
 *
 * \param graph Pointer to the graph.
 * \param name The name of the local to find.
 * \return Pointer to the found local, or NULL if not found.
 */
localList* findLocalByName(localList* graph, char* name);

/**
 * \brief Find the code of a local in the graph by name.
 *
 * \param graph Pointer to the graph.
 * \param name The name of the local to find.
 * \return The code of the found local, or -1 if not found.
 */
int findLocalCodByName(localList* graph, char* name);

/**
 * \brief Find the name of a local in the graph by code.
 *
 * \param graph Pointer to the graph.
 * \param cod The code of the local to find.
 * \return The name of the found local, or "" if not found.
 */
char* findLocalNameByCod(localList* graph, int cod);

#pragma endregion


#pragma region ShowFunctions
/**
 * \brief Show the graph, printing it.
 *
 * \param graph Pointer to the graph.
 * \return True if successful, false otherwise.
 */
bool showGraph(localList* graph);

/**
 * \brief Show the list of locals and their adjacent locals.
 *
 * \param graph Pointer to the graph.
 * \return True if successful, false otherwise.
 */
bool showLocalsAndAdjs(localList* graph);

/**
 * \brief Show the adjacent locals of a local.
 *
 * \param adjLocals Pointer to the adjacency list.
 * \return True if successful, false otherwise.
 */
bool showAdjs(adjLocalList* adjLocals);

#pragma endregion



#endif
