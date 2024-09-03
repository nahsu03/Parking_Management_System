#ifndef PARKINGLOTMANAGER_H
#define PARKINGLOTMANAGER_H

#include "ParkingLot.h"
#include <string>

using namespace std;

class ParkingLotManager {
private:
    ParkingLot parkingLot;
    string filePath;
    string userId;

    void loadData();
    void saveData();

public:
    ParkingLotManager(const string& filePath, const string& userId);
    void setParkingLotSize();
    void setParkingLotTarget();
    void setParkingFee();
    void showMenu();
};

#endif // PARKINGLOTMANAGER_H
