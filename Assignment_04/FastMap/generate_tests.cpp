

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

void generate_fm(const string& filename, int N, int k) {
    srand(42);

    vector<vector<double>> pts(N, vector<double>(k));
    for (int i = 0; i < N; i++)
        for (int d = 0; d < k; d++)
            pts[i][d] = (double)rand() / RAND_MAX * 100.0;

    cout << "Generating " << filename
         << " (N=" << N << ", k=" << k << ")..." << endl;

    ofstream f(filename);
    f << N << " " << k << "\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double d = 0.0;
            for (int x = 0; x < k; x++) {
                double diff = pts[i][x] - pts[j][x];
                d += diff * diff;
            }
            d = sqrt(d);
            if (j > 0) f << " ";
            f << fixed;
            f.precision(4);
            f << d;
        }
        f << "\n";
    }
    f.close();
    cout << "Done: " << filename << endl;
}

int main() {
    generate_fm("tests/fm_02.txt", 100,  2);
    generate_fm("tests/fm_03.txt", 1000, 3);
    cout << "All done!" << endl;
    return 0;
}