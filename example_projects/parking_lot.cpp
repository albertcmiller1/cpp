#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class Vehicle {
private:
    int spotSize;

public:
    Vehicle(int spotSize) {
        this->spotSize = spotSize;
    }

    int getSpotSize() {
        return this->spotSize;
    }
};

class Driver {
private:
    int id;
    Vehicle* vehicle;
    int paymentDue;

public:
    Driver(int id, Vehicle* vehicle) {
        this->id = id;
        this->vehicle = vehicle;
        this->paymentDue = 0;
    }

    Vehicle* getVehicle() {
        return this->vehicle;
    }

    int getId() {
        return this->id;
    }

    void charge(int amount) {
        this->paymentDue += amount;
    }
};

class Car : public Vehicle {
public:
    Car() : Vehicle(1) {}
};

class Limo : public Vehicle {
public:
    Limo() : Vehicle(2) {}
};

class SemiTruck : public Vehicle {
public:
    SemiTruck() : Vehicle(3) {}
};

class ParkingFloor {
private:
    vector<int> spots;
    unordered_map<Vehicle*, vector<int>> vehicleMap;

public:
    ParkingFloor(int spotCount) {
        this->spots = vector<int>(spotCount);
        this->vehicleMap = unordered_map<Vehicle*, vector<int>>();
    }

    bool parkVehicle(Vehicle* vehicle) {
        int size = vehicle->getSpotSize();
        int l = 0, r = 0;
        while (r < this->spots.size()) {
            if (this->spots[r] != 0) {
                l = r + 1;
            }
            if (r - l + 1 == size) {
                // we found enough spots, park the vehicle
                for (int k = l; k <= r; k++) {
                    this->spots[k] = 1;
                }
                this->vehicleMap[vehicle] = vector<int>{l, r};
                return true;
            }
            r++;
        }
        return false;
    }

    void removeVehicle(Vehicle* vehicle) {
        vector<int> startEnd = this->vehicleMap[vehicle];
        int start = startEnd[0], end = startEnd[1];
        for (int i = start; i <= end; i++) {
            this->spots[i] = 0;
        }
        this->vehicleMap.erase(vehicle);
    }

    vector<int> getParkingSpots() {
        return this->spots;
    }

    vector<int> getVehicleSpots(Vehicle* vehicle) {
        return this->vehicleMap[vehicle];
    }
};

class ParkingGarage {
private:
    vector<ParkingFloor*> parkingFloors;

public:
    ParkingGarage(int floorCount, int spotsPerFloor) {
        this->parkingFloors = vector<ParkingFloor*>(floorCount);
        for (int i = 0; i < floorCount; i++) {
            this->parkingFloors[i] = new ParkingFloor(spotsPerFloor);
        }
    }

    bool parkVehicle(Vehicle* vehicle) {
        for (ParkingFloor* floor : this->parkingFloors) {
            if (floor->parkVehicle(vehicle)) {
                return true;
            }
        }
        return false;
    }

    bool removeVehicle(Vehicle* vehicle) {
        for (ParkingFloor* floor : this->parkingFloors) {
            if (floor->getVehicleSpots(vehicle).size() != 0) {
                floor->removeVehicle(vehicle);
                return true;
            }
        }
        return false;
    }
};

class ParkingSystem {
private:
    ParkingGarage* parkingGarage;
    int hourlyRate;
    unordered_map<int, int> timeParked;    // map driverId to time that they parked

public:
    ParkingSystem(ParkingGarage* parkingGarage, int hourlyRate) {
        this->parkingGarage = parkingGarage;
        this->hourlyRate = hourlyRate;
        this->timeParked = unordered_map<int, int>();
    }

    bool parkVehicle(Driver* driver) {
        int currentHour = time(0);
        bool isParked = this->parkingGarage->parkVehicle(driver->getVehicle());
        if (isParked) {
            this->timeParked[driver->getId()] = currentHour;
        }
        return isParked;
    }

    bool removeVehicle(Driver* driver) {
        if (this->timeParked.find(driver->getId()) == this->timeParked.end()) {
            return false;
        }
        int currentHour = time(0);
        int timeParked = ceil(currentHour - this->timeParked[driver->getId()]);
        driver->charge(timeParked * this->hourlyRate);

        this->timeParked.erase(driver->getId());
        return this->parkingGarage->removeVehicle(driver->getVehicle());
    }
};

int main() {
    ParkingGarage* parkingGarage = new ParkingGarage(3, 2);
    ParkingSystem* parkingSystem = new ParkingSystem(parkingGarage, 5);

    Driver* driver1 = new Driver(1, new Car());
    Driver* driver2 = new Driver(2, new Limo());
    Driver* driver3 = new Driver(3, new SemiTruck());

    cout << parkingSystem->parkVehicle(driver1) << endl;    // true
    cout << parkingSystem->parkVehicle(driver2) << endl;    // true
    cout << parkingSystem->parkVehicle(driver3) << endl;    // false

    cout << parkingSystem->removeVehicle(driver1) << endl;  // true
    cout << parkingSystem->removeVehicle(driver2) << endl;  // true
    cout << parkingSystem->removeVehicle(driver3) << endl;  // false
}
