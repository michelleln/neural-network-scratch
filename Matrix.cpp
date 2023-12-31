// Header guard
#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <string>
#include <cmath>

// Class template Matrix parametized by type T
template <typename T>
class Matrix
{
public:
    // Class members
    int noRows;
    int noColumns;
    std::vector<T> data;

    // Default constructor
    Matrix()
    {
        noRows = 0;
        noColumns = 0;
        data = std::vector<T>(0); // empty vector
    }

    // Initiate a matrix with all zero entries
    explicit Matrix(const std::vector<int> size)
    {
        noRows = size[0];
        noColumns = size[1];
        data = std::vector<T>(noRows * noColumns);
    }

    // Initiate a matrix with the same entry
    Matrix(const std::vector<int> size, T temp)
    {
        noRows = size[0];
        noColumns = size[1];
        data = std::vector<T>(noRows * noColumns);
        for (T &i : data)
        { // iterates over every reference i of type T in data
            i = temp;
        }
    }

    // Initiate a matrix with all given entries
    Matrix(const std::vector<int> size, const std::vector<T> &_data)
    {
        noRows = size[0];
        noColumns = size[1];
        data = _data;
    }

    // Instance method set all entries of the matrix to a given value
    Matrix &setAll(T x)
    {
        for (T &i : data)
        {
            i = x;
        }
        return *this;
    }
    // Make a static method for every instance method
    static Matrix setAll(const Matrix &m, T x)
    {
        return Matrix(m).setAll(x);
    }

    // Set a specific entry to a given value
    Matrix& set(int row, int column, T value)
    {
        data[row * noColumns + column] = value;
        return *this;
    }
    
    static Matrix set(const Matrix &m, int row, int column, T value)
    {
        return Matrix(m).set(row, column, value);
    }

    // Instance method add 2 matrices
    Matrix &add(const Matrix &m2)
    {
        for (int i = 0; i < (int)data.size(); i++)
        {
            data[i] += m2.data[i];
        }
        return *this;
    }

    static Matrix add(const Matrix &m1, const Matrix &m2)
    {
        return Matrix(m1).add(m2);
    }

    // Instance method subtract 2 matrices
    Matrix &subtract(const Matrix &m2)
    {
        for (int i = 0; i < data.size(); i++)
        {
            data[i] -= m2.data[i];
        }
        return *this;
    }

    static Matrix subtract(const Matrix &m1, const Matrix &m2)
    {
        return Matrix(m1).subtract(m2);
    }

    // get the value at a specific entry of the matrix
    T get(int row, int col) const
    {
        return data[row * noColumns + col];
    }

    static T get(const Matrix &m, int row, int col)
    {
        return m.get(row, col);
    }

    // Hadamard product (element-wise multiplication) to help computing derivatives by recursion from layers to layers
    Matrix &hProduct(const Matrix &m2)
    {
        for (int i = 0; i < data.size(); i++)
        {
            data[i] *= m2.data[i];
        }
        return *this;
    }

    static Matrix hProduct(const Matrix &m1, const Matrix &m2)
    {
        return Matrix(m1).hProduct(m2);
    }

    // Multiply two matrices by dot product
    Matrix multiply(const Matrix &m2) const
    {
        Matrix result({noRows, m2.noColumns});
        for (int i = 0; i < result.noRows; i++)
        {
            for (int j = 0; j < result.noColumns; j++)
            {
                for (int order = 0; order < noColumns; order++)
                    result.data[i * result.noColumns + j] = data[i * noColumns + order] * m2.data[m2.noColumns * order + j];
            }
        }
        return result;
    }

    static Matrix multiply(const Matrix &m1, const Matrix &m2)
    {
        return m1.multiply(m2);
    }

    // Transpose a matrix
    static Matrix transpose(const Matrix &m)
    {
        Matrix result({m.noColumns, m.noRows});
        if (m.noRows == 1 || m.noColumns == 1)
        { // if matrix is a vector, just swap width/height (copy data)
            result.data = m.data;
            return result;
        }
        for (int i = 0; i < result.noRows; i++)
        {
            for (int j = 0; j < result.noColumns; j++)
            {
                result.data[result.noColumns * i + j] = m.data[m.noColumns * j + i];
            }
        }
        return result;
    }

    Matrix &transpose ()
    {
        *this = transpose(this);
        return *this;
    }

    // Operation on all elements
    Matrix& opElement(T (*func)(T))
    {
        for (int i = 0; i < data.size(); i++)
        {
            data[i] = func(data[i]);
        }
        return *this;
    }

    static Matrix opElement(const Matrix &m, T (*func)(T))
    {
        return Matrix(m).opElement(func);
    }

    // Multiply all elements by a scalar value
    Matrix &multiply(T x)
    {
        for (T &i : data)
        {
            i *= x;
        }
        return *this;
    }

    static Matrix multiply(const Matrix &m, const T x)
    {
        return Matrix(m).multiply(x);
    }

    // Divide all elements by a scalar value using multiply method
    Matrix &divide(T x)
    {
        return multiply(1 / x);
    }

    static Matrix divide(const Matrix &m, T x)
    {
        return Matrix::multiply(m, 1 / x);
    }

    // To string a matrix
    std::string toString() const {
        std::string res;
        for (int row = 0; row < noRows; row++) {
            res += "[";
            for (int col = 0; col < noColumns; col++) {
                res += std::to_string(get(row,col));
                if (col != noColumns - 1) {
                    res += ",";
                }
            }
            res += "]\n";
        }
        return res;
    }

    static std::string toString(const Matrix &m) {
        return m.toString();
    }
};

#endif

