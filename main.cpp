#include <iostream>
#include "NDArray.h"

int main() {

    NDArray ar(4, 5);
    std::cout << "An array 4x5 filled with zeroes" << std::endl;
    ar.fill_zero();
    ar.display();
    std::cout << std::endl;
    std::cout << "An array 4x5 filled with ones" << std::endl;
    ar.fill_one();
    ar.display();
    std::cout << std::endl;
    std::cout << "An array 4x5 filled with random numbers" << std::endl;
    ar.fill_rand();
    ar.display();

    std::cout << std::endl;
    std::cout << "Array 1: " << std::endl;
    NDArray ar1({1,2,3,4,5,6},2,3);
    ar1.display();
    std::cout << std::endl;
    std::cout << "Array 2: " << std::endl;
    NDArray ar2({6,5,4,3,2,1},2,3);
    ar2.display();
    std::cout << std::endl;
    std::cout << "Array 1 + Array 2:" << std::endl;
    (ar1 + ar2).display();
    std::cout << std::endl;
    std::cout << "Array 1 - Array 2:" << std::endl;
    (ar1 - ar2).display();
    std::cout << std::endl;
    std::cout << "Array 1 * Array 2:" << std::endl;
    (ar1 * ar2).display();
    std::cout << std::endl;
    std::cout << "Array 1 / Array 2:" << std::endl;
    (ar1 / ar2).display();

    std::cout << std::endl << "Array 1 transposed:" << std::endl;
    ar1.transpose().display();

    ar2 = NDArray({1,2,3,4,5,6},3,2);
    std::cout << std::endl << "Redefinition of Array 2:" << std::endl;
    ar2.display();

    std::cout << std::endl << "Matmul:" << std::endl;
    ar1.matmul(ar2).display();

    std::cout << std::endl << "Array filled with random nums sum(0):" << std::endl;
    ar.sum(0).display();
    std::cout << std::endl << "Array filled with random nums min(0):" << std::endl;
    ar.min(0).display();
    std::cout << std::endl << "Array filled with random nums max(0):" << std::endl;
    ar.max(0).display();
}
