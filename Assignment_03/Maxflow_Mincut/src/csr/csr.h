#ifndef CSR_H
#define CSR_H

#include <vector>
#include <utility>
#include <string>

struct CSRGraph
{
    std::vector<int> row_ptr;
    std::vector<int> col_idx;
    std::vector<int> values;
};

using WeightedAdjList = std::vector<std::vector<std::pair<int, int>>>;

// Read unweighted graph from file
bool readGraph(
    const std::string& filename,
    std::vector<std::vector<int>>& adjacencyList,
    int& vertices,
    int& source
);

// Weighted adjacency list → CSR
CSRGraph convertToCSR(const WeightedAdjList& adjacencyList);

// Unweighted adjacency list → CSR
CSRGraph convertToCSR(const std::vector<std::vector<int>>& adjacencyList);

#endif