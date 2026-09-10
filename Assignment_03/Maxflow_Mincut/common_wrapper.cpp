
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc >= 3 && string(argv[1]) == "maxflow") {
        string command = "maxflow_driver \"" + string(argv[2]) + "\"";
        return system(command.c_str());
    }

cout << "CS509 Buddy Assignment 3 - Maxflow-Mincut\n";
    cout<<"Usage:\n";
    cout<< "  wrapper maxflow <test_file>\n";
    cout<< "\nExamples:\n";
    cout << "  wrapper maxflow assignment_03/tests/maxflow_10.txt\n";
    cout <<"  wrapper maxflow assignment_03/tests/maxflow_100.txt\n";
   return 0;
}
