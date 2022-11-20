#include "graph_h.h"

void DiscGrElem(Graph const& graph, int v, vector<bool>& discov, vector<int>& depart, int& time) {
    
    // �������� ������� ���� ��� ������������
    discov[v] = true;
    for (Edge e : graph.new_graph[v]) {
        int u = e.end;
        // ���� u ��� �� ���������
        if (!discov[u]) {
            DiscGrElem(graph, u, discov, depart, time);
        }
    }

    // ������������� ����� ����������� ������� `v`
    depart[time] = v;
    time++;
}


// ������������ �������� ��������������
void longest_dist(Graph const& graph, int source, int n) {

    // departure[] ������ ����� �������, � ������� ��� ����������
    // ����� ����� ��� �������
    vector<int> depart(n, -1);

    // ����� �����������, ������� ������� ��� ���
    vector<bool> discov(n);
    int time = 0;

    // ��������� ����� � ������� �� ���� ���������� ��������
    for (int i = 0; i < n; i++) {
        if (!discov[i]) {
            DiscGrElem(graph, i, discov, depart, time);
        }
    }

    vector<int> cost(n, INT_MAX);
    cost[source] = 0;

    // ������������ ������� � �������������� �������, �.�. � �������
    // ���������� ������� �� ����������� � DFS
    for (int i = n - 1; i >= 0; i--) {
        // ��� ������ ������� � �������������� �������,
        // �������� ��������� �������� ������
        int v = depart[i];
        for (Edge e : graph.new_graph[v]) {
            // ����� `e` �� `v` �� `u` � ����� `w`
            int u = e.end;
            int w = e.weight * -1; // ������� ��� ����� �������������

            // ���� ���������� �� ������ ���������� `u` ����� ���������
            // ��������� ������������ (v, u), ����� ���������� ��������� �� ������ ����� ������� ��������
            if (cost[v] != INT_MAX && cost[v] + w < cost[u]) {
                cost[u] = cost[v] + w;
            }
        }
    }

    int tmp_cost = 0, k = 0;
    for (int i = 0; i < n-1; i++) {
        if (cost[i+1] * -1 > cost[i] * -1) {
            tmp_cost = cost[i + 1];
            k = i + 1;
        }
    }
    cout << "������������ ���������� ������� ����� ���������: " << source << " � " << k << " - ��� ����� " << setw(2) << tmp_cost * -1;
}


void lowest_dist(Graph const& graph, int start, int end, int n) {
    vector<int> depart(n, -1);
    vector<bool> discov(n);
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (!discov[i]) {
            DiscGrElem(graph, i, discov, depart, time);
        }
    }

    vector<int> cost(n, INT_MAX);
    cost[start] = 0;


    for (int i = n - 1; i >= 0; i--) {
        int v = depart[i];
        for (Edge e : graph.new_graph[v]) {
            int u = e.end;
            int w = e.weight;
            if (cost[v] != INT_MAX && cost[v] + w < cost[u]) {
                cost[u] = cost[v] + w;
            }
        }
    }

    int tmp_cost = 0, k = 0;
    for (int i = 0; i < n - 1; i++) {
        if (i = end) {
            tmp_cost = cost[i];
        }
    }
    cout << "����������� ���������� ����� ���������: " << start << " � " << end << " - ����� " << setw(2) << tmp_cost;
    /*cout << "\n//////////////\n";
    for (int i = 0; i < n; i++) {
        cout << "���������� ����� " << start << " � " << i << " ����� " << setw(2) << cost[i];
        cout << endl;
    }*/
}

