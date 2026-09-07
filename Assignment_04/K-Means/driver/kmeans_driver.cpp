#include "../src/kmeans.h"
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: kmeans.exe <input.txt>\n";
        return 1;
    }

    try {
        std::ifstream in(argv[1]);
        if (!in) throw std::runtime_error("Cannot open input file.");

        int N, D, K;
        if (!(in >> N >> D >> K) || N <= 0 || D <= 0 || K <= 0 || K > N)
            throw std::runtime_error("Invalid N, D or K.");

        std::vector<std::vector<double>> points(N, std::vector<double>(D));
        for (auto& p : points)
            for (double& x : p)
                if (!(in >> x)) throw std::runtime_error("Invalid point data.");

        std::string key;
        int maxIt;
        double tol;
        if (!(in >> key >> maxIt) || key != "MAX_ITERATIONS" || maxIt <= 0)
            throw std::runtime_error("Invalid MAX_ITERATIONS.");
        if (!(in >> key >> tol) || key != "TOLERANCE" || tol <= 0)
            throw std::runtime_error("Invalid TOLERANCE.");

        auto start = std::chrono::steady_clock::now();
        KMeansResult r = kmeans(points, K, maxIt, tol);
        auto stop = std::chrono::steady_clock::now();

        double ms = std::chrono::duration<double, std::milli>(stop-start).count();

        std::cout << std::fixed << std::setprecision(6);
        std::cout << "Algorithm: K-Means Clustering\n";
        std::cout << "K: " << K << "\n";
        std::cout << "Point assignments:\n";
        for (int i = 0; i < N; ++i)
            std::cout << i << " " << r.assignment[i] << "\n";

        std::cout << "Final centroids:\n";
        for (int c = 0; c < K; ++c) {
            std::cout << c << ":";
            for (double x : r.centroids[c]) std::cout << " " << x;
            std::cout << "\n";
        }

        std::cout << "WCSS: " << r.wcss << "\n";
        std::cout << "Iterations: " << r.iterations << "\n";
        std::cout << "Converged: " << (r.converged ? "true" : "false") << "\n";
        std::cout << "Execution time: " << ms << " ms\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
