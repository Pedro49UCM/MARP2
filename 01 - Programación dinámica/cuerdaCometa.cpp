#include<fstream>
#include<iostream>
#include<vector>
#include <algorithm>
#include <climits>
using namespace std;

/*
RECURSION
Parametros:
    i es el index de cordel
    j es la longitud a la que quiero llegar con el cordel
    dp_ways es el vector que guarda el numero de formas de llegar a la lonjitud j
    dp_min_cords es el vector que guarda el numero minimo de cordeles para llegar a a longitud j
    dp_min_cost es el vector que guarda el coste minimo para llegar a la longitid j
Rangos:
    los cordeles van del 0 al n
    los vectores soluion van del 0 a L+1
Casos base: 
    if(j > legths[i] || i == n) break;
Casos recursivos:
    if(j<=leghts[i] && i <n)
        calculate vector values at j
        j++

*/
/*
IMPLEMENACION
Iterativo: 
    Como relleno el vector:
        Primero itero por los cordeles, del 1 al n, y despues con cada cordel voy iterndo desde
        el final de la longitud desada hasta la distancia del corel, para asi poder añadir al punto
        en cuestion el valor de lo que habia antes del cordel más lo del cordel
*/
/*
COSTE DE RELLENADO DE LA MATRIZ:
Tiempo: O(n*L)
Espacio: O(L)
    El espacio ya esta reducido a 1 dimension por lo que no se podría reducir más ya que necesitamos los valores de diversas longitudes

*/



void solve() {
	int n, L;
	while (cin >> n >> L) {
		vector<int> leghts(n);//vector con las longitudes
		vector<int> costs(n);//vector con los costes
		for (int i = 0; i < n; i++)
			cin >> leghts[i] >> costs[i];
        // DP arrays
        vector<long long> dp_ways(L + 1, 0); // n�mero de formas de conseguir cada longitud
        vector<int> dp_min_cords(L + 1, INT_MAX); // m�nimo n�mero de cordeles para cada longitud
        vector<long long> dp_min_cost(L + 1, LLONG_MAX); // m�nimo coste para cada longitud

        // Inicializar para longitud 0
        dp_ways[0] = 1;
        dp_min_cords[0] = 0;
        dp_min_cost[0] = 0;

        for (int i = 0; i < n; i++) {
            for (int j = L; j >= leghts[i]; j--) {
                // Actualizar n�mero de formas
                dp_ways[j] += dp_ways[j - leghts[i]]; // Al n�mero de formas de llegar a j, se le suman el numero de formas de llegar a j - leghts[i]

                // Actualizar m�nimo n�mero de cordeles
                if (dp_min_cords[j - leghts[i]] != INT_MAX) {
                    dp_min_cords[j] = min(dp_min_cords[j], dp_min_cords[j - leghts[i]] + 1); // se guarda el valor del numero minimo de cordeles necesarios para llegar a j
                }

                // Actualizar m�nimo coste
                if (dp_min_cost[j - leghts[i]] != LLONG_MAX) {
                    dp_min_cost[j] = min(dp_min_cost[j], dp_min_cost[j - leghts[i]] + costs[i]);//Se guarda el valor del numero minimo de coste necesarios para llegar a j
                }
            }
        }

        if (dp_ways[L] > 0) {
            cout << "SI " << dp_ways[L] << " " << dp_min_cords[L] << " " << dp_min_cost[L] << endl;
        }
        else {
            cout << "NO" << endl;
        }
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