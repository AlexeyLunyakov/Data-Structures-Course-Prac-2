#ifndef SIAOD_6_GR_HEAD_H
#define SIAOD_6_GR_HEAD_H

#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>
//#include <cmath>
//#include <Windows.h>
//#include <conio.h>
using namespace std;

// Структура данных для хранения ребра
struct Edge {
    int start, end, weight;
};

class Graph {
public:
    // вектор векторов для представления списка смежности
    vector<vector<Edge>> new_graph;

    // Конструктор
    Graph(vector<Edge> const& edges, int n) {
        // изменить размер вектора, чтобы он содержал `n` элементов типа vector<Edge>
        new_graph.resize(n);

        // добавляем ребра в ориентированный граф
        for (Edge const& edge : edges) {
            new_graph[edge.start].push_back(edge);
        }
    }
};

#endif //SIAOD_6_GR_HEAD_H