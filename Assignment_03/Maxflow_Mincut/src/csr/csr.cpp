#include "csr.h"

#include <fstream>

bool readGraph(
    const std::string& filename,
    std::vector<std::vector<int>>& adjacencyList,
    int& vertices,
    int& source
)
{
    std::ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        return false;
    }

    int edges;
    inputFile >> vertices >> edges;

    adjacencyList.resize(vertices);

    for (int i = 0; i < vertices; i++)
    {
        int vertex;
        int degree;

        inputFile >> vertex >> degree;

        for (int j = 0; j < degree; j++)
        {
            int neighbour;
            inputFile >> neighbour;

            adjacencyList[vertex].push_back(neighbour);
        }
    }

    std::string sourceLabel;
    inputFile >> sourceLabel >> source;

    inputFile.close();

    return true;
}

CSRGraph convertToCSR(const WeightedAdjList& adjacencyList)
{
    CSRGraph graph;

    std::size_t vertices = adjacencyList.size();

    graph.row_ptr.resize(vertices + 1);

    graph.row_ptr[0] = 0;

    for (std::size_t i = 0; i < vertices; i++)
    {
        graph.row_ptr[i + 1] =
            graph.row_ptr[i] + adjacencyList[i].size();
    }

    std::size_t edges = graph.row_ptr[vertices];

    graph.col_idx.reserve(edges);
    graph.values.reserve(edges);

    for (std::size_t i = 0; i < vertices; i++)
    {
        for (const auto& edge : adjacencyList[i])
        {
            graph.col_idx.push_back(edge.first);
            graph.values.push_back(edge.second);
        }
    }

    return graph;
}

CSRGraph convertToCSR(const std::vector<std::vector<int>>& adjacencyList)
{
    CSRGraph graph;

    std::size_t vertices = adjacencyList.size();

    graph.row_ptr.resize(vertices + 1);

    graph.row_ptr[0] = 0;

    for (std::size_t i = 0; i < vertices; i++)
    {
        graph.row_ptr[i + 1] =
            graph.row_ptr[i] + adjacencyList[i].size();
    }

    std::size_t edges = graph.row_ptr[vertices];

    graph.col_idx.reserve(edges);
    graph.values.reserve(edges);

    for (std::size_t i = 0; i < vertices; i++)
    {
        for (int neighbour : adjacencyList[i])
        {
            graph.col_idx.push_back(neighbour);
            graph.values.push_back(1);
        }
    }

    return graph;
}