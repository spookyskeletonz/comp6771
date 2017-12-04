//AN Sarkar z5061286 comp6771 Advanced C++ assignment 2
#include "EuclideanVector.h"
#include <vector>
#include <cmath>
#include <list>
#include <iostream>
#include <assert.h>

//copy constructor
evec::EuclideanVector::EuclideanVector(const evec::EuclideanVector& e){
    *this = e;
}

//move constructor
evec::EuclideanVector::EuclideanVector(EuclideanVector&& e): numDimensions{e.numDimensions}, dimensions{std::move(e.dimensions)} {
    e.dimensions = nullptr;    
}

//copy assignment operator
evec::EuclideanVector& evec::EuclideanVector::operator=(const evec::EuclideanVector& e){
    numDimensions = e.numDimensions;
    dimensions = new double[numDimensions];
    for(int counter = 0; counter < numDimensions; counter++){
        dimensions[counter] = e.dimensions[counter]; 
    }
    calculateNorm = true;
    return *this;
}

//move assignment operator
evec::EuclideanVector& evec::EuclideanVector::operator=(EuclideanVector&& e){
    if (this != &e){
        numDimensions = std::move(e.numDimensions);
        dimensions = std::move(e.dimensions);
        e.dimensions = nullptr;
        calculateNorm = true;
    }
    return *this;
}

//[] operator overload for setting via EuclideanVector[] = x
double& evec::EuclideanVector::operator[](int index){
    assert((index < numDimensions) && (index >= 0));
    calculateNorm = true;
    return dimensions[index];
}

//[] operator overload for getting via double x = EuclideanVector[]
double evec::EuclideanVector::operator[](int index) const{
    assert((index < numDimensions) && (index >= 0));
    return dimensions[index];
}

//compound addition assignment operator
evec::EuclideanVector& evec::EuclideanVector::operator+=(const evec::EuclideanVector& e){
    assert(e.numDimensions == numDimensions);
    for(int counter = 0; counter < numDimensions; counter++){
        dimensions[counter] += e.dimensions[counter];
    }
    calculateNorm = true;
    return *this;
}

//compound subtraction assignment operator
evec::EuclideanVector& evec::EuclideanVector::operator-=(const evec::EuclideanVector& e){
    assert(e.numDimensions == numDimensions);
    for(int counter = 0; counter < numDimensions; counter++){
        dimensions[counter] -= e.dimensions[counter];
    }
    calculateNorm = true;
    return *this;
}

//compound multiplication assignment operator
evec::EuclideanVector& evec::EuclideanVector::operator*=(const double multiplier){
    for(int counter = 0; counter < numDimensions; counter++){
        dimensions[counter] *= multiplier;
    }
    calculateNorm = true;
    return *this;
}

//compound division assignment operator
evec::EuclideanVector& evec::EuclideanVector::operator/=(const double divisor){
    for(int counter = 0; counter < numDimensions; counter++){
        dimensions[counter] /= divisor;
    }
    calculateNorm = true;
    return *this;
}

//get function, to return the magnitude at the index asked. eg. double x = e.get(1)
double evec::EuclideanVector::get(const unsigned int index) const{
    assert(index >= 0 && index < numDimensions);
    return dimensions[index];
}

//getEuclideanNorm function. calculates euclidean norm if we have changed the magnitudes, otherwise will return stored norm. will store calculated norm
double evec::EuclideanVector::getEuclideanNorm() const{
    if(calculateNorm == true){
        double sum = 0;
        for(int counter = 0; counter < numDimensions; counter++){
            sum += dimensions[counter]*dimensions[counter];
        }
        euclideanNorm = sqrt(sum);
        calculateNorm = false;
    }
    return euclideanNorm;
}

//will create a unit vector of this. eg EuclideanVector unit = e.createUnitVector()
evec::EuclideanVector evec::EuclideanVector::createUnitVector() const{
    evec::EuclideanVector unit{*this};
    unit /= getEuclideanNorm();
    return unit;
}

//for type conversion to a vector of doubles
evec::EuclideanVector::operator std::vector<double>() const{
    std::vector<double> v;
    for(int counter = 0; counter < numDimensions; counter++){
        v.push_back(dimensions[counter]);
    }
    return v;
}

//for type conversion to a list of doubles
evec::EuclideanVector::operator std::list<double>() const{
    std::list<double> l;
    for(int counter = 0; counter < numDimensions; counter++){
        l.push_back(dimensions[counter]);
    }
    return l;
}

//equality operator overload
bool evec::operator==(const evec::EuclideanVector& lhs, const evec::EuclideanVector& rhs){
    if(lhs.numDimensions == rhs.numDimensions){
        for(int counter = 0; counter < lhs.numDimensions; counter++){
            if(lhs.dimensions[counter] != rhs.dimensions[counter]) return false;
        }
        return true;
    } else return false;
}

//inequality operator overload
bool evec::operator!=(const evec::EuclideanVector& lhs, const evec::EuclideanVector& rhs){
    return !(lhs==rhs);
}

//addition operator overload
evec::EuclideanVector evec::operator+(const evec::EuclideanVector& lhs, const evec::EuclideanVector& rhs){
    evec::EuclideanVector sum = lhs;
    sum += rhs;
    return sum;
}

//subtraction operator overload
evec::EuclideanVector evec::operator-(const evec::EuclideanVector& lhs, const evec::EuclideanVector& rhs){
    evec::EuclideanVector diff = lhs;
    diff -= rhs;
    return diff;
}

//multiplication operator overload for calculating dot product of two euclidean vectors
double evec::operator*(const evec::EuclideanVector& lhs, const evec::EuclideanVector& rhs){
    assert(lhs.numDimensions == rhs.numDimensions);
    double dotprod = 0;
    for(int counter = 0; counter < lhs.numDimensions; counter++){
        dotprod += lhs.dimensions[counter] * rhs.dimensions[counter];
    }
    return dotprod;
}

//multiplication operator overload
evec::EuclideanVector evec::operator*(const evec::EuclideanVector& lhs, const double multiplier){
    evec::EuclideanVector product = lhs;
    product *= multiplier;
    return product;
}

//same as prev function
evec::EuclideanVector evec::operator*(const double multiplier, const evec::EuclideanVector& rhs){
    EuclideanVector product = rhs;
    product *= multiplier;
    return product;
}

//division operator overload
evec::EuclideanVector evec::operator/(const evec::EuclideanVector& lhs, const double divisor){
    evec::EuclideanVector result = lhs;
    result /= divisor;
    return result;
}

//<< operator overload
std::ostream& evec::operator<<(std::ostream& output, const EuclideanVector& e){
    output << "[";
    if(e.dimensions == nullptr){
        output << "]";
        return output;
    }
    for(int counter = 0; counter < e.numDimensions; counter++){
        if(counter != 0) output << " ";
        output << e.dimensions[counter];
    }
    output << "]";
    return output;
}
