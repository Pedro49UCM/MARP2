#include<fstream>
#include<iostream>
#include<vector>
#include<queue>
#include <algorithm>
#include <climits>
using namespace std;

/*
RECURSION
Parametros:
    i es el index de la seccion
    j es la puntuacion a la que se quiere llegar con esa seccion
    dp_min_dards es el vector que guarda el numero minimo de secciones para llegar a la puntuacion j
    backtrack es el vector que guarda la ultima seccion utilizada para legar a la puntuacion j
Rangos:
    las secciones van de la 0 a la S
    los vectores solucion van del 0 a O+1
Casos base: 
    if (dp_min_dards[j - secciones[i]] == INT_MAX || dp_min_dards[j - secciones[i]] + 1 == dp_min_dards[j]) break;
Casos recursivos:
    if (dp_min_dards[j - secciones[i]] != INT_MAX && dp_min_dards[j - secciones[i]] + 1 <= dp_min_dards[j])
        calculate vector values at j
        j++

*/
/*
IMPLEMENACION
Iterativo: 
    Como relleno el vector:
        Primero itero por las secciones, de la 1 a la n, y despues con cada seccion voy iterndo desde
        la puntuacion de la seccion hasta la puntuacion objectivo,  asi que voy rellenando de forma ascendente,
        para asi poder tener el numero minimo de secciones para llegar a j, y añadir las secciones a backtrack
*/
/*
COSTE DE RELLENADO DE LA MATRIZ:
Tiempo: O(S*O)
Espacio: O(O)
    El espacio ya esta reducido a 1 dimension por lo que no se podría reducir más ya que necesitamos los valores de diversas puntciones
*/
/*
RECONSTRUCCION:
Algoritmo:
    Dado que ya tengo la resconstruccion en backtrack, el algoritmo consiste en iterar por backtrack, para ir sacando las secciones 
    que se han ido utilizando, pues al tener gurdada backrack la ultima seccion, puedes iterar restamdo la puntuacion de esa seccion
Coste: 
    Tiempo:O(O)
    Espacio: O(S)
*/

void solve() {
	int n;
	while (cin >> n) {
		vector<vector<int>> matriz(n, vector<int>(n));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> matriz[i][j];
			}
		}
		vector<int> sumaAnetior(n, 0);
		vector<int> sumaNueva(n);
		for (int r = 0; r < n; r++) {
			for (int c = 0; c < n; c++) {
				int maxi = sumaAnetior[c];
				if (c - 1 >= 0 && maxi < sumaAnetior[c - 1]) {
					maxi = sumaAnetior[c - 1];
				}			
				if (c + 1 < n  && maxi< sumaAnetior[c + 1]) {
					maxi = sumaAnetior[c + 1];
				}
				sumaNueva[c] = maxi + matriz[r][c];
				//cout << "ROW:" << r << " COL:" << c << " suma:" << sumaNueva[c] << " columnaInicial:" << columnaNueva[c] << endl;
			}
			sumaAnetior = sumaNueva;
		}
		int maxi = -1;
		int c;
		for (int i = 0; i < n; i++) {
			if (sumaAnetior[i] > maxi) {
				maxi = sumaAnetior[i];
				c = i;
			}
		}
		cout << maxi << " " << c + 1 << endl;
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