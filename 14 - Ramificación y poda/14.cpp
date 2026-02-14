#include<iostream>
#include<fstream>
#include<vector>
#include<climits>
#include<algorithm>
#include<string>
#include<iomanip>
#include <cassert>
#include <tuple> 
#include <cmath>
#include<queue>
#include<unordered_map>
using namespace std;

using namespace std;
using ll = long long;
const ll INF = 1e9;

struct Nodo {
    vector<ll> sol;
    int k;
    //double peso; // peso acumulado
    double beneficio_ac; // valor acumulado
    double beneficio_est; // prioridad
    bool operator<(Nodo const& otro) const {
        return otro.beneficio_est < beneficio_est;
    }
};

typedef priority_queue<Nodo> pq;

ll ramificacionYPoda(const ll& N, const vector<vector<ll>>& funcionarioCurro, const vector<ll> &opt) {
    Nodo a;a.k = 0;a.sol.assign(N, -1); a.beneficio_ac = 0; a.beneficio_est = opt[0];
    pq nodos;nodos.push(a);
    ll best = INF;
    while (!nodos.empty()) {
        Nodo Y = nodos.top();nodos.pop();
        if (Y.k == N) {
            best = Y.beneficio_ac;
            return best;
        }
        else {
            for (ll i = 0; i < N; i++) {
                if (Y.sol[i] == -1) {
                    Nodo X = Y;
                    X.beneficio_ac += funcionarioCurro[Y.k][i];
                    if (Y.k < N - 1)
                        X.beneficio_est = X.beneficio_ac + opt[Y.k + 1];
                    else
                        X.beneficio_est = X.beneficio_ac;
                    X.sol[i] = Y.k;
                    X.k++;
                    nodos.push(X);
                }
            }
        }
    }
    return best;
}

void solve() {
    ll N;
    cin >> N;
    while (N != 0) {
        vector<vector<ll>> funcionarioCurro(N, vector<ll>(N));
        vector<ll> opt(N);
        for (ll i = 0; i < N; i++) {
            ll smallest = INF;
            for (ll j = 0; j < N; j++) {
                cin >> funcionarioCurro[i][j];
                if (funcionarioCurro[i][j] < smallest)
                    smallest = funcionarioCurro[i][j];
            }
            opt[i] = smallest;
        }
        for (ll i = N - 2; i >= 0; i--) {
            opt[i] += opt[i + 1];
        }
        cout << ramificacionYPoda(N, funcionarioCurro, opt) << endl;
        cin >> N;
    }
}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
    //std::ofstream out("out.txt");
    //auto coutbuf = std::cout.rdbuf(out.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

    solve();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
}