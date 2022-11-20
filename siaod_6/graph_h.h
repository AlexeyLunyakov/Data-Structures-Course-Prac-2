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

// ��������� ������ ��� �������� �����
struct Edge {
    int start, end, weight;
};

class Graph {
public:
    // ������ �������� ��� ������������� ������ ���������
    vector<vector<Edge>> new_graph;

    // �����������
    Graph(vector<Edge> const& edges, int n) {
        // �������� ������ �������, ����� �� �������� `n` ��������� ���� vector<Edge>
        new_graph.resize(n);

        // ��������� ����� � ��������������� ����
        for (Edge const& edge : edges) {
            new_graph[edge.start].push_back(edge);
        }
    }
};

#endif //SIAOD_6_GR_HEAD_H