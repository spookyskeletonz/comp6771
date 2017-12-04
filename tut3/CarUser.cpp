#include "Car.hpp"

int main() {
        Car one;
            Car two{"Toyota",5};
                
                    std::cout << Car::getCarCount() << std::endl;
                        
                            Car* three = new Car{};
                                std::cout << Car::getCarCount() << std::endl;
                                    delete three;
                                        std::cout << Car::getCarCount() << std::endl;
                                            
                                                Car four{two};
                                                    std::cout << Car::getCarCount() << std::endl;
                                                        
                                                            Car five = std::move(one);
                                                                std::cout << Car::getCarCount() << std::endl;
                                                                    
                                                                        Car six{std::move(two)};
                                                                            std::cout << Car::getCarCount() << std::endl;
                                                                                
                                                                                    four = six;
                                                                                        std::cout << Car::getCarCount() << std::endl;
                                                                                            
                                                                                                five = std::move(six);
                                                                                                    std::cout << Car::getCarCount() << std::endl;
}
