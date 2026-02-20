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
    ll k;//index de canción
    ll a;//ocupacion cinta a
    ll b;//ocupacion cinta b
    double beneficio_ac; // valor acumulado
    double beneficio_est; // prioridad
    bool operator<(Nodo const& otro) const {// > maximizar
        return otro.beneficio_est > beneficio_est;
    }
};

typedef priority_queue<Nodo> pq;

struct Cancion {
    ll duracion;
    ll puntuacion;
    bool operator<(Cancion const& otro) const {// > maximizar
        return otro.puntuacion/otro.duracion > puntuacion/duracion;
    }
};

double podaOptimista(Nodo &a, const ll&A, const ll& B,const vector<Cancion>& canciones) {
    ll restante = A - a.a + B - a.b;
    double beneficio = 0;
    for (int i = a.k; i < canciones.size(); i++) {
        if (canciones[i].duracion <= restante) {
            beneficio += canciones[i].puntuacion;
            restante -= canciones[i].duracion;
        }
        else {
            beneficio += (restante * (canciones[i].puntuacion/ canciones[i].duracion)); // Tomar fraccion
            break;
        }
    }
    return beneficio;
}


ll ramificacionYPoda(const ll& N, const ll& A, const ll&B,const vector<Cancion> &canciones) {
    Nodo a; a.k = 0; a.a = 0;a.b = 0;a.sol.assign(N, -1); a.beneficio_ac = 0;
    a.beneficio_est = podaOptimista(a,A,B,canciones);
    pq nodos;nodos.push(a);
    ll best = 0;
    while (!nodos.empty()) {
        Nodo Y = nodos.top();nodos.pop();
        if (Y.k == N) {
            best = Y.beneficio_ac;
            return best;
        }
        else {
            //Meter en cara A
            if ((A - Y.a) >= canciones[Y.k].duracion) {
                Nodo X = Y;
                X.a += canciones[Y.k].duracion;
                X.beneficio_ac += canciones[Y.k].puntuacion;
                if (X.beneficio_ac > best)
                    best = X.beneficio_ac;
                X.k++;
                X.sol[Y.k] = 1;//1 es cara a
                X.beneficio_est = X.beneficio_ac + podaOptimista(X, A, B, canciones);
                if(X.beneficio_est > best)
                    nodos.push(X);
            }
            //Meter en cara B
            if ((B - Y.b) >= canciones[Y.k].duracion) {
                Nodo X = Y;
                X.b += canciones[Y.k].duracion;
                X.beneficio_ac += canciones[Y.k].puntuacion;
                if (X.beneficio_ac > best)
                    best = X.beneficio_ac;
                X.k++;
                X.sol[Y.k] = 2;//2 es cara b
                X.beneficio_est = X.beneficio_ac + podaOptimista(X, A, B, canciones);
                if (X.beneficio_est > best)
                    nodos.push(X);
            }

            //No la meto
            Y.sol[Y.k] = 0;//0 es no la meto
            Y.k++;
            Y.beneficio_est = Y.beneficio_ac + podaOptimista(Y, A, B, canciones);
            if (Y.beneficio_est > best)
                nodos.push(Y);

        }
    }
    return best;
}



void solve() {
    ll N;
    cin >> N;
    while (N != 0) {
        ll A, B;
        cin >> A;
        B = A;
        vector<Cancion> canciones(N);
        for (int i = 0; i < N; i++) {
            cin >> canciones[i].duracion >> canciones[i].puntuacion;
        }
        sort(canciones.begin(), canciones.end());
        cout << ramificacionYPoda(N,A,B,canciones) << endl;
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