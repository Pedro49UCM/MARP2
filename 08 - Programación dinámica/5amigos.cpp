#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<unordered_map>
#include <algorithm>
#include <climits>
using namespace std;
const int INF = 1e8;

void floyd(vector<vector<int>>& distancias, const int &P) {
	for (int k = 0; k < P; k++) {
		for (int i = 0; i < P; i++) {
			for (int j = 0; j < P; j++) {
				if (distancias[i][k] < INF && distancias[k][j] < INF) {
					distancias[i][j] = min(distancias[i][j], distancias[i][k] + distancias[k][j]);
				}
			}
		}
	}
}

void solve() {
	int P, R;
	while (cin >> P >> R) {
		unordered_map<string, int> nombres;
		int idx = 0;
		vector<vector<int>> distancias(P, vector<int>(P, INF));
		for (int i = 0; i < R; i++) {
			string uno, dos;
			cin >> uno >> dos;
			if (nombres.find(uno) == nombres.end()) {
				nombres[uno] = idx;
				idx++;
			}
			if (nombres.find(dos) == nombres.end()) {
				nombres[dos] = idx;
				idx++;
			}
			distancias[nombres[uno]][nombres[dos]] = 1;
			distancias[nombres[dos]][nombres[uno]] = 1;
		}
		for (int i = 0; i < P; i++)
			distancias[i][i] = 0;//Por esta mierda me fallaba en el juez
		floyd(distancias, P);
		int maximo = 0;
		for (int i = 0; i < P && maximo < INF; i++) {
			for (int j = 0; j < P && maximo < INF; j++) {
				if (distancias[i][j] > maximo)
					maximo = distancias[i][j];
			}
		}
		if (maximo < INF)
			cout << maximo << endl;
		else
			cout << "DESCONECTADA" << endl;
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