// parkinglotService.h


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include "Vehicle.h"

using namespace std;

class ParkingLotService {

public:
    string userId;
    int rows, cols;
    int targetX, targetY;
    double fee;
    string vehicleFilePath;
    Vehicle** map;
    ParkingLotService();
    ParkingLotService(int rows, int cols);
    ParkingLotService(const string& filePath, const string& userId);
    ~ParkingLotService();
    void initializeParkingLot(int x,int y);
    void enterVehicle(const Vehicle& vehicle);
    void exitVehicle(const string& licensePlate);
    vector<Vehicle> readVehicle() const;

    void printVehicleInfo(int currentRow, int currentCol);
    void printArray(int currentRow, int currentCol);
    void gotoxy(int x, int y);
    void showParkingLotService();

    void loadDataFromFile(const string & filePath);


    string getUserId();
    void setUserId(string & userId);

    // Getter and Setter for rows
    int getRows();
    void setRows(int rows);

    // Getter and Setter for cols
    int getCols();
    void setCols(int cols);

    // Getter and Setter for targetX
    int getTargetX();
    void setTargetX(int targetX);

    // Getter and Setter for targetY
    int getTargetY();
    void setTargetY(int targetY);

    // Getter and Setter for fee
    double getFee();
    void setFee(double fee);

    // Getter and Setter for vehicleFilePath
    string getVehicleFilePath();
    void setVehicleFilePath(const string & vehicleFilePath);
    
};