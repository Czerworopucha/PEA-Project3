//
// Created by czerw on 10/01/2024.
//

#ifndef PEA_PROJEKT_3_MATRIX_H
#define PEA_PROJEKT_3_MATRIX_H


#include "fstream"
#include "iostream"

class matrix {
public:
    int numberOfCities;
    int **distanceMatrix;

    matrix();
    ~matrix();
    void LoadMatrixFromFile(const std::string &filename);
    void DisplayMatrix();
};


#endif //PEA_PROJEKT_3_MATRIX_H
