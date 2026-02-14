#include <iostream>
#include<fstream>
#include <vector>
using namespace std;

struct Cofre {
    int profundidad;
    int oro;
};

void solve() {
    int T, N;
    bool first_case = true;

    while (cin >> T) {
        cin >> N;
        vector<Cofre> cofres(N);
        for (int i = 0; i < N; ++i) {
            cin >> cofres[i].profundidad >> cofres[i].oro;
        }

        vector<vector<int>> dp(N + 1, vector<int>(T + 1, 0));

        for (int i = 1; i <= N; ++i) {
            int tiempo = 3 * cofres[i - 1].profundidad;
            for (int t = 0; t <= T; ++t) {
                dp[i][t] = dp[i - 1][t]; 
                if (t >= tiempo) {
                    dp[i][t] = max(dp[i][t], dp[i - 1][t - tiempo] + cofres[i - 1].oro);
                }
            }
        }

        // Obtener la cantidad máxima de oro
        int maxOro = dp[N][T];

        // Reconstruir la solución
        vector<Cofre> seleccionados;
        int t = T;
        for (int i = N; i > 0 && maxOro > 0; --i) {
            int tiempo = 3 * cofres[i - 1].profundidad;
            if (t >= tiempo && dp[i][t] == dp[i - 1][t - tiempo] + cofres[i - 1].oro) {
                seleccionados.push_back(cofres[i - 1]);
                t -= tiempo;
                maxOro -= cofres[i - 1].oro;
            }
        }


        cout << dp[N][T] << endl;
        cout << seleccionados.size() << endl;
        for (int i = seleccionados.size() - 1; i >= 0; --i) {
            cout << seleccionados[i].profundidad << " " << seleccionados[i].oro << endl;
        }
        cout << "---\n";
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
