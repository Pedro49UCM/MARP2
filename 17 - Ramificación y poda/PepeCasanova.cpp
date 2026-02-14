#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct Cancion {
    int duracion, puntuacion;
    double ratio; // Heurística: puntuación / duración
};

// Comparador para ordenar las canciones en orden decreciente de eficiencia
bool comparar(const Cancion& a, const Cancion& b) {
    return a.ratio > b.ratio;
}

// Cálculo de la cota optimista usando una versión fraccionaria de la mochila
double cota_optimista(const vector<Cancion>& canciones, int idx, int tiempo_restante) {//O(N)
    double beneficio = 0;
    for (int i = idx; i < canciones.size(); i++) {
        if (canciones[i].duracion <= tiempo_restante) {
            beneficio += canciones[i].puntuacion;
            tiempo_restante -= canciones[i].duracion;
        }
        else {
            beneficio += (tiempo_restante * canciones[i].ratio); // Tomar fracción
            break;
        }
    }
    return beneficio;
}

// Búsqueda con poda optimista-pesimista
void backtracking(const vector<Cancion>& canciones, int idx, int tiempo1, int tiempo2,
    int puntos_actuales, int& benef_mejor) {
    if (idx == canciones.size()) {
        benef_mejor = max(benef_mejor, puntos_actuales);
        return;
    }

    // Cota optimista (estimación máxima alcanzable)
    double benef_estimado = puntos_actuales + cota_optimista(canciones, idx, tiempo1 + tiempo2);//O(N)
    if (benef_estimado <= benef_mejor) return; // Poda optimista


    //O(K) -> K << 3^N
    // Opción 1: Colocar la canción en la cara 1
    if (tiempo1 >= canciones[idx].duracion) {
        backtracking(canciones, idx + 1, tiempo1 - canciones[idx].duracion, tiempo2,
            puntos_actuales + canciones[idx].puntuacion, benef_mejor);
    }

    // Opción 2: Colocar la canción en la cara 2
    if (tiempo2 >= canciones[idx].duracion) {
        backtracking(canciones, idx + 1, tiempo1, tiempo2 - canciones[idx].duracion,
            puntos_actuales + canciones[idx].puntuacion, benef_mejor);
    }

    // Opción 3: No colocar la canción
    backtracking(canciones, idx + 1, tiempo1, tiempo2, puntos_actuales, benef_mejor);
}

void solve() {
    int N;
    while (cin >> N && N != 0) {
        int t;
        cin >> t;

        vector<Cancion> canciones(N);
        for (int i = 0; i < N; i++) {
            cin >> canciones[i].duracion >> canciones[i].puntuacion;
            canciones[i].ratio = (double)canciones[i].puntuacion / canciones[i].duracion;
        }

        // Ordenamos las canciones por eficiencia
        sort(canciones.begin(), canciones.end(), comparar);//O(N log N).

        int benef_mejor = 0;
        backtracking(canciones, 0, t, t, 0, benef_mejor);

        cout << benef_mejor << endl;
    }
}

int main() {
#ifndef DOMJUDGE
    ifstream in("in.txt");
    cin.rdbuf(in.rdbuf());
#endif
    solve();
    return 0;
}
