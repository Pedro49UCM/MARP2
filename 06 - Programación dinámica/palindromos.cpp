#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include <algorithm>
#include <climits>
using namespace std;

//Calcula la lonjitud máxima entre i y j
int palin_rec(string const& palabra, int i, int j, vector<vector<int>>& palin) {
	int& res = palin[i][j];
	if (res == -1) {
		if (i > j)
			res = 0;
		else if (i == j)
			res = 1;
		else if (palabra[i] == palabra[j])
			res = palin_rec(palabra, i + 1, j - 1, palin) + 2;
		else
			res = max(palin_rec(palabra, i, j - 1, palin), palin_rec(palabra, i + 1, j, palin));
	}
	return res;
}

string reconstruir(string const& palabra, vector<vector<int>> const& palin, int i, int j) {
	if (i > j)return{};
	if (i == j)return { palabra[i] };
	if (palabra[i] == palabra[j])
		return palabra[i] + reconstruir(palabra, palin, i + 1, j - 1) + palabra[i];
	else if (palin[i][j] == palin[i + 1][j])
		return palabra[i]+ reconstruir(palabra, palin, i + 1, j)+ palabra[i];
	else
		return  palabra[j]+ reconstruir(palabra, palin, i, j-1) + palabra[j];
}

void solve() {
	string palabra;
	while (cin >> palabra) {
		vector<vector<int>> palin(palabra.size(), vector<int>(palabra.size(), -1));
		int size = palin_rec(palabra, 0, palabra.size() - 1, palin);
		string answer = reconstruir(palabra, palin, 0, palabra.size() - 1);
		cout << palabra.size() -size << " " << answer << endl;
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