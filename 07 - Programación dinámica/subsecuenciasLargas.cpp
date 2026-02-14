#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include <algorithm>
#include <climits>
using namespace std;


// Función para encontrar la subsecuencia común más larga
string lcs(const string& X, const string& Y) {
	int m = X.size(), n = Y.size();
	vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

	// Llenar la tabla de programación dinámica
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (X[i - 1] == Y[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else {
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}

	// Reconstruir la subsecuencia común más larga
	string result;
	int i = m, j = n;
	while (i > 0 && j > 0) {
		if (X[i - 1] == Y[j - 1]) {
			result = X[i - 1] + result;
			i--, j--;
		}
		else if (dp[i - 1][j] > dp[i][j - 1]) {
			i--;
		}
		else {
			j--;
		}
	}
	return result;
}

void solve() {
	string uno, dos;
	while (cin >> uno >> dos) {
		
		cout << lcs(uno,dos) << endl;
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