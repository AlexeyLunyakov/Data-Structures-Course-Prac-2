#include "graph_h.h"

void DiscGrElem(Graph const& graph, int v, vector<bool>& discov, vector<int>& depart, int& time) {
    
    // помечаем текущий узел как обнаруженный
    discov[v] = true;
    for (Edge e : graph.new_graph[v]) {
        int u = e.end;
        // если u еще не обнаружен
        if (!discov[u]) {
            DiscGrElem(graph, u, discov, depart, time);
        }
    }

    // устанавливаем врем€ отправлени€ вершины `v`
    depart[time] = v;
    time++;
}


// »спользуетс€ алгоритм ЅеллманаЦ‘орда
void longest_dist(Graph const& graph, int source, int n) {

    // departure[] хранит номер вершины, с которой оно отправлено
    // врем€ равно его индексу
    vector<int> depart(n, -1);

    // чтобы отслеживать, открыта вершина или нет
    vector<bool> discov(n);
    int time = 0;

    // выполн€ем поиск в глубину на всех неоткрытых вершинах
    for (int i = 0; i < n; i++) {
        if (!discov[i]) {
            DiscGrElem(graph, i, discov, depart, time);
        }
    }

    vector<int> cost(n, INT_MAX);
    cost[source] = 0;

    // ќбрабатываем вершины в топологическом пор€дке, т.е. в пор€дке
    // уменьшени€ времени их отправлени€ в DFS
    for (int i = n - 1; i >= 0; i--) {
        // дл€ каждой вершины в топологическом пор€дке,
        // ослабить стоимость соседних вершин
        int v = depart[i];
        for (Edge e : graph.new_graph[v]) {
            // ребро `e` от `v` до `u` с весом `w`
            int u = e.end;
            int w = e.weight * -1; // сделать вес ребра отрицательным

            // если рассто€ние до пункта назначени€ `u` можно сократить
            // получение преимущества (v, u), затем обновление стоимости до нового более низкого значени€
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
    cout << "ћаксимальное рассто€ние найдено между вершинами: " << source << " и " << k << " - оно равно " << setw(2) << tmp_cost * -1;
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
    cout << "ћинимальное рассто€ние между вершинами: " << start << " и " << end << " - равно " << setw(2) << tmp_cost;
    /*cout << "\n//////////////\n";
    for (int i = 0; i < n; i++) {
        cout << "–ассто€ние между " << start << " и " << i << " равно " << setw(2) << cost[i];
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
    cout << "\n\tћатрица смежности графа: \n\t  ";
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
            cout << "¬ершина " << i + 1 << " €вл€етс€ корнем ациклического графа\n";
            tmp_c = 0;
        }
        
    }
    if (tmp_c == 1) cout << " орн€ ациклического графа нет.";
    cout << endl;
}

// вывести пути вершины
    /*for (int i = 0; i < n; i++)
    {
        cout << "–ассто€ние между " << source << " и " << i << " равно " << setw(2) << cost[i] * -1;
        cout << endl;
    }*/
//void or_gr_test(bool (&graph) [1000][1000], int n, int m) {
//    for (int i = 0; i < m; i++) {
//        int u, v;   
//        cout << "Ќомера вершин, соединЄнных очередным ребром, через пробел: \n";
//        cin >> u >> v;
//        u--, v--; 
//        graph[u][v] = true; //= graph[v][u]; - дл€ неор графа
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