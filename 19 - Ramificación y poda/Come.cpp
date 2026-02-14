#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int INF = 1e8;

/*
* EXPLICACION
* arbol de exploracion -> para cada comensal asignar un sitio
*
* funcion de poda -> nodos donde el numero de parejas estimado sea menor a la mejor
                    solucion encontrada/cota pesimista
* estimacion -> cota superior:
*              
*/

struct Nodoma {
    vector<int> sol; // sitio de cada persona ya sentada
    int k; // 0 a M
    int parejas;
    int parejas_est;
    vector<bool> pillado; // lugares ya asignados

    bool operator<(Nodoma const& n) const {
        return (parejas_est < n.parejas_est) || (parejas_est == n.parejas_est && parejas < n.parejas); // maximizar
    }
};

typedef priority_queue<Nodoma> pq;

// asignamos en orden cumpliendo las restricciones, pesimista
int parejas_est_pes(vector<vector<double>> const& dist, vector<vector<bool>> const& alle, Nodoma const& X) {
    int N = dist.size(), M = alle.size();
    int estimacion = X.parejas, i = X.k + 1;

    return estimacion;
}

// solucion voraz optimista
int parejas_est(vector<vector<double>> const& dist, vector<vector<bool>> const& alle, Nodoma const& X) {
    int N = dist.size(), M = alle.size();
    int estimacion = X.parejas, asignados = X.k + 1;

    for (int i = 0; i < asignados; ++i)
        for (int k = asignados; k < M; ++k)
            if (alle[i][k])
                ++estimacion;

    for (int k = asignados; k < M; ++k)
        for (int l = k + 1; l < M; ++l)
            if (alle[k][l])
                estimacion++;
    
    return estimacion;
}

bool comensales_rp(vector<vector<double>> const& dist, vector<vector<bool>> const& alle, vector<int>& sol, int& best) {
    bool res = false;
    int N = dist.size(), M = alle.size();

    Nodoma Y;
    Y.sol = vector<int>(M, -1); Y.pillado = vector<bool>(N, false);
    Y.k = -1;
    Y.parejas = 0;
    Y.parejas_est = parejas_est(dist, alle, Y);

    pq cola;
    cola.push(Y);
    best = parejas_est_pes(dist, alle, Y);

    while (!cola.empty() && cola.top().parejas_est >= best) {
        Y = cola.top(); cola.pop();
        Nodoma X(Y);
        ++X.k;

        // Asignar un sitio
        for (int r = 0; r < N; ++r) {
            if (Y.pillado[r]) continue;
            
            // comprobar si no causa problemas y contar los allegados cercanos
            int cerca = 0; bool error = false;
            for (int k = 0; k < X.k; ++k) {
                int u = Y.sol[k];
                if (!alle[X.k][k] && dist[r][u] < 2) {
                    error = true; break;
                }
                else if (alle[X.k][k] && dist[r][u] < 2)
                    ++cerca;
            }
            if (error) continue;

            X.sol[X.k] = r; X.pillado[r] = true;
            X.parejas = Y.parejas + cerca;
            X.parejas_est = parejas_est(dist, alle, X);
            if (X.parejas_est >= best) {
                if (X.k == M - 1) {
                    sol = X.sol; best = X.parejas; res = true;
                }
                else {
                    cola.push(X);
                    int pesimista = parejas_est_pes(dist, alle, X);
                    if (pesimista > best)
                        best = pesimista;
                }
            }
            X.pillado[r] = false;

        }
    }
    return res;
}

void solve_co() {
    int N, M;
    cin >> N >> M;

    vector<vector<double>> dist(N, vector<double>(N));
    vector<vector<bool>> alle(M, vector<bool>(M));

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> dist[i][j];

    for (int i = 0; i < M; ++i)
        for (int j = 0; j < M; ++j) {
            int a; cin >> a;
            alle[i][j] = a == 1;
        }

    vector<int> sol;
    int best;

    if (comensales_rp(dist, alle, sol, best))
        cout << "PAREJAS " << best << "\n";
    else
        cout << "CANCELA\n";

}

int main() {
#ifndef DOMJUDGE
    ifstream in("in.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    int C; cin >> C;
    for (int i = 0; i < C; ++i) solve_co();

    return 0;
}