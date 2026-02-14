#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


const int INF = 1e8;


struct Sumin {
    int st; // stock
    int p; // precio
};

struct Nodoma {
    int k; // 0 a M
    int coste;
    int coste_est;
    vector<int> masc; // 0 a N, numero de mascarillas por universidad
    int dones; // 0 -> N, si es N entonces hay solucion

    bool operator<(Nodoma const& n) const {
        return coste_est > n.coste_est;
    }
};

typedef priority_queue<Nodoma> pq;

// asignamos en orden cumpliendo las restricciones, pesimista
int coste_masc_est_pes(vector<int> const& uni, vector<Sumin> const& dist, Nodoma const& X) {
    int N = uni.size(), M = dist.size();
    int estimacion = X.coste, i = X.k + 1;

    for (int u = 0; u < N; ++u) {
        int c = X.masc[u];
        while (c < uni[u] && i < M) {
            estimacion += min(dist[i].st, (uni[u] - c)) * dist[i].p;
            c = min(uni[u], c + dist[i].st);
            ++i;
        }
        if (c < uni[u]) return INF; // es imposible llegar a la solucion en este estado
    }

    return estimacion + 1;
}

// solucion voraz optimista
int coste_masc_est(vector<int> const& uni, vector<Sumin> const& dist, Nodoma const& X) {
    int N = uni.size(), M = dist.size();
    int estimacion = X.coste, i = X.k + 1;

    if (i == M) return estimacion;

    int stock = 0;

    for (int u = 0; u < N; ++u) {
        stock += uni[u] - X.masc[u];
    }

    while (i < M && stock > 0) {
        estimacion += min(dist[i].st, stock) * dist[i].p;
        stock = max(0, stock - dist[i].st);
        ++i;
    }

    return estimacion;
}

bool mascarillas_rp(vector<int> const& uni, vector<Sumin> const& dist, int& best) {
    bool res = false;
    int N = uni.size(), M = dist.size();

    Nodoma Y;
    Y.masc = vector<int>(N, 0);
    Y.k = -1; Y.dones = 0;
    Y.coste = 0;
    Y.coste_est = coste_masc_est(uni, dist, Y);

    pq cola;
    cola.push(Y);
    best = coste_masc_est_pes(uni, dist, Y);

    while (!cola.empty() && cola.top().coste_est <= best) {
        Y = cola.top(); cola.pop();
        Nodoma X(Y);
        ++X.k;

        // comprobar solucion sin asignar camino
        X.coste = Y.coste;
        X.coste_est = coste_masc_est(uni, dist, X);
        if (X.k < N - 1 && X.coste_est <= best)
            cola.push(X);

        for (int u = 0; u < N; ++u) {
            if (Y.masc[u] == uni[u]) continue;

            X.dones = Y.dones;
            X.coste = Y.coste + min(dist[X.k].st, (uni[u] - Y.masc[u])) * dist[X.k].p;
            X.masc[u] = min(uni[u], Y.masc[u] + dist[X.k].st);
            if (X.masc[u] == uni[u]) X.dones = Y.dones + 1;
            X.coste_est = coste_masc_est(uni, dist, X);

            if (X.coste_est <= best)
                if (X.dones == N) {
                    best = X.coste; res = true;
                }
                else if (X.k < M - 1) {
                    cola.push(X);
                    int pesimista = coste_masc_est_pes(uni, dist, X);
                    if (pesimista < best)
                        best = pesimista;
                }
            X.masc[u] = Y.masc[u];
        }
    }
    return res;
}

void solve_ma() {
    int N, M;
    cin >> N >> M;

    vector<int> uni(N);
    vector<Sumin> dist(M);

    for (int i = 0; i < N; ++i)
        cin >> uni[i];

    for (int i = 0; i < M; ++i)
        cin >> dist[i].st;

    for (int i = 0; i < M; ++i)
        cin >> dist[i].p;

    int best;
    
    if (mascarillas_rp(uni, dist, best))
        cout << best << "\n";
    else
        cout << "NO\n";

}

int main() {
#ifndef DOMJUDGE
    ifstream in("in.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    int C; cin >> C;
    for (int i = 0; i < C; ++i) {
        solve_ma();
    }
       

    return 0;
}