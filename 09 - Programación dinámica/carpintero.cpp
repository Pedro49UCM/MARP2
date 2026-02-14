#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include <algorithm>
#include <climits>
using namespace std;

int cortarMadera(vector<int>& longitudes, int L) {//Coste en tiempo O(N^3) y en espacio O(N^2)
    int N = longitudes.size();
    // Añadimos los límites inicial y final de la madera
    longitudes.insert(longitudes.begin(), 0);
    longitudes.push_back(L);

    // Matriz de DP para almacenar los costos mínimos
    vector<vector<int>> dp(N + 2, vector<int>(N + 2, 0));

    // Iterar por longitudes crecientes del intervalo
    for (int len = 2; len <= N + 1; len++) {
        for (int i = 0; i + len <= N + 1; i++) {
            int j = i + len;
            dp[i][j] = INT_MAX;
            for (int k = i + 1; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + (longitudes[j] - longitudes[i])*2);
            }
        }
    }

    return dp[0][N + 1];
}


void solve() {
	int N, L;
	while (cin >> L >> N && L!= 0 && N != 0) {
		vector<int>longitudes(N);
		for (int i = 0; i < N; i++) {
			cin>> longitudes[i];
		}
		cout << cortarMadera(longitudes, L) << endl;
	}
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("in.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
	solve();
	return 0;
}