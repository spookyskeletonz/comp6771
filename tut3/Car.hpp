#ifndef CAR_HPP
#define CAR_HPP
#include<iostream>
class Car {
public:
	Car(const std::string &s, const unsigned int n) : manufacturer{s}, numSeats{n} {carCount++;}
	Car() : Car("unknown", 4) {}
    ~Car() {carCount--;}
    Car(const Car& c);
    Car(const Car&& c);

    Car& operator=(const Car& c);
    Car& operator=(const Car&& c);

	std::string getManufacturer() const {return manufacturer;}
	unsigned int getNumSeats() const {return numSeats;}
    static unsigned int getCarCount() {return carCount;}

private:
	std::string manufacturer;
	unsigned int numSeats;
    static unsigned int carCount;
};
#endif
