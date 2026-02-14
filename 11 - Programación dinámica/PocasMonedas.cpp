#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include <algorithm>
#include <climits>
using namespace std;


void solve() {
    int N;
    while (cin >> N && N != 0) {
        vector<int>valores(N);
        for (int i = 0; i < N; i++) {
            cin >> valores[i];
        }
        vector<int>cantidades(N);
        for (int i = 0; i < N; i++) {
            cin >> cantidades[i];
        }
        int precio;
        cin >> precio;
         vector<int> dp(precio + 1, INT_MAX);
        dp[0] = 0;

        for (int i = 0; i < N; ++i) {
            vector<int> nueva_dp = dp;
            for (int j = 0; j <= precio; ++j) {
                if (dp[j] != INT_MAX) {
                    for (int k = 1; k <= cantidades[i] && j + k * valores[i] <= precio; ++k) {
                        nueva_dp[j + k * valores[i]] = min(nueva_dp[j + k * valores[i]], dp[j] + k);
                    }
                }
            }
            dp = nueva_dp;
        }

        if (dp[precio] == INT_MAX) {
            cout << "NO" << endl;
        }
        else {
            cout << "SI " << dp[precio] << endl;
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
