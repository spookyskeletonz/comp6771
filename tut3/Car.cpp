#include "Car.hpp"
#include<iostream>
unsigned int Car::carCount = 0;

Car::Car(const Car& c){
    manufacturer = c.manufacturer;
    numSeats = c.numSeats;
    carCount++;
}

Car::Car(const Car&& c){
    manufacturer = std::move(c.manufacturer);
    numSeats = std::move(c.numSeats);
    carCount++;
}

Car& Car::operator=(const Car& c){
    manufacturer = c.manufacturer;
    numSeats = c.numSeats;
    return *this;
}

Car& Car::operator=(const Car&& c){
    manufacturer = std::move(c.manufacturer);
    numSeats = std::move(c.numSeats);
    return *this;
}
