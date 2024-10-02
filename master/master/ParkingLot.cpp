#include "ParkingLot.h"
#include "VehicleInfo.h"

ParkingLot::ParkingLot(int r, int c) : rows(r), cols(c) {
    // 메모리 할당 시 예외 처리
    try {
        parkingLot = new VehicleInfo * [rows];
        for (int i = 0; i < rows; ++i) {
            parkingLot[i] = new VehicleInfo[cols];
        }
    }
    catch (bad_alloc& ba) {
        cerr << "메모리 할당 실패: " << ba.what() << endl;
        exit(EXIT_FAILURE);  // 메모리 할당 실패 시 프로그램 종료
    }
}

ParkingLot::~ParkingLot() {
    for (int i = 0; i < rows; ++i) {
        delete[] parkingLot[i];
    }
    delete[] parkingLot;
}

void ParkingLot::initializeParkingLot(const string& filename) {
    /*
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            parkingLot[i][j] = VehicleInfo();
        }
    }*/
    loadFromCSV(filename); // CSV 파일에서 차량 정보를 불러오기
}

void ParkingLot::loadFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filename << endl;  // 파일 열림 여부 확인
        return;
    }
    else {
        cout << "파일이 성공적으로 열렸습니다: " << filename << endl;  // 파일이 성공적으로 열렸음을 표시
    }

    string line;
    int i = 0, j = 0;
    while (getline(file, line)) {
        if (i >= rows) break;

        stringstream ss(line);
        string vehicleType, vehiclePlate, parkedTime;

        getline(ss, vehicleType, ',');
        getline(ss, vehiclePlate, ',');
        getline(ss, parkedTime, ',');

        parkingLot[i][j] = VehicleInfo(vehicleType, vehiclePlate, stod(parkedTime));

        // 디버깅: 읽어온 데이터를 출력
        cout << "Loaded: " << ", " << vehicleType << ", " << vehiclePlate << parkedTime <<" into [" << i << "][" << j << "]" << endl;

        j++;
        if (j >= cols) {
            j = 0;
            i++;
        }
    }

    file.close();
}


void ParkingLot::printVehicleInfo(int currentRow, int currentCol) {
    VehicleInfo currentInfo = parkingLot[currentRow][currentCol];
    if (!currentInfo.isEmpty()) {
        
        cout << "차량 종류: " << currentInfo.getVehicleType() << endl;
        cout << "차량 번호: " << currentInfo.getVehiclePlate() << endl;
        cout << "주차한 시간: " << currentInfo.getParkedTime() << endl;
    }
    else {
        cout << "이 위치는 비어있습니다." << endl;
    }
}

void ParkingLot::printArray(int currentRow, int currentCol) {
    system("cls");

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i == currentRow && j == currentCol) {
                cout << "[ X ] ";
            }
            else {
                if (parkingLot[i][j].isEmpty()) {
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

void ParkingLot::gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ParkingLot::manageParkingLot() {
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
