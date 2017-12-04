#include "car.hpp"

unsigned int Car::numCars = 0;

Car& Car::operator=(const Car& c){
    manufacturer = c.manufacturer;
    numSeats = c.numSeats;
    return *this;
}

Car& Car::operator=(const Car&& c){
    this->manufacturer = std::move(c.manufacturer);
    this->numSeats = std::move(c.numSeats);
    return *this;
}
