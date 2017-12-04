#ifndef CAR_HPP
#define CAR_HPP

#include <string>
#include <iostream>

class Car {
public:
    Car(std::string manu, int num) : manufacturer(manu), numSeats(num) { ++numCars; }
    Car() : Car("unknown", 4) {}
    ~Car(){ --numCars; }
    Car(const Car& c): manufacturer(c.manufacturer), numSeats(c.numSeats) { ++numCars; }
    Car(Car&& c) : manufacturer(std::move(c.manufacturer)), numSeats(std::move(c.numSeats)) { ++numCars; }
    
    Car& operator=(const Car& c);
    Car& operator=(const Car&& c);

    std::string getManufacturer() const{ return manufacturer; }
    unsigned int getNumSeats() const{ return numSeats; }
    static unsigned int getObjectCount() { return numCars; }

private:
	std::string manufacturer;
	unsigned int numSeats;
    static unsigned int numCars;
};

#endif
