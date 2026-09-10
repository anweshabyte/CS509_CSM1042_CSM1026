#include "fastmap.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

static double deflated_dist(
    const vector<vector<double>>& dist,
    const vector<vector<double>>& coords,
    int i, int j,
    int current_dim
) {
    double d_sq = dist[i][j] * dist[i][j];

    for (int dim = 0; dim < current_dim; dim++) {
        double diff = coords[i][dim] - coords[j][dim];
        d_sq -= diff * diff;
    }

    if (d_sq < 0.0) d_sq = 0.0;

    return sqrt(d_sq);
}
static pair<int, int> choose_pivots(
    const vector<vector<double>>& dist,
    const vector<vector<double>>& coords,
    int N,
    int current_dim
) {
    int start = rand() % N;

    int pivot_a = start;
    double max_d = -1.0;
    for (int i = 0; i < N; i++) {
        double d = deflated_dist(dist, coords, start, i, current_dim);
        if (d > max_d) {
            max_d = d;
            pivot_a = i;
        }
    }
    int pivot_b = pivot_a;
    max_d = -1.0;
    for (int i = 0; i < N; i++) {
        double d = deflated_dist(dist, coords, pivot_a, i, current_dim);
        if (d > max_d) {
            max_d = d;
            pivot_b = i;
        }
    }
    if (pivot_a == pivot_b) {
        pivot_b = (pivot_a + 1) % N;
    }

    return {pivot_a, pivot_b};
}
FastMapResult fastmap(
    vector<vector<double>>& dist,
    int N,
    int k
) {
    FastMapResult result;
    result.coordinates.assign(N, vector<double>(k, 0.0));
    result.pivots.resize(k);
    result.execution_time_ms = 0.0;
    srand(42);

    for (int dim = 0; dim < k; dim++) {

    pair<int,int> piv = choose_pivots(
    dist, result.coordinates, N, dim
);
int pivot_a = piv.first;
int pivot_b = piv.second;
result.pivots[dim] = make_pair(pivot_a, pivot_b);

        double d_ab = deflated_dist(
            dist, result.coordinates, pivot_a, pivot_b, dim
        );

        if (d_ab < 1e-10) {
            for (int i = 0; i < N; i++) {
                result.coordinates[i][dim] = 0.0;
            }
            continue;
        }
        for (int i = 0; i < N; i++) {
            double d_ai = deflated_dist(
                dist, result.coordinates, pivot_a, i, dim
            );
            double d_bi = deflated_dist(
                dist, result.coordinates, pivot_b, i, dim
            );

            double x_i = (d_ai*d_ai + d_ab*d_ab - d_bi*d_bi)
                         / (2.0 * d_ab);

            result.coordinates[i][dim] = x_i;
        }
    } 

    return result;
}
bool validate_fastmap_input(
    const vector<vector<double>>& dist,
    int N,
    int k
) {
    if (k <= 0) {
        cerr << "Error: k must be positive. Got k=" << k << endl;
        return false;
    }
    if (k >= N) {
        cerr << "Error: k must be less than N. "
             << "Got k=" << k << ", N=" << N << endl;
        return false;
    }
    if ((int)dist.size() != N) {
        cerr << "Error: Non-square distance matrix." << endl;
        return false;
    }

    const double EPS = 1e-9;

    for (int i = 0; i < N; i++) {
        if ((int)dist[i].size() != N) {
            cerr << "Error: Non-square matrix at row "
                 << i << endl;
            return false;
        }

        for (int j = 0; j < N; j++) {
            if (i == j && fabs(dist[i][j]) > EPS) {
                cerr << "Error: Non-zero diagonal at ("
                     << i << "," << j << ") = "
                     << dist[i][j] << endl;
                return false;
            }
            if (dist[i][j] < -EPS) {
                cerr << "Error: Negative distance at ("
                     << i << "," << j << ") = "
                     << dist[i][j] << endl;
                return false;
            }
            if (fabs(dist[i][j] - dist[j][i]) > EPS) {
                cerr << "Error: Non-symmetric at ("
                     << i << "," << j << "). "
                     << "d[i][j]=" << dist[i][j]
                     << " d[j][i]=" << dist[j][i] << endl;
                return false;
            }
        }
    }

    return true;
}