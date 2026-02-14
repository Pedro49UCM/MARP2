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
        vector<vector<int>>costes(N-1, vector<int>(N-1,-1));
        for (int i = 0; i < N-1; i++) {
            for (int j = 0; j < N - 1 - i; j++) {
                cin >> costes[i][j];
            }
        }
        vector<vector<int>>dp(N, vector<int>(N, -1));
        for (int gap = 1; gap < N; gap++) {
            for (int i = N - 1 - gap; i >= 0; i--) {
                dp[i][i + gap] = costes[i][gap - 1];
            }
        }

        //Master Floyd
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                for (int k= i+1; k < j; k++) {
                        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
                    
                }
            }
        }
        for (int i = 0; i < N - 1; i++) {
            for (int j = i + 1; j < N; j++) {
                if (j != i + 1)
                    cout << " ";
                cout << dp[i][j];
            }
            cout << endl;
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