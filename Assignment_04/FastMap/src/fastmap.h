// src/fastmap.h
// FastMap Algorithm - Header File
// Assignment 4 - Buddy Task (FastMap)

#ifndef FASTMAP_H
#define FASTMAP_H

#include <vector>
#include <utility>

struct FastMapResult {
    std::vector<std::vector<double>> coordinates;
    std::vector<std::pair<int, int>> pivots;
    double execution_time_ms;
};

FastMapResult fastmap(
    std::vector<std::vector<double>>& dist,
    int N,
    int k
);

bool validate_fastmap_input(
    const std::vector<std::vector<double>>& dist,
    int N,
    int k
);

#endif