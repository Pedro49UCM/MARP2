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
	int O, S;
	while (cin >> O >> S) {
		vector<int> secciones(S);
		for (int i = 0; i < S; i++) {
			cin >> secciones[i];
		}
		vector<int> dp_min_dards(O + 1, INT_MAX); // m�nimo n�mero de dardos para cada puntuacion
        vector<int> backtrack(O + 1, -1); // Para rastrear qu� puntuaci�n llev� al estado �ptimo


        // Inicializar para longitud 0
        dp_min_dards[0] = 0;


        // Programaci�n din�mica
        for (int i = 0; i < S; ++i) {
            for (int j = secciones[i]; j <= O; ++j) {
                if (dp_min_dards[j - secciones[i]] != INT_MAX && dp_min_dards[j - secciones[i]] + 1 <= dp_min_dards[j]) {
                    // Actualizar si encontramos una soluci�n m�s corta o igual
                    if (dp_min_dards[j - secciones[i]] + 1 < dp_min_dards[j] ||
                        (backtrack[j - secciones[i]] != -1 && secciones[i] > secciones[backtrack[j]])) {
                        dp_min_dards[j] = dp_min_dards[j - secciones[i]] + 1;
                        backtrack[j] = i; // Guardamos el �ndice de la puntuaci�n usada
                    }
                }
            }
        }
        // Construir resultado
        if (dp_min_dards[O] == INT_MAX) {
            cout << "Imposible" << endl;
        }
        else {
            cout << dp_min_dards[O] << ":";
            vector<int> resultado;
            int current = O;

            // Rastreamos las puntuaciones utilizadas
            while (current > 0) {
                resultado.push_back(secciones[backtrack[current]]);
                current -= secciones[backtrack[current]];
            }

            // Ordenar las puntuaciones de mayor a menor
            sort(resultado.rbegin(), resultado.rend());

            for (int puntuacion : resultado) {
                cout << " " << puntuacion;
            }
            cout << endl;
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