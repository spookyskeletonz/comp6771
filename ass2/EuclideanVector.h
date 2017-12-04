//AN Sarkar z5061286 comp6771 Advanced C++ assignment 2
#ifndef EUCLIDEANVECTOR_H
#define EUCLIDEANVECTOR_H

#include <iterator>
#include <iostream>
#include <cmath>
#include <initializer_list>
#include <list>
#include <vector>
#include <assert.h>

namespace evec {
    class EuclideanVector {
        public: 
            //constructors
            //constructor for given number of dimensions of equal magnitude
            EuclideanVector(const unsigned int d, const double m) : 
                numDimensions{d}, dimensions{new double[d]} {
                    for(int counter = 0; counter < d; counter++){
                        dimensions[counter] = m;
                    }
                    calculateNorm = true;
                }
            //constructor for only number of dimensions given
            EuclideanVector(const unsigned int d) : EuclideanVector(d, 0.0) {}
            //default constructor
            EuclideanVector() : EuclideanVector(1, 0.0) {}
            //template for iterator constructor
            template <typename T>
            EuclideanVector(T iteratorOne, T iteratorTwo) : 
                numDimensions{static_cast<unsigned int>(std::distance(iteratorOne, iteratorTwo))} 
                {
                    dimensions = new double[numDimensions];
                    int counter= 0;
                    while(iteratorOne != iteratorTwo){
                        dimensions[counter] = *iteratorOne;
                        counter++;
                        ++iteratorOne;
                    }
                }
            //constructor for a list of doubles as magnitudes
            EuclideanVector(const std::initializer_list<double> mags) : EuclideanVector(mags.begin(), mags.end()) {}
            //copy constructor
            EuclideanVector(const EuclideanVector&);
            //move constructor
            EuclideanVector(EuclideanVector&&);
            //deconstructor. deletes dynamically allocated array
            ~EuclideanVector() {delete[] dimensions;}
            
            //overloaded operators
            EuclideanVector& operator=(const EuclideanVector&);
            EuclideanVector& operator=(EuclideanVector&&);
            double& operator[](int);
            double operator[](int) const;
            EuclideanVector& operator+=(const EuclideanVector&);
            EuclideanVector& operator-=(const EuclideanVector&);
            EuclideanVector& operator*=(const double);
            EuclideanVector& operator/=(const double);
            
            //getter for number of dimensions
            unsigned int getNumDimensions() const { return numDimensions; }
            //get the magnitude of a certain dimension           
            double get(const unsigned int) const;
            //gets euclidean norm
            double getEuclideanNorm() const;
            //will create a new euclidean vector as a unit vector
            EuclideanVector createUnitVector() const;
            
            //type conversion
            operator std::vector<double>() const;
            operator std::list<double>() const;

            //friends
            friend bool operator==(const EuclideanVector&, const EuclideanVector&);
            friend bool operator!=(const EuclideanVector&, const EuclideanVector&);
            friend EuclideanVector operator+(const EuclideanVector&, const EuclideanVector&);
            friend EuclideanVector operator-(const EuclideanVector&, const EuclideanVector&);
            friend double operator*(const EuclideanVector&, const EuclideanVector&);
            friend EuclideanVector operator*(const EuclideanVector&, const double);
            friend EuclideanVector operator*(const double, const EuclideanVector&);
            friend EuclideanVector operator/(const EuclideanVector&, const double);
            friend std::ostream& operator<<(std::ostream&, const EuclideanVector&);
        private:
            unsigned int numDimensions;
            double* dimensions;
            mutable bool calculateNorm = true;
            mutable double euclideanNorm = 0;
    };
bool operator==(const EuclideanVector&, const EuclideanVector&);
bool operator!=(const EuclideanVector&, const EuclideanVector&);
EuclideanVector operator+(const EuclideanVector&, const EuclideanVector&);
EuclideanVector operator-(const EuclideanVector&, const EuclideanVector&);
double operator*(const EuclideanVector&, const EuclideanVector&);
EuclideanVector operator*(const EuclideanVector&, const double);
EuclideanVector operator*(const double, const EuclideanVector&);
EuclideanVector operator/(const EuclideanVector&, const double);
std::ostream& operator<<(std::ostream&, const EuclideanVector&);
}

#endif
