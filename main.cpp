#include <iostream>
#include "matrix.h"
#include "geneticAlgorithm.h"
using namespace std;

int main() {

    auto *matrixPointer = new matrix();
    int choice;
    int stopTime = 0;
    int population = 0;
    float mutationFactor = 0;
    float crossingFactor = 0;
    //int crossingMethod = 0;
    int mutationMethod = 0;

    do{
        cout << endl;
        cout << "==== MAIN MENU ====" << endl;
        cout << "1.Wczytaj dane z pliku" << endl;
        cout << "2.Wybor kryterium zatrzymania" << endl;
        cout << "3.Wybor populacji poczatkowej" << endl;
        cout << "4.Wybor wspolczynnika mutacji" << endl;
        cout << "5.Wybor wspolczynnika krzyzowania" << endl;
        cout << "6.Wybor metody krzyzowania - BRAK (tylko 1 metoda dostepna)" << endl;
        cout << "7.Wybor metody mutacji" << endl;
        cout << "8.Algorytm Genetyczny" << endl;
        cout << "0.Exit" << endl;
        cout << "Wybor : ";
        cin >> choice;

        switch (choice){
            case 1:{
                string filename;
                cout << "Podaj nazwe pliku: ";
                cin >> filename;
                matrixPointer->LoadMatrixFromFile(filename);
                matrixPointer->DisplayMatrix();
                break;
            }

            case 2:{
                cout << "Wybierz czas po jakim czasie algorytm ma sie zatrzymac [s]: " << endl;
                cout << "1. 120" << endl;
                cout << "2. 240" << endl;
                cout << "3. 360" << endl;
                cin >> stopTime;
                break;
            }

            case 3:{
                cout << "Podaj wielkosc populacji: " << endl;
                cin >> population;
                break;
            }

            case 4:{
                cout << "Podaj wspolczynnik mutacji - Zalecane [0.0 < wspolczynnik <= 0.1]: " << endl;
                cin >> mutationFactor;
                break;
            }

            case 5:{
                cout << "Podaj wspolczynnik krzyzowania - Zalecane [0.5 <= wspolczynnik <= 1.0]: " << endl;
                cin >> crossingFactor;
                break;
            }

            case 6:{
                cout << "Blad - brak funkcjonalnosci";
                break;
            }

            case 7:{
                cout << "Wybierz metode mutacji: " << endl;
                cout << "1. Zamiana 2 losowych wierzcholkow" << endl;
                cout << "2. Odwrocenie losowego fragmentu sciezki" << endl;
                cin >> mutationMethod;
                break;
            }

            case 8:{
                auto genAlgo = new geneticAlgorithm(matrixPointer, stopTime, population, mutationFactor, crossingFactor, mutationMethod);
                //auto genAlgo = new geneticAlgorithm(matrixPointer, 1, 300, 0.01, 0.8, 1);
                genAlgo->runGeneticAlgorithm();
                genAlgo->displayResults();
                genAlgo->saveToFile();
                break;
            }

            case 9: {
                cout << "Test for 47" << endl;
                matrixPointer->LoadMatrixFromFile("D:/Users/czerw/Downloads/ftv47.atsp/ftv47.atsp");
                cout << "Mutation 1" << endl;
                cout << "Population 100" << endl;
                for (int i = 0; i < 1; i++) {
                    cout << "running " << i << "..." << endl;
                    auto genAlgo = new geneticAlgorithm(matrixPointer, 1, 5000, 0.01, 0.8, 1);
                    genAlgo->runGeneticAlgorithm();
                    //genAlgo->saveToFile();
                }
            }
                /*
                cout<< "Mutation 2" << endl;
                cout << "Population 100" << endl;
                for (int i = 0; i < 5; i++){
                    cout << "running " << i << "..." << endl;
                    auto genAlgo = new geneticAlgorithm(matrixPointer, 1, 100, 0.01, 0.8, 2);
                    genAlgo->runGeneticAlgorithm();
                    genAlgo->saveToFile();
                }

                cout<< "Mutation 1" << endl;
                cout << "Population 200" << endl;
                for (int i = 0; i < 5; i++){
                    cout << "running " << i << "..." << endl;
                    auto genAlgo = new geneticAlgorithm(matrixPointer, 1, 200, 0.01, 0.8, 1);
                    genAlgo->runGeneticAlgorithm();
                    genAlgo->saveToFile();
                }
                cout<< "Mutation 2" << endl;
                cout << "Population 200" << endl;
                for (int i = 0; i < 5; i++){
                    cout << "running " << i << "..." << endl;
                    auto genAlgo = new geneticAlgorithm(matrixPointer, 1, 200, 0.01, 0.8, 2);
                    genAlgo->runGeneticAlgorithm();
                    genAlgo->saveToFile();
                }

                cout<< "Mutation 1" << endl;
                cout << "Population 400" << endl;
                for (int i = 0; i < 5; i++){
                    cout << "running " << i << "..." << endl;
                    auto genAlgo = new geneticAlgorithm(matrixPointer, 1, 400, 0.01, 0.8, 1);
                    genAlgo->runGeneticAlgorithm();
                    genAlgo->saveToFile();
                }
                cout<< "Mutation 2" << endl;
                cout << "Population 400" << endl;
                for (int i = 0; i < 5; i++){
                    cout << "running " << i << "..." << endl;
                    auto genAlgo = new geneticAlgorithm(matrixPointer, 1, 400, 0.01, 0.8, 2);
                    genAlgo->runGeneticAlgorithm();
                    genAlgo->saveToFile();
                }


                cout << "Test for 170" << endl;
                matrixPointer->LoadMatrixFromFile("D:/Users/czerw/Downloads/ftv170.atsp(1)/ftv170.atsp");
                cout<< "Mutation 1" << endl;
                cout << "Population 100" << endl;
                for (int i = 0; i < 5; i++){
                    cout << "running " << i << "..." << endl;
                    auto genAlgo = new geneticAlgorithm(matrixPointer, 2, 100, 0.01, 0.8, 1);
                    genAlgo->runGeneticAlgorithm();
                    genAlgo->saveToFile();
                }
                cout<< "Mutation 2" << endl;
                cout << "Population 100" << endl;
                for (int i = 0; i < 5; i++){
                    cout << "running " << i << "..." << endl;
                    auto genAlgo = new geneticAlgorithm(matrixPointer, 2, 100, 0.01, 0.8, 2);
                    genAlgo->runGeneticAlgorithm();
                    genAlgo->saveToFile();
                }

                cout<< "Mutation 1" << endl;
                cout << "Population 200" << endl;
                for (int i = 0; i < 5; i++){
                    cout << "running " << i << "..." << endl;
                    auto genAlgo = new geneticAlgorithm(matrixPointer, 2, 200, 0.01, 0.8, 1);
                    genAlgo->runGeneticAlgorithm();
                    genAlgo->saveToFile();
                }
                cout<< "Mutation 2" << endl;
                cout << "Population 200" << endl;
                for (int i = 0; i < 5; i++){
                    cout << "running " << i << "..." << endl;
                    auto genAlgo = new geneticAlgorithm(matrixPointer, 2, 200, 0.01, 0.8, 2);
                    genAlgo->runGeneticAlgorithm();
                    genAlgo->saveToFile();
                }

                cout<< "Mutation 1" << endl;
                cout << "Population 400" << endl;
                for (int i = 0; i < 5; i++){
                    cout << "running " << i << "..." << endl;
                    auto genAlgo = new geneticAlgorithm(matrixPointer, 2, 400, 0.01, 0.8, 1);
                    genAlgo->runGeneticAlgorithm();
                    genAlgo->saveToFile();
                }
                cout<< "Mutation 2" << endl;
                cout << "Population 400" << endl;
                for (int i = 0; i < 5; i++){
                    cout << "running " << i << "..." << endl;
                    auto genAlgo = new geneticAlgorithm(matrixPointer, 2, 400, 0.01, 0.8, 2);
                    genAlgo->runGeneticAlgorithm();
                    genAlgo->saveToFile();
                }

                cout << "Test for 403" << endl;
                matrixPointer->LoadMatrixFromFile("D:/Users/czerw/Downloads/rbg403.atsp/rbg403.atsp");
                cout<< "Mutation 1" << endl;
                cout << "Population 100" << endl;
                for (int i = 0; i < 5; i++){
                    cout << "running " << i << "..." << endl;
                    auto genAlgo = new geneticAlgorithm(matrixPointer, 3, 100, 0.01, 0.8, 1);
                    genAlgo->runGeneticAlgorithm();
                    genAlgo->saveToFile();
                }
                cout<< "Mutation 2" << endl;
                cout << "Population 100" << endl;
                for (int i = 0; i < 5; i++){
                    cout << "running " << i << "..." << endl;
                    auto genAlgo = new geneticAlgorithm(matrixPointer, 3, 100, 0.01, 0.8, 2);
                    genAlgo->runGeneticAlgorithm();
                    genAlgo->saveToFile();
                }

                cout<< "Mutation 1" << endl;
                cout << "Population 200" << endl;
                for (int i = 0; i < 5; i++){
                    cout << "running " << i << "..." << endl;
                    auto genAlgo = new geneticAlgorithm(matrixPointer, 3, 200, 0.01, 0.8, 1);
                    genAlgo->runGeneticAlgorithm();
                    genAlgo->saveToFile();
                }
                cout<< "Mutation 2" << endl;
                cout << "Population 200" << endl;
                for (int i = 0; i < 5; i++){
                    cout << "running " << i << "..." << endl;
                    auto genAlgo = new geneticAlgorithm(matrixPointer, 3, 200, 0.01, 0.8, 2);
                    genAlgo->runGeneticAlgorithm();
                    genAlgo->saveToFile();
                }

                cout<< "Mutation 1" << endl;
                cout << "Population 400" << endl;
                for (int i = 0; i < 5; i++){
                    cout << "running " << i << "..." << endl;
                    auto genAlgo = new geneticAlgorithm(matrixPointer, 3, 400, 0.01, 0.8, 1);
                    genAlgo->runGeneticAlgorithm();
                    genAlgo->saveToFile();
                }
                cout<< "Mutation 2" << endl;
                cout << "Population 400" << endl;
                for (int i = 0; i < 5; i++){
                    cout << "running " << i << "..." << endl;
                    auto genAlgo = new geneticAlgorithm(matrixPointer, 3, 400, 0.01, 0.8, 2);
                    genAlgo->runGeneticAlgorithm();
                    genAlgo->saveToFile();
                }
            }
            */

        }

    }while(choice != 0);

    return 0;
}
