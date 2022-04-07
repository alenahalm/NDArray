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
    for (int k = 0; k < vector.size(); ++k) {
        A[k] = vector[k];
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
    if (shape == other.shape) {
        NDArray sum (shape.first, shape.second);
        for (int i = 0; i < length; ++i) {
            sum.A[i] = A[i] + other.A[i];
        }
        return sum;
    }
}

NDArray NDArray::operator-(NDArray other) {
    if (shape == other.shape) {
        NDArray sum (shape.first, shape.second);
        for (int i = 0; i < length; ++i) {
            sum.A[i] = A[i] - other.A[i];
        }
        return sum;
    }
}

NDArray NDArray::operator*(NDArray other) {
    if (shape == other.shape) {
        NDArray sum (shape.first, shape.second);
        for (int i = 0; i < length; ++i) {
            sum.A[i] = A[i] * other.A[i];
        }
        return sum;
    }
}

NDArray NDArray::operator/(NDArray other) {
    if (shape == other.shape) {
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
    NDArray array = *this;
    if (shape.first != 1 && other.shape.first != 1 &&
            shape.second == other.shape.first) {
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
}

NDArray NDArray::sum(int index) {
    std::vector<int> vec;
    if (index == 0) {
        for (int i = 0; i < shape.second; ++i) {
            int sum = 0;
            for (int j = 0; j < shape.first; ++j) {
                sum += A[flatten_indexes(j, i)];
            }
            vec.push_back(sum);
        }
        return NDArray(vec, shape.second);
    }
    else if (index == 1) {
        for (int i = 0; i < shape.first; ++i) {
            int sum = 0;
            for (int j = 0; j < shape.second; ++j) {
                sum += A[flatten_indexes(i, j)];
            }
            vec.push_back(sum);
        }
        return NDArray (vec, shape.first);
    }
}

NDArray NDArray::min(int index) {
    std::vector<int> vec;
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
        return NDArray(vec, shape.second);
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
        return NDArray (vec, shape.first);
    }
}

NDArray NDArray::max(int index) {
    std::vector<int> vec;
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
        return NDArray(vec, shape.second);
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
        return NDArray (vec, shape.first);
    }
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
