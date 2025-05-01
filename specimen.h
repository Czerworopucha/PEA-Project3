//
// Created by czerw on 12/01/2024.
//

#ifndef PEA_PROJEKT_3_SPECIMEN_H
#define PEA_PROJEKT_3_SPECIMEN_H


#include <vector>

class specimen {
public:
    std::vector<int> path;
    int cost;

    specimen(std::vector<int>, int);
    ~specimen();

};


#endif //PEA_PROJEKT_3_SPECIMEN_H
