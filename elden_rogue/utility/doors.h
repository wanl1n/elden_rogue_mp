#ifndef DOORS_MANAGER
#define DOORS_MANAGER

Door* createDoorArray(int nArea);
Door* createNodeFromDoor (Door sDoor);
void connectDoors(Door* pDoorList, Door* pDoorArray, int nIndex);
Door* createConnectedDoorList (int nArea);

#endif