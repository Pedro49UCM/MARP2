#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include <algorithm>
#include <climits>
using namespace std;

void comeDevoradora(const vector<int>& cubos, int &ini, int &fin) {
    if (ini > fin || ini >= cubos.size() || fin < 0)
        return;
    if (cubos[ini] >= cubos[fin])
        ini++;
    else
        fin--;
}

int resuelve(const vector<int>& cubos, vector<vector<int>>&dp, int ini, int fin, int profundidad) {
    if (dp[ini][fin] == -1) {
        /*for (int jk = 0; jk < profundidad; jk++)
            cout << "   ";
        cout << "comienzo iteracion con ini=" << ini << " y fin=" << fin << endl;*/
        int result;
        if (ini >= fin || ini >= cubos.size() || fin < 0) {
            result = cubos[ini];
        }
        else if (fin - ini == 1)
            result = max(cubos[ini], cubos[fin]);
        else {
            int newIni = ini + 1, newFin = fin;
            comeDevoradora(cubos, newIni, newFin);
            int izq = cubos[ini] + resuelve(cubos, dp, newIni, newFin, profundidad + 1);

            newIni = ini, newFin = fin - 1;
            comeDevoradora(cubos, newIni, newFin);
            int der = cubos[fin] + resuelve(cubos, dp, newIni, newFin, profundidad + 1);
            result = max(dp[ini][fin], max(izq, der));
        }
        dp[ini][fin] = result;
        /*for (int jk = 0; jk < profundidad; jk++)
            cout << "   ";
        cout << "fin iteracion dp[ini][fin] =" << dp[ini][fin] << endl;*/
        return result;
    }
    else {
        return dp[ini][fin];
    }
}


void solve() {
    int N;
    while (cin >> N && N != 0) {
        vector<int>cubos(N);
        for (int i = 0; i < N; i++) {
            cin >> cubos[i];
        }
        vector<vector<int>>dp(N, vector<int>(N, -1));
        cout << resuelve(cubos, dp,0, N - 1, 0) << endl;
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