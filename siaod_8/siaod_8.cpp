#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/*
Вариант 16

Метод Ветвей и границ

Задача: В массиве размером M˟N, заполненном нулями и единицами найти квадратный(!) блок, состоящий из одних нулей.

*/

int main() {
	setlocale(LC_ALL, "Russian");
	cout << "Практическая работа №8 \n'Алгоритмические стратегии или методы разработки алгоритмов. Перебор и методы его сокращения'. \n\t\t\tЛуняков Алексей\n"
		"~~~(Размер массива n - количество строк, m - количество столбцов)~~~\n";
	int n, m; 
	cout << "\nВведите размеры массива: (n, m через проблел)\n";
	cin >> m >> n;
	// задаем массив
	vector < vector<int> > mas(n, vector<int>(m));
	cout << "Введите массив: \n";
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			cin >> mas[i][j];

	int mtrx_max = 0; // размер самой большой квадратной матрицы 

	vector<int> d(m, -1), d1(m), d2(m); // вспомогательный одномерный массив хранения значений вспомогательных динамик

	stack<int> safe_stck; // стек хранения коэфициентов расширения границ матрицы

	cout << endl;
	// начинаем анализировать массив
	for (int i = 0; i < n; i++) {	
		// находим верхнюю границу блока: 
		for (int j = 0; j < m; j++) {
			if (mas[i][j] == 1) {
				d[j] = i;
			}
		}
		while (!safe_stck.empty()) {
			safe_stck.pop();
		}
		// нахоим правую границу блока:
		for (int j = m - 1; j >= 0; j--) {
			while (!safe_stck.empty() && d[safe_stck.top()] <= d[j]) {
				safe_stck.pop();
			}
			if (safe_stck.empty()) {
				d2[j] = -1; // расширили макисмально правую границу
			}
			else {
				d2[j] = safe_stck.top(); // продолжаем расширять правую границу
			}
			safe_stck.push(j);
		}
		while (!safe_stck.empty()) {
			safe_stck.pop();
		}
		// находим левую границу блока:
		for (int j = 0; j < m; j++) {
			while (!safe_stck.empty() && d[safe_stck.top()] <= d[j])  {
				safe_stck.pop();
			}
			if (safe_stck.empty()) {
				d1[j] = -1; // расширили макисмально левую границу
			}
			else {
				d1[j] = safe_stck.top(); // продолжаем расширять левую границу
			}
			
			safe_stck.push(j);
		}
		// анализируем найденные блоки
		for (int j = 0; j < m; ++j) {
			float num = 0;
			num = sqrt((i - d[j]) * (d2[j] - d1[j] - 1)); // площадь блока равна: (i - d[j]) * (d2[j] - d1[j] - 1)
			if (num == int(num) && num != 0) {
				//cout << "вехняя граница " << d[j] << " строка, левая граница " << d1[j] << " строка, правая граница " << d2[j] << " строка\n";
				mtrx_max = max(mtrx_max, (i - d[j]) * (d2[j] - d1[j] - 1));
			}
		}
	}
	if (mtrx_max > 0) {
		cout << "Самый большой квадратный блок состоит из " << mtrx_max << " нулей" << endl;
	}
	else {
		cout << "В данном массиве не существует квадратного блока размером больше 1";
	}
}