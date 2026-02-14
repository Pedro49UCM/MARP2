#include <fstream>
#include <iostream>
#include <vector>
#include<map>

using namespace std;

/*
 Definicion de la recurrencia
    dados(i, j) = formas de llegara cantidad i usando dados desde 1 hasta la j

    se cumple el principio de optimalidad de bellman porque cualquier subproblema de la solucion óptima
    es subsolucion óptima

    RECURSIVIDAD
    dados(i, j) = SUM(l=1->j) [dados(i-l, l)]

    CASOS BAASE: dados(0, j) = 1
    LLAMADA INICIAL: dados(SUMA, k)

    tabla -> SUMA x K
 */
 //Resuelve el problema usando PD
     //Explica la implementacion
     //Optimiza en espacio si procede
     //Analiza el coste en tiempo y espacio
long long maneras(int k, int i, int j, vector<vector<long long>>& dp) {
    if (i == 0) {
        return 1;
    }
    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    long long m = 0;
    for (int l = 1; l <= j; ++l) {
        if (i - l < 0) break;
        m += maneras(k, i - l, l, dp);
    }

    return dp[i][j] = m;
}

void resuelveCaso() {
    int k, suma;  //caras y suma a obtener
    cin >> k >> suma;
    vector<vector<long long>> dp(suma + 1, vector<long long>(k + 1, -1));

    cout << maneras(k, suma, k, dp) << "\n";
}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int casos;
    cin >> casos;
    for (int i = 0; i < casos; ++i)
        resuelveCaso();

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}