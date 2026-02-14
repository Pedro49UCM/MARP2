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

struct Cofre {
    ll p;
    ll valor;
};

ll recursiva(vector<vector<ll>>& dp,const vector<Cofre>& cofres, ll i, ll j) {
    if (i == 0 || j == 0) {
        dp[i][j] = 0;
        return dp[i][j];
    }
    else if (dp[i][j] != -1)
        return dp[i][j];
    if (j < cofres[i].p * 3) {
        dp[i][j] = recursiva(dp, cofres, i - 1, j);
        return dp[i][j];
    }
    else {
        ll loCojo = recursiva(dp, cofres, i - 1, j - cofres[i].p * 3) + cofres[i].valor;
        ll noLoCojo = recursiva(dp, cofres, i - 1, j);
        dp[i][j] = max(noLoCojo, loCojo);
        return dp[i][j];
    }
    
}

vector<ll> reconstruccion(const vector<vector<ll>>& dp, const vector<Cofre>& cofres, const ll T, const ll N) {
    vector<ll> solucion;
    ll i = N, j = T, total = dp[i][j];
    while (i > 0 && j > 0) {
        if (dp[i][j] == dp[i - 1][j])
            i--;
        else {
            j -= cofres[i].p * 3;
            solucion.push_back(i);
            i--;
            
        }
    }
    return solucion;
}

void solve() {
    ll T;
    while (cin >> T) {
        ll N;
        cin >> N;
        vector<Cofre> cofres(N+1);
        for (ll i = 1; i <= N; i++) {
            Cofre x;
            cin >> cofres[i].p >> cofres[i].valor;
        }
        vector<vector<ll>> dp(N+1, vector<ll>(T + 1, -1));

        cout << recursiva(dp, cofres, N,T) << endl;


        vector<ll> solucion = reconstruccion(dp, cofres, T, N);
        cout << solucion.size() << endl;
        for (ll a : solucion) {
            cout << cofres[a].p << " " << cofres[a].valor << endl;
        }
        cout << "---" << endl;
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