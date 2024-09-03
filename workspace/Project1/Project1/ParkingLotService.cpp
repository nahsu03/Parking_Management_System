#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <conio.h>   // _getch
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "ParkingLotService.h"

using namespace std;

ParkingLotService::ParkingLotService(const string& filePath, const string& userId)
    : userId(userId) {
    loadDataFromFile(filePath);
    vehicleFilePath = userId + "_vehicles.csv";
    //initializeParkingLot();
}


void ParkingLotService::initializeParkingLot(int x,int y) {
    for (int i = 0; i < x; ++i) {//rows
        for (int j = 0; j < y; ++j) { //cols
            map[i][j] = Vehicle();
        }
    }
    // 번호판 모델 타임 
    map[0][0] = Vehicle("user1", "Sedan", 0.6);
    map[0][1] = Vehicle("user2", "SUV", 3.2);
    map[1][0] = Vehicle("user5", "Van", 5.4);
    map[2][0] = Vehicle("user9", "Hatchback", 0.9);
    map[3][1] = Vehicle("user14", "Van", 1.6);

}

void ParkingLotService::loadDataFromFile(const string& filePath) {
    ifstream file(filePath);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string id;
        getline(ss, id, ',');

        if (id == userId) {
            ss >> rows;
            ss.ignore();
            ss >> cols;
            ss.ignore();
            ss >> targetX;
            ss.ignore();
            ss >> targetY;
            ss.ignore();
            ss >> fee;
            break;
        }
    }
    file.close();
}

/*
void ParkingLotService::enterVehicle(const Vehicle& vehicle) {
    ofstream file(vehicleFilePath, ios::app); // append mode
    if (file.is_open()) {
        file << vehicle.getLicensePlate() << ","
            << vehicle.getModel() << ","
            << time(nullptr) << endl; // 현재 시각 저장
        file.close();
    }
    else {
        cerr << "Unable to open file for writing." << endl;
    }
}
*/

void ParkingLotService::exitVehicle(const string& licensePlate) {
    ifstream file(vehicleFilePath);
    ofstream tempFile("temp.csv");
    string line;

    if (file.is_open() && tempFile.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string plate;
            getline(ss, plate, ',');

            if (plate != licensePlate) {
                tempFile << line << endl;
            }
        }
        file.close();
        tempFile.close();

        remove(vehicleFilePath.c_str());
        rename("temp.csv", vehicleFilePath.c_str());
    }
    else {
        cerr << "Unable to open file for reading/writing." << endl;
    }
}

vector<Vehicle> ParkingLotService::readVehicle() const {
    ifstream file(vehicleFilePath);
    vector<Vehicle> vehicles;
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string licensePlate, model;
            double parkingTime;

            getline(ss, licensePlate, ',');
            getline(ss, model, ',');
            ss >> parkingTime;

            Vehicle vehicle(licensePlate, model, parkingTime);
            vehicle.setParkingTime(parkingTime);
            vehicles.push_back(vehicle);
        }
        file.close();
    }
    else {
        cerr << "Unable to open file for reading." << endl;
    }
    return vehicles;
}



ParkingLotService::~ParkingLotService() {
    for (int i = 0; i < rows; ++i) {
        delete[] map[i];
    }
    delete[] map;
}


/*
void ParkingLotService::initializeParkingLot() {
    parkingLotManager.loadSettings();
}
*/
void ParkingLotService::printVehicleInfo(int currentRow, int currentCol) {
    Vehicle currentInfo = map[currentRow][currentCol];
    if (!currentInfo.isEmpty()) {
        cout << "차량 번호: " << currentInfo.getLicensePlate() << endl;
        cout << "차량 종류: " << currentInfo.getModel() << endl;
        cout << "주차된 시간: " << currentInfo.getParkedTime() << endl;
    }
    else {
        cout << "이 위치는 비어 있습니다." << endl;
    }
}

void ParkingLotService::printArray(int currentRow, int currentCol) {
    system("cls");

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i == currentRow && j == currentCol) {
                cout << "[ X ] ";
            }
            else {
                if (map[i][j].isEmpty()) {
                    cout << "[ 0 ] ";
                }
                else {
                    cout << "[ 1 ] ";
                }
            }
        }
        cout << endl;
    }

    gotoxy(0, rows + 2);
    printVehicleInfo(currentRow, currentCol);
}

void ParkingLotService::gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ParkingLotService::showParkingLotService() {
    int currentRow = 0, currentCol = 0;

    while (true) {
        printArray(currentRow, currentCol);

        int key = _getch();

        if (key == 224) {
            key = _getch();

            if (key == 72 && currentRow > 0) {
                currentRow--;
            }
            else if (key == 80 && currentRow < rows - 1) {
                currentRow++;
            }
            else if (key == 75 && currentCol > 0) {
                currentCol--;
            }
            else if (key == 77 && currentCol < cols - 1) {
                currentCol++;
            }
        }
        else if (key == 27) {
            break;
        }
    }
}

// Getter and Setter for userId
string ParkingLotService::getUserId() {
    return userId;
}

void ParkingLotService::setUserId( string& userId) {
    this->userId = userId;
}

// Getter and Setter for rows
int ParkingLotService::getRows()  {
    return rows;
}

void ParkingLotService::setRows(int rows) {
    this->rows = rows;
}

// Getter and Setter for cols
int ParkingLotService::getCols()  {
    return cols;
}

void ParkingLotService::setCols(int cols) {
    this->cols = cols;
}

// Getter and Setter for targetX
int ParkingLotService::getTargetX(){
    return targetX;
}

void ParkingLotService::setTargetX(int targetX) {
    this->targetX = targetX;
}

// Getter and Setter for targetY
int ParkingLotService::getTargetY() {
    return targetY;
}

void ParkingLotService::setTargetY(int targetY) {
    this->targetY = targetY;
}

// Getter and Setter for fee
double ParkingLotService::getFee() {
    return fee;
}

void ParkingLotService::setFee(double fee) {
    this->fee = fee;
}

// Getter and Setter for vehicleFilePath
string ParkingLotService::getVehicleFilePath()  {
    return vehicleFilePath;
}

void ParkingLotService::setVehicleFilePath(const string& vehicleFilePath) {
    this->vehicleFilePath = vehicleFilePath;
}