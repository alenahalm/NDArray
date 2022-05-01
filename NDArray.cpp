#include "NDArray.h"

NDArray::NDArray(int i, int j) {
    length = i * j;
    if (j == 1) {
        shape.first = 1;
        shape.second = i;
    }
    else {
        shape.first = i;
        shape.second = j;
    }
    A = (int *) malloc((length) * sizeof(int));
}

NDArray::NDArray(std::vector<int> vector, int i, int j) {
    length = i * j;
    if (j == 1) {
        shape.first = 1;
        shape.second = i;
    }
    else {
        shape.first = i;
        shape.second = j;
    }
    A = (int *) malloc((length) * sizeof(int));
    int k = 0;
    for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); ++it) {
        A[k] = *it;
        k++;
    }
}

void NDArray::display() {
    for (int i = 0; i < length; ++i) {
        std::cout << A[i] << " ";
        if (i % shape.second == shape.second - 1) {
            std::cout << std::endl;
        }
    }
}

void NDArray::fill_zero() {
    for (int i = 0; i < length; ++i) {
        A[i] = 0;
    }
}

void NDArray::fill_one() {
    for (int i = 0; i < length; ++i) {
        A[i] = 1;
    }
}

void NDArray::fill_rand() {
    for (int i = 0; i < length; ++i) {
        A[i] = rand();
    }
}

NDArray NDArray::operator+(NDArray other) {
    if (shape.first != other.shape.first || shape.second != other.shape.second){
        throw std::invalid_argument("Both matrices must be the same shape.");
    }
    NDArray sum (shape.first, shape.second);
    for (int i = 0; i < length; ++i) {
        sum.A[i] = A[i] + other.A[i];
    }
    return sum;
}

NDArray NDArray::operator-(NDArray other) {
    if (shape.first != other.shape.first || shape.second != other.shape.second){
        throw std::invalid_argument("Both matrices must be the same shape.");
    }
    NDArray sum (shape.first, shape.second);
    for (int i = 0; i < length; ++i) {
        sum.A[i] = A[i] - other.A[i];
    }
    return sum;
}

NDArray NDArray::operator*(NDArray other) {
    if (shape.first != other.shape.first || shape.second != other.shape.second){
        throw std::invalid_argument("Both matrices must be the same shape.");
    }
    NDArray sum (shape.first, shape.second);
    for (int i = 0; i < length; ++i) {
        sum.A[i] = A[i] * other.A[i];
    }
    return sum;
}

NDArray NDArray::operator/(NDArray other) {
    if (shape.first != other.shape.first || shape.second != other.shape.second){
        throw std::invalid_argument("Both matrices must be the same shape.");
    }
    NDArray sum (shape.first, shape.second);
    for (int i = 0; i < length; ++i) {
        if (other.A[i] != 0) {
            sum.A[i] = A[i] / other.A[i];
        }
        else {
            sum.A[i] = 0;
        }
    }
    return sum;
}

int NDArray::operator()(int i, int j) {
    return A[flatten_indexes(i, j)];
}

int NDArray::operator[](int index) {
    return A[index];
}

NDArray NDArray::operator()(int index) {
    std::vector<int> vec;
    for (int i = flatten_indexes(index, 0); i < flatten_indexes(index, shape.second); ++i) {
        vec.push_back(A[i]);
    }
    return NDArray(vec, 1, shape.second);
}

NDArray NDArray::transpose() {
    std::vector<int> vec;
    int index = 0;
    for (int i = 0; i < length; ++i) {
        if (index % (length - 1) != 0) {
            index %= (length - 1);
        }
        vec.push_back(A[index]);
        index += shape.second;
    }
    NDArray array(vec, shape.second, shape.first);
    return array;
}

NDArray NDArray::matmul(NDArray other) {
    if (shape.second != other.shape.first) {
        throw std::invalid_argument("Number of columns in the first matrix must be equal to the number of lines in the second.");
    }
    NDArray array = *this;
    std::vector<int> vec;
    for (int i = 0; i < shape.first; ++i) {
        for (int j = 0; j < other.transpose().shape.first; ++j) {
            int sum = 0;
            for (int k = 0; k < shape.second; ++k) {
                sum += (array(i)[k] * other.transpose()(j)[k]);
            }
            vec.push_back(sum);
        }
    }
    return NDArray(vec, shape.first, other.shape.second);
}

