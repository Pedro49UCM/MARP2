#include<fstream>
#include<iostream>
#include<vector>
#include<queue>
#include <algorithm>
#include <climits>
using namespace std;

void solve() {
	int N, pMin, pMax;
	while (cin >> N >> pMax >> pMin) {
		vector<int> potencia(N);
		vector <int> coste(N);
		for (int i = 0; i < N; i++)
			cin >> potencia[i];
		for (int i = 0; i < N; i++)
			cin >> coste[i];

		vector<long long> dp_min_cost(pMax + 1, LLONG_MAX); // mínimo coste para cada longitud
		dp_min_cost[0] = 0;
		for (int i = 0; i < N; i++) {
			for (int j = potencia[i]; j <= pMax; j++) {
				// Actualizar mínimo coste
				if (dp_min_cost[j - potencia[i]] != LLONG_MAX) {
					dp_min_cost[j] = min(dp_min_cost[j], dp_min_cost[j - potencia[i]] + coste[i]);//Se guarda el valor del numero minimo de coste necesarios para llegar a j
				}
			}
		}
		int costeMin = INT_MAX, potenciaX = -1;
		for (int i = pMin; i <= pMax; i++) {
			if (dp_min_cost[i] < costeMin) {
				costeMin = dp_min_cost[i];
				potenciaX = i;
			}
		}
		if (potenciaX == -1) {
			cout << "IMPOSIBLE" << endl;
		}
		else {
			cout << costeMin << " " << potenciaX << endl;
		}
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