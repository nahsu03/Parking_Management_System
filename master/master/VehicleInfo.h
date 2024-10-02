#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <sstream>

using namespace std;

class VehicleInfo {
private:
    string vehiclePlate;
    string vehicleType;
    double parkedTime;

public:
    VehicleInfo() : vehicleType(""), vehiclePlate(""),parkedTime(0.0) {}
    VehicleInfo(string type, string plate, double time) :  vehicleType(type), vehiclePlate(plate), parkedTime(time) {}

    string getVehicleType() const {
        return vehicleType;
    }

    string getVehiclePlate() const {
        return vehiclePlate;
    }
    double getParkedTime()  {
        return parkedTime;
    }

    void setVehicleType(string type) {
        vehicleType = type;
    }

    void setVehiclePlate(string plate) {
        vehiclePlate = plate;
    }

    void setParkedTime(double time) {
        parkedTime = time;
    }

    bool isEmpty() const {
        return vehicleType.empty() && vehiclePlate.empty();
    }
};
