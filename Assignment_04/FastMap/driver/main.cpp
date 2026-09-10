#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <string>
#include <cmath>
#include "../src/fastmap.h"

using namespace std;
using namespace chrono;

bool read_input(
    const string& filename,
    vector<vector<double>>& dist,
    int& N,
    int& k
) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Cannot open file '"
             << filename << "'" << endl;
        cerr << "Check if the file path is correct." << endl;
        return false;
    }

    if (!(file >> N >> k)) {
        cerr << "Error: Cannot read N and K." << endl;
        return false;
    }

    if (N <= 0) {
        cerr << "Error: N must be positive. Got N="
             << N << endl;
        return false;
    }
    dist.assign(N, vector<double>(N, 0.0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!(file >> dist[i][j])) {
                cerr << "Error: Not enough values. "
                     << "Failed at row=" << i
                     << " col=" << j << endl;
                return false;
            }
        }
    }

    file.close();
    return true;
}
double compute_avg_error(
    const vector<vector<double>>& orig,
    const vector<vector<double>>& coords,
    int N, int k
) {
    double total = 0.0;
    long long count = 0;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            double emb_sq = 0.0;
            for (int d = 0; d < k; d++) {
                double diff = coords[i][d] - coords[j][d];
                emb_sq += diff * diff;
            }
            double emb_d = sqrt(emb_sq);

            total += fabs(orig[i][j] - emb_d);
            count++;
        }
    }

    if (count == 0) return 0.0;
    return total / (double)count;
}
void print_output(
    const FastMapResult& result,
    const vector<vector<double>>& orig_dist,
    int N, int k
) {
    cout << "Algorithm: FastMap" << endl;
    cout << "Target dimensions: " << k << endl;

    cout << "Pivots per dimension:" << endl;
    for (int dim = 0; dim < k; dim++) {
        cout << "Dim " << (dim + 1) << ": "
             << result.pivots[dim].first << " "
             << result.pivots[dim].second << endl;
    }
    cout << "Object coordinates:" << endl;
    cout << fixed << setprecision(6);
    for (int i = 0; i < N; i++) {
        cout << i << ":";
        for (int dim = 0; dim < k; dim++) {
            cout << " " << result.coordinates[i][dim];
        }
        cout << endl;
    }
    cout << "Execution time: "
         << fixed << setprecision(3)
         << result.execution_time_ms << " ms" << endl;
    if (N <= 1000) {
        double err = compute_avg_error(
            orig_dist, result.coordinates, N, k
        );
        cout << "Average pairwise distance error: "
             << fixed << setprecision(6) << err << endl;
    } else {
        cout << "Average pairwise distance error: "
             << "(skipped for large N)" << endl;
    }
}
int main(int argc, char* argv[]) {

    if (argc != 2) {
        cerr << "Usage: " << argv[0]
             << " <input_file>" << endl;
        cerr << "Example: " << argv[0]
             << " tests/fm_01.txt" << endl;
        return 1;
    }

    string filename = argv[1];

    cout << "========================================" << endl;
    cout << " FastMap - Assignment 4 (Buddy Task)"    << endl;
    cout << " Input: " << filename                    << endl;
    cout << "========================================" << endl;

    vector<vector<double>> dist;
    int N, k;
    if (!read_input(filename, dist, N, k)) return 1;

    cout << "Loaded: N=" << N
         << " objects, k=" << k
         << " target dimensions" << endl;

    if (!validate_fastmap_input(dist, N, k)) return 1;

    cout << "Validation: PASSED" << endl;
    cout << "Running FastMap..." << endl;
    cout << "----------------------------------------" << endl;

    auto t_start = high_resolution_clock::now();

    FastMapResult result = fastmap(dist, N, k);
    auto t_end = high_resolution_clock::now();

    duration<double, milli> elapsed = t_end - t_start;
    result.execution_time_ms = elapsed.count();

    print_output(result, dist, N, k);

    cout << "========================================" << endl;
    return 0;
}