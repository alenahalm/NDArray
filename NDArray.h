#ifndef NDARRAY_NDARRAY_H
#define NDARRAY_NDARRAY_H

#include <iostream>
#include <vector>

class NDArray {
    int *A;
    std::pair<int, int> shape;
    int length;

public:
    NDArray (int i, int j=1);
    NDArray (std::vector<int> vector, int i, int j=1);
    void display();

    void fill_zero();
    void fill_one();
    void fill_rand();


    NDArray operator+(NDArray other);
    NDArray operator-(NDArray other);
    NDArray operator*(NDArray other);
    NDArray operator/(NDArray other);

    int operator() (int i, int j);
    int operator[] (int index);
    NDArray operator() (int index);

    NDArray transpose();
    NDArray matmul(NDArray other);

    NDArray sum(int index);
    NDArray min(int index);
    NDArray max(int index);

    int flatten_indexes(int i, int j);

    int getI();
    int getJ();
    int getLength();
    int getValue(int index);

    void setShape(int first, int second);
    void setA(std::vector<int> vector);

};


#endif //NDARRAY_NDARRAY_H
