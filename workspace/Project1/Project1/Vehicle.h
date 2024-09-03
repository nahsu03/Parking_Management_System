#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <ctime>
using namespace std;
class Vehicle {
private:
    string licensePlate;
    string model;
    double parkingTime;

public:
    Vehicle();
    Vehicle(string licensePlate, string model,double parkingTime);

    string getLicensePlate();
    string getModel();
    double getParkedTime();
    void setParkingTime(double parkingTime);

    bool isEmpty();
};

#endif
