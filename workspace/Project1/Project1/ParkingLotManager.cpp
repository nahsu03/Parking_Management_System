#include "ParkingLotManager.h"
#include "ParkingLotService.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
int NN, MM;
ParkingLotManager::ParkingLotManager(const string& filePath, const string& userId)
    : filePath(filePath), userId(userId) {
    loadData();  // 사용자 데이터를 로드하거나 초기화
}

void ParkingLotManager::loadData() {
    ifstream file(filePath);
    string line, token;
    bool userExists = false;

    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() == 6 && tokens[0] == userId) {
            parkingLot.setSizeX(stoi(tokens[1]));
            parkingLot.setSizeY(stoi(tokens[2]));
            parkingLot.setTargetX(stoi(tokens[3]));
            parkingLot.setTargetY(stoi(tokens[4]));
            parkingLot.setFee(stod(tokens[5]));
            userExists = true;
            break;
        }
    }

    if (!userExists) {
        parkingLot.setSizeX(0);
        parkingLot.setSizeY(0);
        parkingLot.setTargetX(0);
        parkingLot.setTargetY(0);
        parkingLot.setFee(0.0);
        saveData();  // 초기화된 데이터를 저장
    }

    file.close();
}

void ParkingLotManager::saveData() {
    ifstream file(filePath);
    vector<string> lines;
    string line;
    bool userExists = false;

    while (getline(file, line)) {
        if (line.find(userId) == 0) {
            stringstream ss;
            ss << userId << ","
                << parkingLot.getSizeX() << ","
                << parkingLot.getSizeY() << ","
                << parkingLot.getTargetX() << ","
                << parkingLot.getTargetY() << ","
                << parkingLot.getFee();
            lines.push_back(ss.str());
            userExists = true;
        }
        else {
            lines.push_back(line);
        }
    }

    if (!userExists) {
        stringstream ss;
        ss << userId << ","
            << parkingLot.getSizeX() << ","
            << parkingLot.getSizeY() << ","
            << parkingLot.getTargetX() << ","
            << parkingLot.getTargetY() << ","
            << parkingLot.getFee();
        lines.push_back(ss.str());
    }

    file.close();

    ofstream outFile(filePath, ios::trunc);
    for (const string& line : lines) {
        outFile << line << "\n";
    }
    outFile.close();
}

void ParkingLotManager::setParkingLotSize() {
    int sizex, sizey;
    cout << "Enter the new size X of the parking lot: ";
    cin >> sizex;
    NN = sizex;
    parkingLot.setSizeX(sizex);
    cout << "Enter the new size Y of the parking lot: ";
    cin >> sizey;
    MM = sizey;
    parkingLot.setSizeY(sizey);
    cout << "Parking lot size set to " << sizex << "x" << sizey << " spots.\n";
    saveData();  // 데이터 변경 시 저장
}

void ParkingLotManager::setParkingLotTarget() {
    int targetx, targety;
    cout << "Enter the new target X of the parking lot: ";
    cin >> targetx;
    parkingLot.setTargetX(targetx);
    cout << "Enter the new target Y of the parking lot: ";
    cin >> targety;
    parkingLot.setTargetY(targety);
    cout << "Parking lot target set to " << targetx << "x" << targety << " spots.\n";
    saveData();  // 데이터 변경 시 저장
}

void ParkingLotManager::setParkingFee() {
    double fee;
    cout << "Enter the new parking fee per hour: ";
    cin >> fee;
    parkingLot.setFee(fee);
    cout << "Parking fee set to $" << fee << " per hour.\n";
    saveData();  // 데이터 변경 시 저장
}

void ParkingLotManager::showMenu() {
    int choice;

    while (true) {
        cout << "+------------------------------------------+\n";
        cout << "|          Parking Lot Manager Menu        |\n";
        cout << "+------------------------------------------+\n";
        cout << "1. Start Parking Lot Service\n";
        cout << "2. Set Parking Lot Size\n";
        cout << "3. Set Parking Lot Target\n";
        cout << "4. Set Parking Fee\n";
        cout << "5. Calculate Fee\n";
        cout << "6. Logout\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            
            ParkingLotService* ps{};
            int x = NN;
            int y = MM;
            ps->initializeParkingLot(x,y);
            ps->showParkingLotService();
            
        }
        else if (choice == 2) {
            setParkingLotSize();
        }
        else if (choice == 3) {
            setParkingLotTarget();
        }
        else if (choice == 4) {
            setParkingFee();
        }
        else if (choice == 5) {
            // 정산 확인
        }
        else if (choice == 6) {
            cout << "Logging out...\n";
            break;
        }
        else {
            cout << "Invalid option. Please choose again.\n";
        }
    }
}
