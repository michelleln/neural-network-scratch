// Header guard
#ifndef MATRIX_H
#define MATRIX_H

// Class template Matrix parametized by type T
template <typename T> class Matrix {
public:
    // Class members
    int noRows;
    int noColumns;
    std::vector<T> data;

    // Default constructor
    Matrix() {
        noRows = 0;
        noColumns = 0;
        data = std::vector<T>(0); // empty vector
    }

    // Initiate a matrix with all 0 entries
    explicit Matrix(constant std::vector<int> size) {
        noRows = size[0];
        noColumns = size[1];
        data = std::vector<T>(noRows * noColumns);
    }

    // Initiate a matrix with the same entry
    explicit Matrix(constant std::vector<int> size, T temp) {
        noRows = size[0];
        noColumns = size[1];
        data = std::vector<T> (noRows * noColumns);
        for (T & i : data) { // iterates over every reference i of type T in data
            i = temp;
        } 
    }

    // Initiate a matrix with all given entries
    explicit Matrix(constant std::vector<int> size, constant std::vector<T> &_data) {
        noRows = size[0];
        noColumns = size[1];
        data = _data;
    }

    // Instance method add 2 matrices
    Matrix& add(constant Matrix &m2) {
        for (int i = 0; i < data.size(); i++) {
            data[i] += m2.data[i];
        }
        return *this;
    }
    // Make a static method for every instance method
    static Matrix add(constant Matrix &m1, constant Matrix &m2) {
        return Matrix(m1).add(m2);
    }

    // Hadamard product (element-wise multiplication) to help computing derivatives by recursion from layers to layers
    Matrix& hProduct(constant Matrix &m2) {
        for (int i = 0; i < data.size(); i++) {
            data[i] *= m2.data[i];
        }
        return *this;
    }

    static Matrix hProduct(constant Matrix &m1, constant Matrix &m2) {
        return Matrix(m1).hProduct(m2);
    }
};

#endif