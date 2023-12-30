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

    // Instance method set all entries of the matrix to a given value
    Matrix& setAll(T x) {
        for (T & i : data){
            i = x;
        }
        return *this;
    }
    // Make a static method for every instance method
    static Matrix setAll(const Matrix &m, T x){
        return Matrix(m).setAll(x);
    }

    // Set a specific entry to a given value
    Matrix& set(int row, int column, T value) {
        data[row * noColumns + col] = value;
        return *this;
    }
    static Matrix set(const Matrix &m, int row, int column, T value) {
        return Matrix(m).set(row, column, value);
    }

    // Instance method add 2 matrices
    Matrix& add(constant Matrix &m2) {
        for (int i = 0; i < data.size(); i++) {
            data[i] += m2.data[i];
        }
        return *this;
    }
    
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

    // Multiply two matrices by dot product
    Matrix multiply(constant Matrix &m2) const {
        Matrix result({noRows, m2.noColumns});
        for (int i = 0; i < result.noRows, i++){
            for (int j = 0; j < result.noColumns; j++) {
                for (int order = 0; order < noColumns; order++)
                    result.data[i * result.noColumns + j] = data[i * noColumns + order] * m2.data[m2.noColumns * order + j];
            }
        }
        return result;
    }

    static Matrix multiply(const Matrix &m1, const Matrix &m2) {
        return m1.multiply(m2);
    }

    // Transpose a matrix
    static Matrix (const Matrix &m) {
        Matrix result({m.noRows, m.noColumns});
        if (m.numRows == 1 || m.numCols == 1) { // if matrix is a vector, just swap width/height (copy data)
            res.data = m.data;
            return res;
        }
        for (int i = 0; i < result.noRows; i++) {
            for (int j = 0; j < result.noColumns; j++){
                result.data[result.noColumns * i + j] = m.data[m.noColumns * j + i];
            }
        }
    }

    Matrix& transpose {
        *this = transpose(this);
        return *this;
    }

    // Operation on all elements
    Matrix& opElement (T (*func)(T)) {
        for (int i = 0; i < data.size(); i++) {
            data[i] = func(data[i]);
        }
        return *this;
    }

    static Matrix opElement(const Matrix &m, T (*func)(T)) {
        return Matrix(m).opElement(func);
    }

    // Multiply all elements by a scalar value
    Matrix& multiply (T x) {
        for (T & i : data) {
            i *= x;
        }
        return *this;
    }

    static Matrix multiply (const Matrix &m, const T x) {
        return Matrix(m).multiply(x);
    }

    // Divide all elements by a scalar value using multiply method
    Matrix& divide (T x) {
        return multiply(1/x);
    }

    static Matrix divide(const Matrix &m, T x) {
        return Matrix::multiply(m, 1/x);
    }
};

#endif