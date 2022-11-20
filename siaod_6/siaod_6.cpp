#include "gr_source.hpp"

/*Вариант 16. Матрица смежности

Найти корень ациклического графа.
Составить программу нахождения самого длинного пути в ациклическом графе. 
Вывести кратчайший путь между двумя заданными вершинами.

*/

void local_menu() {
    setlocale(LC_ALL, "Russian");
    cout << "Практикум №6 'Основные алгоритмы работы с графами.'. Алексей Луняков\n";
    cout << "Список команд для выполнения: \n"
        "\n"
        "1. Вывод графа на экран.\n"
        "-----------------------------\nИндивидуальные задания Вариант 16.\n"
        "2. Поиск корня ациклического графа. \n"
        "3. Нахождение самого длинного пути в ациклическом графе.\n"
        "4. Вывод кратчайшего пути между двумя заданными вершинами. \n"
        "5. Повторить главное меню. \n"
        "Любое другое число завершает работу программы.\n";
}


int main() {
    int mnum;
    bool main = true;
    bool flag = true;
    local_menu();
    int n, m;
    Edge edge;
    vector<Edge> edges;
    
    cout << "Ввод графа с клавиатуры (метод добавления одного ребра): \nВведите количество вершин и ребер через пробел: ";
    cin >> n >> m;
    n++;
    int tmp_m = m;
    cout << "Введите значения в формате {(вершина) пробел (вершина) пробел (вес ребра)}\n";
    while (tmp_m > 0) {
        int tmp, tmp2, wght;
        // ввод данных ребра 
        cin >> tmp >> tmp2 >> wght;
        // создание ребра (присвоение полям значений)
        edge.start = tmp;
        edge.end = tmp2;
        edge.weight = wght;
        // и добавление его в граф
        edges.push_back(edge);
        tmp_m--;
    }
    // создание графа 
    Graph graph(edges, n);
    
    while (main) {
        int val;
        cout << "\nВведите вашу команду меню: \n";
        cin >> mnum;
        switch (mnum) {
        case 1: {
            // Вывод графа
            print_graph(graph, n);
            break;
        }
        case 2: {
            cout << "\nТаблица смежности вашего графа: \n";
            print_graph(graph, n);
            //cout << "\nКорень ациклического графа: \n";
            //int i = 1;
            cout << endl;
            graph_root(graph, n);
            break;
        }
        case 3: {
            // поиск самого длинного пути в ациклическом графе от вершины
            cout << "Введите начальную вершину ацикличского графа: ";
            int start;
            cin >> start;
            longest_dist(graph, start, n);
            break;
        }
        case 4: {
            // поиск кратчайшего пути между вершинами
            cout << "Введите начальную и конечную вершину через пробел: ";
            int start, end;
            cin >> start >> end;
            lowest_dist(graph, start, end, n);
            break;
        }
        case 5: {
            local_menu();
            break;
        }
        default:
            main = false;
            break;
        }
    }

}


/*{
        { 0, 6, 2 }, { 1, 2, -4 }, { 1, 4, 1 }, { 1, 6, 8 }, { 3, 0, 3 }, { 3, 4, 5 },
        { 5, 1, 2 }, { 7, 0, 6 }, { 7, 1, -1 }, { 7, 3, 4 }, { 7, 5, -4 }
    };*/

//while (_getch() != 27) {
//    cout << "Enter value (press ESC to complete entry) ";
//    cin >> val;
//    //buildBinTree(val, &Tree);
//}
//print_BT(&Tree, 0);

//bool graph[1000][1000] = { false };
//or_gr_test(graph, n, m);
//or_gr_print(graph, n);