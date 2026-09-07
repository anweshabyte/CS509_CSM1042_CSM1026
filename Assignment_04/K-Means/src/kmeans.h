#pragma once
#include <vector>

struct KMeansResult {
    std::vector<int> assignment;
    std::vector<std::vector<double>> centroids;
    int iterations = 0;
    bool converged = false;
    double wcss = 0.0;
};

KMeansResult kmeans(const std::vector<std::vector<double>>& points,
                    int K, int maxIterations, double tolerance);