void print_graph(Graph const& graph, int n) {
    vector<int> depart(n, -1);

    vector<bool> discov(n);
    int time = 0;

    for (int i = 0; i < n; i++) {
        if (!discov[i]) {
            DiscGrElem(graph, i, discov, depart, time);
        }
    }
    int int_graph[100][100];
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            int_graph[i][j] = 0;
    for (int i = n - 1; i >= 0; i--) {
        int v = depart[i];
        for (Edge e : graph.new_graph[v]) {
            int u = e.end;
            int w = e.weight;
            v--; u--;
            int_graph[v][u] = w;
            v++; u++;
            //cout << ' ' << v << ' ' << u << ' ' << w << '\n';
        }   
    }
    cout << "\n\t������� ��������� �����: \n\t  ";
    for (int i = 0; i < n-1; i++) cout << ' ' << i + 1 << ' ';
    cout << "\n\t";
    int tmp_c = 1;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1; j++) {
            if (j == 0) cout << tmp_c << ' ';
            if (int_graph[i][j]) {
                //cout << " 1 ";
                cout << ' ' << int_graph[i][j] << ' ';
            }
            else cout << " 0 ";
        }
        tmp_c++;
        cout << "\n\t";
    }
}  

void graph_root(Graph const& graph, int n) {
    vector<int> depart(n, -1);

    vector<bool> discov(n);
    int time = 0;

    for (int i = 0; i < n; i++) {
        if (!discov[i]) {
            DiscGrElem(graph, i, discov, depart, time);
        }
    }
    int int_graph[100][100];
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            int_graph[i][j] = 0;
    for (int i = n - 1; i >= 0; i--) {
        int v = depart[i];
        for (Edge e : graph.new_graph[v]) {
            int u = e.end;
            int w = e.weight;
            v--; u--;
            int_graph[v][u] = w;
            v++; u++;
        }
    }
   
    int tmp_c = 1;
    for (int i = 0; i < n - 1; i++) {
        int counter = 0;
        for (int j = 0; j < n - 1; j++) {
            if (int_graph[j][i]) {
                counter++;
            }
        }
        if (counter == 0) {
            cout << "������� " << i + 1 << " �������� ������ ������������� �����\n";
            tmp_c = 0;
        }
        
    }
    if (tmp_c == 1) cout << "����� ������������� ����� ���.";
    cout << endl;
}

// ������� ���� �������
    /*for (int i = 0; i < n; i++)
    {
        cout << "���������� ����� " << source << " � " << i << " ����� " << setw(2) << cost[i] * -1;
        cout << endl;
    }*/
//void or_gr_test(bool (&graph) [1000][1000], int n, int m) {
//    for (int i = 0; i < m; i++) {
//        int u, v;   
//        cout << "������ ������, ���������� ��������� ������, ����� ������: \n";
//        cin >> u >> v;
//        u--, v--; 
//        graph[u][v] = true; //= graph[v][u]; - ��� ���� �����
//    }
//    cout << "\n\n\t  ";
//    for (int i = 0; i < n; i++) cout << ' ' << i + 1 << ' ';
//    cout << "\n\t";
//    int tmp_c = 1;
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            if (j == 0) cout << tmp_c << ' ';
//            if (graph[i][j]) {
//                cout << " 1 ";
//            }
//            else cout << " 0 ";
//        }
//        tmp_c++;
//        cout << "\n\t";
//    }
//
//}
//
//void or_gr_print(bool(&graph)[1000][1000], int n) {
//    cout << "\n\n\t  ";
//    for (int i = 0; i < n; i++) cout << ' ' << i + 1 << ' ';
//    cout << "\n\t";
//    int tmp_c = 1;
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            if (j == 0) cout << tmp_c << ' ';
//            if (graph[i][j]) {
//                cout << " 1 ";
//            }
//            else cout << " 0 ";
//        }
//        tmp_c++;
//        cout << "\n\t";
//    }
//}
//
//void find_root(bool(&graph)[1000][1000], int n) {
//    int tmp_c = 1;
//    bool tmp[1000] = { false };
//    for (int i = 0; i < n; i++) {
//        for (int j = 1; j < n; j++) {
//            if (graph[i][j]) {
//                cout << "!";
//            }
//        }
//        tmp_c++;
//        cout << "\n\t";
//    }
//    cout << "wtf";
//}