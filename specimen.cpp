//
// Created by czerw on 12/01/2024.
//

#include "specimen.h"


specimen::~specimen() = default;


specimen::specimen(std::vector<int> path, int cost){
    specimen::path = path;
    specimen::cost = cost;
}
