#include <conio.h>
#include <memory.h>
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

#define N 8
#define E 15
const int MAX_E = (int)1000000;
const int MAX_V = (int)1000;
const int INF = (int)1000000000;

int firstVert[MAX_V], visited[MAX_V];
int edgeCount = 0, capacity[MAX_E], onEnd[MAX_E], nextEdge[MAX_E];

int read_matrix(int matr[N][N]) {
	ifstream in("l4-1.txt");
	if (in.is_open())
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				in >> matr[i][j];

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				cout << matr[i][j] << "\t";
			cout << "\n";
		}

		in.close();
		return **matr;
	}
	else
	{
		cout << "Файл не знайдено.";
		return 0;
	}
}

int find_way(int matr[N][N], int min[E], int way[N]) {
	int v = 1;
	int u, i = 0;
	stack <int> plan;
	plan.push(--v);

	matr[v][v] = 1; 
	int counter = 1;  
	do {
		way[i] = v;
		plan.pop();     
		for (u = 0; u < N; u++) { 
			if (matr[v][u] > 0 && !matr[u][u]) { 
				i++;
				if (u == N) {
					break;
				}
				if (matr[v][N - 1] != 0) {
					u = N - 1;
					plan.push(u);   
					matr[u][u] = 1; 
					cout << v + 1 << ", " << u + 1 << " - " << matr[v][u] << endl;
					min[u] = matr[v][u];
					way[i] = u;
				}
				else {
					plan.push(u);    
					matr[u][u] = 1;
					counter++;      
					cout << v + 1 << ", " << u + 1 << " - " << matr[v][u] << endl;
					min[u] = matr[v][u];
					v = u;
					way[i] = v;
				}
			}
		}
	} while (false);
	return *min, * way;
}

int find_flow(int matr[N][N]) {
	int min[N], way[N], minim, max = 0;
	int w;
	bool flag;

	do {
		w = 0;
		minim = INF;
		flag = false;
		cout << "\tШлях: \n";
		find_way(matr, min, way);

		for (int i = 0; i < N; i++) {
			if (minim >= min[i] && min[i] > 0) {
				minim = min[i];
			}
		}
		cout << "Мiнiмум шляху - " << minim << endl;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (matr[i][i] != 0) {
					if (i != N - 1) {
						matr[i][i] = 0;
						matr[way[w]][way[w + 1]] = matr[way[w]][way[w + 1]] - minim;
						w++;
					}
					else {
						matr[i][i] = 0;
					}
				}
			}
		}

		for (int i = 0; i < N; i++) {
			if (way[i] == N - 1) {
				flag = true;
				cout << " + Додаємо шлях до суми" << endl;
			}
		}

		cout << "__________________________________________\n";

		if (flag == true) {
			max += minim;
			for (int i = 0; i < N; i++) {
				way[i] = 0;
			}
		}
		else {
			cout << "\n\tМiнiмальний розрiз мережi: ";
			for (int i = 0; i < N; i++) {
				if (way[i] >= 0 && way[i + 1] > 0) {
					cout << way[i] + 1 << ", " << way[i + 1] + 1 << endl;
				}
			}
		}


	} while (flag == true);

	cout << "\tМаксимальний потiк - " << max << endl << endl;
	return 0;
}

void main()
{
	setlocale(LC_ALL, "Ukrainian");
	int matr[N][N];

	cout << "Кiлькiсть вершин: " << N << endl;
	cout << "Матриця ваг: " << endl;
	read_matrix(matr);
	find_flow(matr);


	system("pause");
}