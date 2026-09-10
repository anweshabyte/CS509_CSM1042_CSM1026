#include "kmeans.h"
#include <cmath>
#include <limits>
#include <stdexcept>

static double sqDist(const std::vector<double>& a,
                     const std::vector<double>& b) {
    double s = 0.0;
    for (size_t j = 0; j < a.size(); ++j) {
        double d = a[j] - b[j];
        s += d * d;
    }
    return s;
}

KMeansResult kmeans(const std::vector<std::vector<double>>& points,
                    int K, int maxIterations, double tolerance) {
    if (points.empty() || K <= 0 || K > static_cast<int>(points.size()))
        throw std::invalid_argument("Invalid N or K.");

    const int N = static_cast<int>(points.size());
    const int D = static_cast<int>(points[0].size());

    KMeansResult r;
    r.assignment.assign(N, -1);
    r.centroids.assign(points.begin(), points.begin() + K);

    std::vector<int> previous(N, -1);

    for (int it = 1; it <= maxIterations; ++it) {
        bool changed = false;

        for (int i = 0; i < N; ++i) {
            int best = 0;
            double bestDist = sqDist(points[i], r.centroids[0]);

            for (int c = 1; c < K; ++c) {
                double dist = sqDist(points[i], r.centroids[c]);
                if (dist < bestDist) {
                    bestDist = dist;
                    best = c;
                }
            }

            r.assignment[i] = best;
            if (r.assignment[i] != previous[i]) changed = true;
        }

        std::vector<std::vector<double>> sums(K, std::vector<double>(D, 0.0));
        std::vector<int> count(K, 0);

        for (int i = 0; i < N; ++i) {
            int c = r.assignment[i];
            ++count[c];
            for (int j = 0; j < D; ++j) sums[c][j] += points[i][j];
        }

        double maxShift = 0.0;
        for (int c = 0; c < K; ++c) {
            if (count[c] == 0) continue;
            std::vector<double> next = r.centroids[c];
            for (int j = 0; j < D; ++j) next[j] = sums[c][j] / count[c];
            maxShift = std::max(maxShift, std::sqrt(sqDist(next, r.centroids[c])));
            r.centroids[c] = std::move(next);
        }

        previous = r.assignment;
        r.iterations = it;

        if (!changed || maxShift <= tolerance) {
            r.converged = true;
            break;
        }
    }

    r.wcss = 0.0;
    for (int i = 0; i < N; ++i)
        r.wcss += sqDist(points[i], r.centroids[r.assignment[i]]);

    return r;
}
