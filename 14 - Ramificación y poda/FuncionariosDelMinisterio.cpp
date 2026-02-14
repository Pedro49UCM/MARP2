#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include <algorithm>
#include <climits>
using namespace std;

void recursivo(const vector<vector<int>> &funcT, vector<bool> &trabajos, int& min, int T, int func) {
    if (func == trabajos.size()) {
        //cout << "min= " << min << " T = " << T << endl;
        min = T;
    }
    else {
        for (int i = 0; i < trabajos.size(); i++) {
            if (!trabajos[i]) {
                trabajos[i] = true;
                if (T + funcT[func][i] < min)
                    recursivo(funcT, trabajos, min, T + funcT[func][i], func + 1);
                trabajos[i] = false;
            }  
        }
    }
}


void solve() {
    int N;
    while (cin >> N && N != 0) {
        vector<vector<int>> funcT(N, vector<int>(N));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> funcT[i][j];
            }
        }
        vector<bool> trabajos(N, false);
        int min = INT_MAX;
        recursivo(funcT, trabajos, min, 0, 0);
        cout << min << endl;
    }
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    solve();
    return 0;
}