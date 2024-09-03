#include "Vehicle.h"
#include <ctime>
using namespace std;
Vehicle::Vehicle()
{
    this->licensePlate = licensePlate;
    this->model = model;
    this->parkingTime = parkingTime;
}

Vehicle::Vehicle(string licensePlate, string model,double time)
    : licensePlate(licensePlate), model(model), parkingTime(time) {}

bool Vehicle::isEmpty()
{
    return licensePlate.empty() && model.empty();
}

std::string Vehicle::getLicensePlate(){
    return licensePlate;
}

std::string Vehicle::getModel() {
    return model;
}

double Vehicle::getParkedTime()
{
    return parkingTime;
}

/*
int Vehicle::getParkedHours() {
    time_t now = time(nullptr);
    return static_cast<int>(difftime(now, parkingTime) / 3600);
}
*/

void Vehicle::setParkingTime(double parkingTime) {
    this->parkingTime = parkingTime;
}
