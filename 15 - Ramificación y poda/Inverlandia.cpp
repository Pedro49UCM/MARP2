#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include <algorithm>
#include <climits>
using namespace std;

void recursivo(const vector<vector<int>>& calidades,const vector<int>&anchurasCarros, const vector<int>& anchurasCaminos,vector<bool>& trabajos, int& maximo, int limpieza, int carro) {
    if (carro >= anchurasCarros.size()) {
        maximo = max(maximo, limpieza);
        return;
    }

    for (int j = 0; j < anchurasCaminos.size(); j++) {
        if (!trabajos[j] && anchurasCarros[carro] <= anchurasCaminos[j]) {
            trabajos[j] = true;
            recursivo(calidades, anchurasCarros,anchurasCaminos,trabajos,maximo, limpieza + calidades[carro][j], carro + 1);
            trabajos[j] = false;
        }
    }
    recursivo(calidades, anchurasCarros, anchurasCaminos, trabajos, maximo, limpieza, carro + 1);
}



void solve() {
    int casosDePrueba;
    cin >> casosDePrueba;
    for (int casoP = 0; casoP < casosDePrueba; casoP++) {
        int carros, caminos;
        cin >> carros >> caminos;//carros<caminos
        vector<int>anchurasCarros(carros);
        for (int i = 0; i < carros; i++) {
            cin >> anchurasCarros[i];
        }
        vector<int>anchurasCaminos(caminos);
        for (int i = 0; i < caminos; i++) {
            cin >> anchurasCaminos[i];
        }
        vector<vector<int>> calidades(carros, vector<int>(caminos));
        for (int i = 0; i < carros; i++) {
            for (int j = 0; j < caminos; j++) {
                cin >> calidades[i][j];
            }
        }
        vector<bool> trabajos(caminos, false);
        int maximo = 0;
        recursivo(calidades, anchurasCarros, anchurasCaminos, trabajos, maximo, 0, 0);
        cout << maximo << endl;
    }
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    solve();
    return 0;
}