#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <sstream>


using namespace std;

class VehicleInfo {
private:
    string userId;
    string vehicleType;
    string vehiclePlate;

public:
    VehicleInfo() : userId(""), vehicleType(""), vehiclePlate("") {}
    VehicleInfo(string id, string type, string plate) : userId(id), vehicleType(type), vehiclePlate(plate) {}

    string getUserId() const {
        return userId;
    }

    string getVehicleType() const {
        return vehicleType;
    }

    string getVehiclePlate() const {
        return vehiclePlate;
    }

    void setUserId(string id) {
        userId = id;
    }

    void setVehicleType(string type) {
        vehicleType = type;
    }

    void setVehiclePlate(string plate) {
        vehiclePlate = plate;
    }

    bool isEmpty() const {
        return userId.empty() && vehicleType.empty() && vehiclePlate.empty();
    }
};

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

ParkingLot::ParkingLot(int r, int c) : rows(r), cols(c) {
    // �޸� �Ҵ� �� ���� ó��
    try {
        parkingLot = new VehicleInfo * [rows];
        for (int i = 0; i < rows; ++i) {
            parkingLot[i] = new VehicleInfo[cols];
        }
    }
    catch (bad_alloc& ba) {
        cerr << "�޸� �Ҵ� ����: " << ba.what() << endl;
        exit(EXIT_FAILURE);  // �޸� �Ҵ� ���� �� ���α׷� ����
    }
}

ParkingLot::~ParkingLot() {
    for (int i = 0; i < rows; ++i) {
        delete[] parkingLot[i];
    }
    delete[] parkingLot;
}

void ParkingLot::initializeParkingLot(const string& filename) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            parkingLot[i][j] = VehicleInfo();
        }
    }
    loadFromCSV(filename); // CSV ���Ͽ��� ���� ������ �ҷ�����
}

void ParkingLot::loadFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "������ �� �� �����ϴ�: " << filename << endl;
        return;
    }

    string line;
    int i = 0, j = 0;
    while (getline(file, line)) {
        if (i >= rows) break;

        stringstream ss(line);
        string userId, vehicleType, vehiclePlate;

        getline(ss, userId, ',');
        getline(ss, vehicleType, ',');
        getline(ss, vehiclePlate, ',');

        parkingLot[i][j] = VehicleInfo(userId, vehicleType, vehiclePlate);

        // �����: �о�� �����͸� ���
        cout << "Loaded: " << userId << ", " << vehicleType << ", " << vehiclePlate << " into [" << i << "][" << j << "]" << endl;

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
        cout << "���� ID: " << currentInfo.getUserId() << endl;
        cout << "���� ����: " << currentInfo.getVehicleType() << endl;
        cout << "���� ��ȣ: " << currentInfo.getVehiclePlate() << endl;
    }
    else {
        cout << "�� ��ġ�� ����ֽ��ϴ�." << endl;
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

int main() {
    int rows, cols;

    cout << "�������� ��(row) ���� �Է��ϼ���: ";
    cin >> rows;
    cout << "�������� ��(col) ���� �Է��ϼ���: ";
    cin >> cols;

    if (rows > 100 || cols > 100) {
        cerr << "�������� ũ�Ⱑ �ʹ� Ů�ϴ�. �ִ� ũ��� 100x100�Դϴ�." << endl;
        return 1;
    }

    ParkingLot parkingLot(rows, cols);
    parkingLot.initializeParkingLot("parkinglot.csv"); // CSV ���Ͽ��� �ʱ�ȭ
    parkingLot.manageParkingLot();

    return 0;
}
