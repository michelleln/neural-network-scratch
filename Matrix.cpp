// Header guard
#ifndef MATRIX_H
#define MATRIX_H

// Class template Matrix parametized by type T
template <typename T> class Matrix {
public:
    // Class members
    std::vector<T> data;
    int noRows;
    int noColumns;

    // Default constructor
    Matrix() {
        noRows = 0;
        noColumns = 0;
        data = std::vector<T>(0); // empty vector
    }

    
};

#endif