NDArray NDArray::sum(int index) {
    if (!(index == 0 || index == 1)) {
        throw std::invalid_argument("Axis is out of bound for array");
    }
    std::vector<int> vec;
    NDArray ndArray(0,0);
    if (index == 0) {
        for (int i = 0; i < shape.second; ++i) {
            int sum = 0;
            for (int j = 0; j < shape.first; ++j) {
                sum += A[flatten_indexes(j, i)];
            }
            vec.push_back(sum);
        }
        ndArray.setShape(shape.second, 1);
        ndArray.setA(vec);
    }
    else if (index == 1) {
        for (int i = 0; i < shape.first; ++i) {
            int sum = 0;
            for (int j = 0; j < shape.second; ++j) {
                sum += A[flatten_indexes(i, j)];
            }
            vec.push_back(sum);
        }
        ndArray.setShape(shape.first, 1);
        ndArray.setA(vec);
    }
    return ndArray;
}

NDArray NDArray::min(int index) {
    if (!(index == 0 || index == 1)) {
        throw std::invalid_argument("Axis is out of bound for array");
    }
    std::vector<int> vec;
    NDArray ndArray(0,0);
    if (index == 0) {
        for (int i = 0; i < shape.second; ++i) {
            int min = A[flatten_indexes(0, i)];
            for (int j = 1; j < shape.first; ++j) {
                if (A[flatten_indexes(j, i)] < min) {
                    min = A[flatten_indexes(j, i)];
                }
            }
            vec.push_back(min);
        }
        ndArray.setShape(shape.second, 1);
        ndArray.setA(vec);
    }
    else if (index == 1) {
        for (int i = 0; i < shape.first; ++i) {
            int min = A[flatten_indexes(i, 0)];
            for (int j = 0; j < shape.second; ++j) {
                if (min > A[flatten_indexes(i, j)])
                min = A[flatten_indexes(i, j)];
            }
            vec.push_back(min);
        }
        ndArray.setShape(shape.first, 1);
        ndArray.setA(vec);
    }
    return ndArray;
}

NDArray NDArray::max(int index) {
    if (!(index == 0 || index == 1)) {
        throw std::invalid_argument("Axis is out of bound for array");
    }
    std::vector<int> vec;
    NDArray ndArray(0,0);
    if (index == 0) {
        for (int i = 0; i < shape.second; ++i) {
            int max = A[flatten_indexes(0, i)];
            for (int j = 1; j < shape.first; ++j) {
                if (A[flatten_indexes(j, i)] > max) {
                    max = A[flatten_indexes(j, i)];
                }
            }
            vec.push_back(max);
        }
        ndArray.setShape(shape.second, 1);
        ndArray.setA(vec);
    }
    else if (index == 1) {
        for (int i = 0; i < shape.first; ++i) {
            int max = A[flatten_indexes(i, 0)];
            for (int j = 0; j < shape.second; ++j) {
                if (max < A[flatten_indexes(i, j)])
                    max = A[flatten_indexes(i, j)];
            }
            vec.push_back(max);
        }
        ndArray.setShape(shape.first, 1);
        ndArray.setA(vec);
    }
    return ndArray;
}

int NDArray::flatten_indexes(int i, int j) {
    return i * shape.second + j;
}

int NDArray::getI() {
    return shape.first;
}

int NDArray::getJ() {
    return shape.second;
}

int NDArray::getLength() {
    return length;
}

int NDArray::getValue(int index) {
    return A[index];
}

void NDArray::setShape(int f, int s) {
    length = f * s;
    if (s == 1) {
        shape.first = s;
        shape.second = f;
    }
    else{
        shape.first = f;
        shape.second = s;
    }
}

void NDArray::setA(std::vector<int> vector) {
    A = (int *) malloc((length) * sizeof(int));
    int k = 0;
    for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); ++it) {
        A[k] = *it;
        k++;
    }
}
