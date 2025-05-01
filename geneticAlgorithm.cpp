//
// Created by czerw on 11/01/2024.
//

#include "geneticAlgorithm.h"

geneticAlgorithm::geneticAlgorithm(matrix *matrixPointer, int stopTime, int population, float mutationFactor, float crossingFactor, int mutationMethod) {
    numberOfCities = matrixPointer->numberOfCities;
    distanceMatrix = matrixPointer->distanceMatrix;

    if (stopTime == 1) {
        maxTime = 120;
    } else if (stopTime == 2) {
        maxTime = 240;
    } else if (stopTime == 3) {
        maxTime = 360;
    } else {
        if (numberOfCities < 150) {
            maxTime = 120;
        } else if (numberOfCities < 250) {
            maxTime = 240;
        } else {
            maxTime = 360;
        }
    }

    populationSize = population;
    bestDistance = INT_MAX;
    bestSolutionFoundTime = 0;

    crossFactor = crossingFactor;
    mutateFactor = mutationFactor;
    mutationChoice = mutationMethod;

}

geneticAlgorithm::~geneticAlgorithm() {
    for (int i = 0; i < numberOfCities; i++) {
        delete[] distanceMatrix[i];

    }
    delete[] distanceMatrix;
}

/*
 * Wspolczynnik krzyzowania = 0.8
 * Wspolczynnik mutacji = 0.01
 * 1.Populacja startowa
 * 2.Fitness - po dlugosci sciezki
 * 3.Selection
 * 4.Crossover
 * 5.Mutacja
 * zapisanie nowej populacji jako aktualnej
 * petla od kroku 2.
 */

void geneticAlgorithm::runGeneticAlgorithm() {
    startingPopulation();
    std::chrono::time_point breakPoint = std::chrono::system_clock::now() + std::chrono::duration_cast<std::chrono::seconds>(std::chrono::duration<int>(maxTime));
    std::random_device rd;
    std::mt19937 generate(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    auto startTime = std::chrono::system_clock::now();

    do{
        fitness();
        //Zapisanie najlepszego rozwiazania
        if(currentPopulation[currentPopulation.size()-1].cost < bestDistance){
            bestSolution = currentPopulation[currentPopulation.size()-1].path;
            bestDistance = currentPopulation[currentPopulation.size()-1].cost;
            bestSolutionFoundTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - startTime).count();
            rozwiazania.push_back(bestDistance);
            czasy.push_back(bestSolutionFoundTime);
        }
        //Selection + cross
        for (int i = 0; i < populationSize - 1; i++) {
            if(crossFactor > dist(generate)) {
                cross();
            }
            else{
                nextPopulation.push_back(currentPopulation[i]);
            }
        }
        //Mutation
        if(mutationChoice == 1) {
            for (int i = 0; i < nextPopulation.size(); i++) {
                if (mutateFactor > dist(generate)) {
                    mutate1(&nextPopulation[i]);
                }
            }
        }
        else if(mutationChoice == 2){
            for (int i = 0; i < nextPopulation.size(); i++) {
                if (mutateFactor > dist(generate)) {
                    mutate2(&nextPopulation[i]);
                }
            }
        }
        //Elitism
        nextPopulation.push_back(currentPopulation[currentPopulation.size()-1]);
        //Zapisanie nowej populacji jako aktualnej
        currentPopulation = std::move(nextPopulation);
        nextPopulation.clear();
        //nextPopulation.shrink_to_fit();
        parents.clear();
        //parents.shrink_to_fit();

    }while ((breakPoint - std::chrono::system_clock::now()).count() > 0);
}

void geneticAlgorithm::startingPopulation() {
    for (int i = 0; i < populationSize; i++){
        std::vector<int> sciezka(numberOfCities);
        //wypelnienie wektora wszystkimi wierzcholkami
        std::iota(sciezka.begin(), sciezka.end(), 0);
        //random shuffle
        std::random_device rd;
        std::mt19937 generate(rd());
        std::shuffle(sciezka.begin(), sciezka.end(), generate);
        //dodanie wierzcholka startowego na koniec (cykl hamiltona)
        sciezka.push_back(sciezka[0]);
        //obliczenie kosztu
        int koszt = 0;
        for (int j = 0; j < sciezka.size() - 1; j++){
            koszt += distanceMatrix[sciezka[j]][sciezka[j+1]];
        }
        //dodanie do populacji
        currentPopulation.emplace_back(sciezka, koszt);

        if(koszt < bestDistance){
            bestSolution = sciezka;
            bestDistance = koszt;
        }
    }
    rozwiazania.push_back(bestDistance);
    czasy.push_back(bestSolutionFoundTime);
    displayResults();
}

///Swap random 2
void geneticAlgorithm::mutate1(specimen* osobnik) {
    std::random_device rng;
    std::mt19937 gen(rng());
    std::uniform_int_distribution<> distribution(0, osobnik->path.size() - 2);

    int swap1 = distribution(gen);
    int swap2 = distribution(gen);
    //Zabezpieczenie zeby nie wylosowaly sie 2 te same
    while(swap2 == swap1){
        swap2 = distribution(gen);
    }

    osobnik->path.pop_back();
    //zamiana 2 losowych wierzcholkow
    std::vector<int> tempOsobnik = osobnik->path;
    osobnik->path[swap1] = tempOsobnik[swap2];
    osobnik->path[swap2] = tempOsobnik[swap1];
    //
    osobnik->path.push_back(osobnik->path[0]);

    //ponowne obliczenie kosztu sciezki
    int koszt = 0;
    for (int j = 0; j < osobnik->path.size() - 1; j++){
        koszt += distanceMatrix[osobnik->path[j]][osobnik->path[j+1]];
    }
    osobnik->cost = koszt;
}

