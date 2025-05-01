//
// Created by czerw on 10/01/2024.
//

#include "matrix.h"

matrix::matrix() {
    numberOfCities = 0;
    distanceMatrix = nullptr;
}

matrix::~matrix() {
    for (int i = 0; i < numberOfCities; i++) {
        delete[] distanceMatrix[i];

    }
    delete[] distanceMatrix;
}

/* Wczytywanie grafu z pliku .atsp jako macierz sąsiedztwa
 *
 */
void matrix::LoadMatrixFromFile(const std::string &filename) {

    std::ifstream file(filename);
    if (file.good()) {
        std::string data;

        do {
            file >> data;
        } while (data != "DIMENSION:");
        file >> numberOfCities;

        do {
            file >> data;
        } while (data != "EDGE_WEIGHT_SECTION");

        distanceMatrix = new int *[numberOfCities];
        for (int i = 0; i < numberOfCities; i++) {
            distanceMatrix[i] = new int[numberOfCities];
        }

        int distance;
        for (int i = 0; i < numberOfCities; i++) {
            for (int j = 0; j < numberOfCities; j++) {
                file >> distance;
                distanceMatrix[i][j] = distance;
            }
        }
        file.close();
    } else {
        std::cout << "Blad wczytywania z pliku" << std::endl;
    }
}

// Wyswietlanie wczytanej macierzy
void matrix::DisplayMatrix() {
    std::cout << "Ilosc miast: " << numberOfCities << std::endl;
    for (int i = 0; i < numberOfCities; i++) {
        for (int j = 0; j < numberOfCities; j++) {
            std::cout << "[" << distanceMatrix[i][j] << "] ";
        }
        std::cout << std::endl;
    }
}
