#include <fstream>
#include <iostream>
#include <vector>
#include<map>

using namespace std;

/*
 Definicion de la recurrencia
    dados(i, j) = formas de llegar a cantidad i usando dados desde 1 hasta la j

    Se cumple el principio de optimalidad de bellman porque cualquier subproblema de la solucion óptima 
    es subsolucion óptima, y por eso no se vuelve a calcular

    Casos base:
        - if(i==0)  return 1;
            El numero de formas de llegar del que se parte es 1, pues para cualquier i>0 el minimo de formas va a ser 1.

        -if (dp[i][j] != -1) return dp[i][j];
            Si ya se ha calculado el valor, se devuelve, evitando asi el recalculo de subproblemas ya resueltos.

    Casos recursivos:
        - for (int l = 1; l <= j; ++l) {
            if (i - l < 0) break;
            m += dados( i - l, l, dp);
        }
            Queremos sumar el numero de formas de llegar a i usando diferentes dados, con caras desde 1 hasta j, 
            emepezamos con un dado de 1 cara, y vamos aumentando el numero de caras hasta llegar a j, 
            y así evitamos contar varias veces la misma combinacion de dados.

 */
/*
    ESTRATEGIA DE RESOLUCIÓN
        El obejtivo es calcular el numero de formas de llegar a una cantidad dada usando dados con un numero de caras dado,
        pero queremos evitar sumar varias veces la misma combinacion de dados, para ello vamos a calcular el numero de formas
        con difernetes dados a los cuales les vamos a ir aumentando el numero de caras, asi evitamos contar varias veces la misma combinacion de dados.

    OPTIMIZACIÓN EN ESPACIO
        El espacio utilizado es de O(suma * k) debido al vector dp. Este no se puede optimizar, puesto que necesitamos tanto la 
        dimension de las suma de los dados, como la dimension del numero de caras de los dados para almacenar los resultados de 
        los subproblemas, ya que para los calculos necesitamos acceder a ambos parametros, y no se puede reducir a una sola 
        dimension sin perder la información necesaria para resolver el problema.

    ANALISIS DE COSTE
        El coste en tiempo es O(suma * k^2) debido a que para cada valor de i (que va desde 0 hasta suma) y para cada valor de j (que va desde 0 hasta k), 
        se realiza un bucle interno que itera hasta j, lo que da lugar a una complejidad cuadrática en términos de k. 
        El coste en espacio es O(suma * k) debido al uso del vector dp para almacenar los resultados de los subproblemas.
*/

long long dados(int i, int j, vector<vector<long long>>& dp) {
    if (i == 0) {
        return 1;
    }
    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    long long m = 0;
    for (int l = 1; l <= j; ++l) {
        if (i - l < 0) break;
        m += dados( i - l, l, dp);
    }

    return dp[i][j] = m;
}

void resuelveCaso() {
    int k, suma;  //caras y suma a obtener
    cin >> k >> suma;
    vector<vector<long long>> dp(suma + 1, vector<long long>(k + 1, -1));

    cout << dados(suma, k, dp) << "\n";
}


int main() {
/*#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif*/

    int casos;
    cin >> casos;
    for (int i = 0; i < casos; ++i)
        resuelveCaso();

/*#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif*/

    return 0;
}