///Reverse section
void geneticAlgorithm::mutate2(specimen* osobnik) {
    std::random_device rng;
    std::mt19937 gen(rng());
    std::uniform_int_distribution<> distribution(0, osobnik->path.size() - 2);

    int start = distribution(gen);
    int end = distribution(gen);
    //Zabezpieczenie zeby nie wylosowaly sie 2 te same
    while(end == start){
        end = distribution(gen);
    }
    if (start > end) {
        std::swap(start, end);
    }
    //
    osobnik->path.pop_back();
    //
    std::vector<int> tempSegment;
    tempSegment.assign(osobnik->path.begin()+start, osobnik->path.begin()+end);
    int i = tempSegment.size() - 1;
    do{
        osobnik->path[start] = tempSegment[i];
        start++;
        i--;
    }while(start < end);
    //
    osobnik->path.push_back(osobnik->path[0]);

    //ponowne obliczenie kosztu sciezki
    int koszt = 0;
    for (int j = 0; j < osobnik->path.size() - 1; j++){
        koszt += distanceMatrix[osobnik->path[j]][osobnik->path[j+1]];
    }
    osobnik->cost = koszt;
}

///Order Crossover
void geneticAlgorithm::cross() {
    std::random_device rng;
    std::mt19937 generate(rng());
    std::uniform_int_distribution<> distribution(0, parents.size() - 2);

    int r1 = distribution(generate);
    int r2 = distribution(generate);

    //kopie wektorow
    std::vector rodzic1 = parents[r1].path;
    std::vector rodzic2 = parents[r2].path;
    rodzic1.pop_back();
    rodzic2.pop_back();

    std::vector<int> dziecko(numberOfCities, INT_MAX);

    //wybor przedzialu z rodzic1
    std::uniform_int_distribution<> distribution2(0, rodzic1.size() - 2);
    int start = distribution2(generate);
    int end;
    do {
        end = distribution2(generate);
    }while (end == start);
    if (start > end) {
        std::swap(start, end);
    }

    //skopiowanie wybranego przedzialu z rodzic1 do dziecka
    //dziecko.assign(rodzic1.begin() + start, rodzic1.begin() + end);
    for (int i = start; i <= end; i++){
        dziecko[i] = rodzic1[i];
    }

    //wypelnienie reszty dziecka w kolejnosci unikalnych wierzcholkow z rodzic2
    for(int i = 0; i < rodzic2.size(); i++){
        int gen = rodzic2[i];
        bool missing = true;
        for (int j = 0; j < dziecko.size(); j++){
            if (dziecko[j] == gen){
                missing = false;
                break;
            }
        }
        if(missing){
            for (int j = 0; j < dziecko.size(); j++){
                if(dziecko[j] == INT_MAX){
                    dziecko[j] = gen;
                    break;
                }
            }
        }
    }

    dziecko.push_back(dziecko[0]);
    int koszt = 0;
    for (int j = 0; j < dziecko.size() - 1; j++){
        koszt += distanceMatrix[dziecko[j]][dziecko[j+1]];
    }
    //dodanie do nowej populacji
    nextPopulation.emplace_back(dziecko, koszt);
}

void geneticAlgorithm::displayResults() {
    std::cout << std::endl;
    std::cout << "Sciezka:" << std::endl;
    for (int i = 0; i < bestSolution.size(); i++){
        std::cout << "[" << bestSolution[i] << "] ";
    }
    std::cout << std::endl;
    std::cout << "Koszt: " << bestDistance << std::endl;
    std::cout << "Czas po ktorym znaleziono najlepsze rozwiazanie: " << bestSolutionFoundTime << std::endl;
}

void geneticAlgorithm::saveToFile() {
    std::ofstream fileName;
    fileName.open("wynik.txt", std::ios::app);
    fileName << "--------------------\n";
    fileName << "Miasta: " << numberOfCities << "\n";
    fileName << "Populacja: " << populationSize << "\n";
    fileName << "Best: " << bestDistance << "\n";
    fileName << "Best path: " << "\n";
    for (int i = 0; i < bestSolution.size(); i++) {
        fileName << " " << bestSolution[i];
    }
    fileName << "\n";
    fileName << "Best time: " << bestSolutionFoundTime << "\n";
    fileName << "\n";
    fileName.close();

    std::ofstream fileName1;
    fileName1.open("czasy2.txt", std::ios::app);
    fileName1 << "--------------------\n";
    for(int i = 0; i < rozwiazania.size(); i++){
        fileName1 << rozwiazania[i] << "," << czasy[i] << "\n";
    }
    fileName1 << "\n";
    fileName1.close();
}

void geneticAlgorithm::tests() {

}

///Rank selection
void geneticAlgorithm::fitness() {
    //sortowanie populacji po koszcie malejaco (najgorsze na poczatku)
    std::sort(currentPopulation.begin(), currentPopulation.end(), [](const specimen& lhs, const specimen& rhs){return lhs.cost > rhs.cost;});

    //dodanie osobnikow do vektora selekcji rodzicow - ilosc zalezna od rangi
    for (int i = 0; i < currentPopulation.size(); i++){
        for (int j = 0; j < i+1; j++) {
            parents.push_back(currentPopulation[i]);
        }
    }
    //losowe przetasowanie tablicy rodzicow
    std::random_device rd;
    std::mt19937 generate(rd());
    std::shuffle(parents.begin(), parents.end(), generate);
}
