#pragma once
#include "VehicleInfo.h"
#include <string>
using namespace std;

class ParkingLot {
private:
    int rows;
    int cols;
    VehicleInfo** parkingLot;

public:
    ParkingLot(int r, int c);
    ~ParkingLot();
    void loadFromCSV(const string& filename);
    void initializeParkingLot(const string& filename);
    void printVehicleInfo(int currentRow, int currentCol);
    void printArray(int currentRow, int currentCol);
    void gotoxy(int x, int y);
    void manageParkingLot();
};


