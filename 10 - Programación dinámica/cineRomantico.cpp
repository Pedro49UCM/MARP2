#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include <algorithm>
#include <climits>
using namespace std;

struct Peli {
    long long inicio, fin, duracion;
};

// Comparador para ordenar las pel�culas por su tiempo de finalizaci�n
bool comparar(const Peli& a, const Peli& b) {
    return a.fin < b.fin;
}

// Funci�n para encontrar la �ltima pel�cula que no se solape con la pel�cula en �ndice `i`
int findLastNonOverlapping(const vector<Peli>& peliculas, int i) {
    int low = 0, high = i - 1, best = -1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (peliculas[mid].fin <= peliculas[i].inicio) {
            best = mid;
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return best;
}

/*
RECURSION
Parametros:
    i es el indice de la pel�cula
    incluir es el tiempo acumulado si se incluye la pel�cula i
    idx es el �ndice de la �ltima pel�cula que no se solapa con la pel�cula i
Rangos:
    Las películas van del 0 al N-1
    El vector dp va del 0 a N-1
Casos base: 
    dp[i] tiene valor, por lo que no se vuelve a calcular
Casos recursivos:
    No sabemos el valor de dp[i]. 2 casos:
        1. No ver la pel�cula i: dp[i] = dp[i-1]
        2. Ver la pel�cula i: dp[i] = duracion de la película i + dp[idx] (si hay pelicula anterior)
    dp[i] será el máximo de las 2 opciones
*/

/*
IMPLEMENACION
Iterativo: 
    Como relleno el vector:
        Voy de pelicula en pelicula viendo si renta más verla o no verla.
        Por ello se rellena el vector de dp de izquierda a derecha, ya que para calcular dp[i] 
        necesito el valor de dp[i-1] y dp[anterior pelicula que no solapa], y ambos ya los tengo calculados al ser menores que i
*/

/*
COSTE DE RELLENADO DE LA MATRIZ:
Tiempo: O(N) se recorre cada pelicula una unica vez
Espacio: O(N) el vector dp tiene tamaño N, y el vector de lastNonOverlapping también tiene tamaño N
*/

void programacionDinamica(vector<int> &dp,vector<int> &lastNonOverlapping, vector<Peli> &peliculas) {
    for (int i = 1; i < dp.size(); i++) {
            // Opci�n 1: No ver la pel�cula `i` (quedarse con la mejor opci�n previa)
            dp[i] = dp[i - 1];

            // Opci�n 2: Ver la pel�cula `i`
            int incluir = peliculas[i].duracion;
            int idx = lastNonOverlapping[i];
            if (idx != -1) {
                incluir += dp[idx];  // Sumar la mejor opci�n previa no solapada
            }

            // Guardar la mejor opci�n entre ambas
            dp[i] = max(dp[i], incluir);
        }
}


void solve() {
    int N;
    while (cin >> N && N != 0) {
        vector<Peli> peliculas(N);

        // Leer los tiempos de inicio y duraci�n
        for (int i = 0; i < N; i++) {
            long long d, h, m, duracion;
            char c;
            cin >> d >> h >> c >> m >> duracion;
            peliculas[i].inicio = (d*24 +h) * 60 + m;
            peliculas[i].fin = peliculas[i].inicio + duracion + 10; // 10 minutos de pausa
            peliculas[i].duracion = duracion;
        }

        // Ordenar pel�culas por tiempo de finalizaci�n
        sort(peliculas.begin(), peliculas.end(), comparar);

        // DP para encontrar el m�ximo tiempo de visionado
        vector<int> dp(N);
        vector<int> lastNonOverlapping(N, -1);

        // Precomputar la �ltima pel�cula que no se solapa con cada pel�cula i
        for (int i = 0; i < N; i++) {
            lastNonOverlapping[i] = findLastNonOverlapping(peliculas, i);
        }

        // Caso base: La mejor opci�n para la primera pel�cula es verla
        dp[0] = peliculas[0].duracion;

        programacionDinamica(dp, lastNonOverlapping, peliculas);

        // La respuesta est� en dp[N-1], el mejor tiempo acumulado posible
        cout << dp[N - 1] << endl;
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
