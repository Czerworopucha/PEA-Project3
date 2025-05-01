//
// Created by czerw on 11/01/2024.
//

#ifndef PEA_PROJEKT_3_GENETICALGORITHM_H
#define PEA_PROJEKT_3_GENETICALGORITHM_H

#include "matrix.h"
#include "chrono"
#include "random"
#include "fstream"
#include "iostream"
#include "vector"
#include "algorithm"
#include "specimen.h"

/*
 * Wspolczynnik krzyzowania = 0.8
 * Wspolczynnik mutacji = 0.01
 */

class geneticAlgorithm {
public:
    int numberOfCities;
    int **distanceMatrix;
    std::vector<int> bestSolution;
    int bestDistance;
    int maxTime;
    int bestSolutionFoundTime;
    std::vector<int> rozwiazania;
    std::vector<int> czasy;
    int populationSize;
    std::vector<double> ranking;
    std::vector<specimen> currentPopulation;
    std::vector<specimen> nextPopulation;
    std::vector<specimen> parents;
    float crossFactor;
    float mutateFactor;
    int mutationChoice;

    geneticAlgorithm(matrix*, int, int ,float ,float ,int);
    ~geneticAlgorithm();
    void runGeneticAlgorithm();
    void startingPopulation();
    void mutate1(specimen*);
    void mutate2(specimen*);
    void cross();
    void displayResults();
    void saveToFile();
    void fitness();

    void tests();
};


#endif //PEA_PROJEKT_3_GENETICALGORITHM_H
