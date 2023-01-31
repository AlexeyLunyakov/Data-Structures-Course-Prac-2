#include "siaod_5_bt_head.h"
#include <vector>
#include <chrono>
#include <fstream>

void umenu() {
    cout << "1. Построение дерева по существующему файлу \n"
        "2. Добавление элемента в дерево \n"
        "3. Поиск по ключу в дереве \n"
        "4. Удаление элемента из дерева \n"
        "5. Вывод дерева в форме дерева \n"
        "Любой другой номер приводит к выходу в меню выбора дерева.\n";
}

void bts_menu() {
    cout << "\nБинарное дерево поиска. Список команд для выполнения: \n";
    umenu();
}

void brt_menu() {
    cout << "\nКрасно-черное дерево. Список команд для выполнения: \n";
    umenu();
}

void buildBTS(int val, int pos, BinTreeS** new_tree) {
    if ((*new_tree) == nullptr) {
        (*new_tree) = new BinTreeS;
        //Помещение в выделенное место нового значения
        (*new_tree)->value = val;
        (*new_tree)->file_pos = pos;
        //Создаем пустые ветки от текущего элемента
        (*new_tree)->left = (*new_tree)->right = nullptr;
        return;
    }
    if (val > (*new_tree)->value) {
        buildBTS(val, pos, &(*new_tree)->right); //Если аргумент больше чем текущий элемент, поместить его вправо
    }
    else {
        buildBTS(val, pos, &(*new_tree)->left); //Иначе поместить его влево
    }
}

int Node_count(BinTreeS* Tree) {
    if (Tree == nullptr) return 0;
    return Node_count(Tree->left) + 1 + Node_count(Tree->right);
}

void print_BTS(BinTreeS** Tree, int l) {
    int i;
    if (*Tree != nullptr) {
        print_BTS(&((**Tree).right), l + 1);
        for (i = 1; i <= l; i++) cout << "   ";
        cout << (**Tree).value << " " << (**Tree).file_pos << endl;
        print_BTS(&((**Tree).left), l + 1);
    }
}

void print_tree_s2(BinTreeS const*Tree, string const& znaki = "\t", bool in_root = true, bool last_elem = true) {
    if (in_root) {
        if (Tree) {
            cout << znaki << to_string(Tree->value) << " " << to_string(Tree->file_pos) << endl;
        }
        else {
            cout << znaki << endl;
        }
    }
    else {
        if (last_elem) {
            if (Tree) {
                cout << znaki << "|-" << to_string(Tree->value) << " " << to_string(Tree->file_pos) << endl;
            }
            else {
                cout << znaki << endl;
            }
        }
        else {
            if (Tree) {
                cout << znaki << "\\-" << to_string(Tree->value) << " " << to_string(Tree->file_pos) << endl;
            }
            else {
                cout << znaki << endl;
            }
        }
    }
    if (!Tree || (!Tree->left && !Tree->right)) {
        return;
    }
    else {
        vector<BinTreeS*> v{ Tree->left, Tree->right };
        for (size_t i = 0; i < v.size(); ++i) {
            if (in_root) {
                print_tree_s2(v[i], znaki, false, i + 1 >= v.size());
            }
            else {
                if (last_elem) {
                    print_tree_s2(v[i], znaki + "  ", false, i + 1 >= v.size());
                }
                else {
                    print_tree_s2(v[i], znaki + "| ", false, i + 1 >= v.size());
                }
            }
        }
    }
}

BinTreeS* Search(BinTreeS* Tree, int key) {
    if (Tree == NULL) {
        return NULL;
    }
    if (Tree->value == key) {
        return Tree;
    }
    if (key < Tree->value) {
        return Search(Tree->left, key);
    }
    else {
        return Search(Tree->right, key);
    }
}

void Del_search(BinTreeS* Tree, int key) {
    if (Tree->right->value == key && Tree->right != nullptr) {
        Tree->right = nullptr;
    }
    else if (Tree->left->value == key && Tree->left != nullptr) {
        Tree->left = nullptr;
    }
    else if (Tree->right->value > key && Tree->right != nullptr) {
        Del_search(Tree->left, key);
    }
    else if (Tree->left->value > key && Tree->left != nullptr) {
        Del_search(Tree->right, key);
    }
    else { cout << "---------"; }
}

void file_to_bts(string BinName, BinTreeS** new_tree) {
    ifstream fileBin(BinName, ios::binary);
    Schedule TT;
    string new_str;
    int pos = 0;
    fileBin.read((char*)&TT, sizeof(Schedule));
    while (!fileBin.eof()) {
        int key = TT.gr_num;
        buildBTS(key, pos, new_tree);
        fileBin.read((char*)&TT, sizeof(Schedule));
        pos++;
    }
    fileBin.close();
}

void file_to_brt(string BinName, RedBlackTree* new_tree) {
    ifstream fileBin(BinName, ios::binary);
    Schedule TT;
    string new_str;
    int pos = 0;
    fileBin.read((char*)&TT, sizeof(Schedule));
    while (!fileBin.eof()) {
        int key = TT.gr_num;
        new_tree->insert(key, pos);
        fileBin.read((char*)&TT, sizeof(Schedule));
        pos++;
    }
    fileBin.close();
}

void testTreeBTS(bool flag) {
    bts_menu();
    string inp_file, outp_file;
    ifstream inp;
    ofstream outp;
    int c;
    bool tmp = true;
    BinTreeS* Tree = nullptr;
    while (tmp) {
        cout << "\nНомер команды: ";
        cin >> c;
        switch (c) {
        case 1: {
            inp_file = "";
            cout << "Введите имя бинарного файла:\n";
            cin >> inp_file;
            if (inp.good()) {
                cout << "\nПеревод всей структуры из файла в бинарное дерево поиска:\n";
                file_to_bts(inp_file, &Tree);
                //print_BTS(&Tree, 0);
            }
            else {
                cout << "Файла с таким именем не существует";
            }
            break;
        }
        case 2: {
            outp_file = "";
            cout << "Введите имя бинарного файла:\n";
            cin >> outp_file;
            outp.open(outp_file, ios::binary | ios::out | ios::app);
            if (outp.good()) {
                cout << "Добавляем новый элемент в текущее дерево: \n";
                int val, pos;
                Schedule tt;
                while (_getch() != 27) {
                    //string tmp_str;
                    cout << "Введите значение и позицию в файле (для завершения ввода нажмите ESC) ";
                    cin >> val >> pos;
                    tt.gr_num = val;
                    cout << "Введите значения структуры (название предмета, номер пары, номер недели, номер дня, тип пары, номер кабинета): \n";
                    cin >> tt.sub_name >> tt.les_num >> tt.week_num >>
                        tt.day_num >> tt.sub_type >> tt.class_num;
                    buildBTS(val, pos, &Tree);
                    outp.write((char*)&tt, sizeof(Schedule));
                }
                outp.close();
                cout << "Итоговое дерево: \n";
                print_BTS(&Tree, 0);
            }
            else {
                cout << "Файла с таким именем не существует";
            }
            break;
        }
        case 3: {
            cout << "Введите имя бинарного файла:\n";
            inp_file = "";
            cin >> inp_file;
            int key;
            ifstream check(inp_file);
            if (check.is_open()) {
                cout << "Введите ключевое значение для поиска: \n";
                cin >> key;

                    // подсчет времени
                    auto start_time = chrono::steady_clock::now();

                BinTreeS* Tree1 = Search(Tree, key);

                    auto end_time = chrono::steady_clock::now();
                    auto interval = chrono::duration_cast <chrono::nanoseconds> (end_time - start_time);
                    
                if (Tree1 == NULL) {
                    cout << "Элемент не найден\n";
                }
                else {
                    cout << "Ваш элемент -> " << Tree1->value << " позиция в файле -> " << Tree1->file_pos << "\n";
                    int pos_num = Tree1->file_pos;
                    Schedule tt = get_struct(inp_file, pos_num);
                    cout << "Ваша запись (бинарный файл): \n";
                    cout << tt.gr_num << ' ' << tt.sub_name << ' ' << tt.les_num << ' '
                        << tt.week_num << ' ' << tt.day_num << ' ' << tt.sub_type << ' ' << tt.class_num << '\n';
                }
                cout << "\nВремя: " << interval.count() / pow(10, 6) << " ms\n\n";
            }
            else {
                cout << "Файла с таким именем не существует";
            }
            break;
        }
        case 4: {
            cout << "Введите имя бинарного файла: \n";
            inp_file = "";
            cin >> inp_file;
            ifstream check(inp_file);
            if (check.is_open()) {
                int key;
                cout << "Введите значение элемента для удаления: \n";
                cin >> key;
                remove_struct(inp_file, key);
                Del_search(Tree, key);
                cout << "\nИтоговое дерево: \n";
                print_BTS(&Tree, 0);
            }
            else {
                cout << "Файла с таким именем не существует";
            }         
            break;
        }
        case 5: {
            cout << "Построенное дерево: \n";
            //print_BTS(&Tree, 0);
            print_tree_s2(Tree);
            break;
        }
        default: 
            tmp = false;
            break;
        }
    }
}

void testTreeBRT(bool flag) {
    brt_menu();
    string inp_file, outp_file;
    ifstream inp;
    ofstream outp;
    int c;
    bool tmp = true;
    RedBlackTree RBTree;
    while (tmp) {
        cout << "\nНомер команды: ";
        cin >> c;
        switch (c) {
        case 1: {
            inp_file = "";
            cout << "Введите имя бинарного файла:\n";
            cin >> inp_file;
            if (inp.good()) {
                cout << "\nПеревод всей структуры из файла в красно-черное дерево:\n";
                file_to_brt(inp_file, &RBTree);
                //RBTree.printTree();
                inp.close();
            }
            else {
                cout << "Файла с таким именем не существует";
                inp.close();
            }
            break;
        }
        case 2: {
            outp_file = "";
            cout << "Введите имя бинарного файла:\n";
            cin >> outp_file;
            outp.open(outp_file, ios::binary | ios::out | ios::app);
            if (outp.good()) {
                cout << "Добавляем новый элемент в текущее дерево: \n (для завершения ввода нажмите ESC)\n";
                int val, pos;
                Schedule tt;
                while (_getch() != 27) {
                    string tmp_str;
                    cout << "Введите значение и позицию в файле через пробел: ";
                    cin >> val >> pos;

                    tt.gr_num = val;
                    cout << "Введите значения структуры (название предмета, номер пары, номер недели, номер дня, тип пары, номер кабинета): \n";
                    cin >> tt.sub_name >> tt.les_num >> tt.week_num >>
                        tt.day_num >> tt.sub_type >> tt.class_num;

                    RBTree.insert(val, pos);
                    outp.write((char*)&tt, sizeof(Schedule));
                }
                cout << "Итоговое дерево: \n";
                RBTree.printTree();
                outp.close();
            }
            else {
                cout << "Файла с таким именем не существует";
            }
            break;
        }
        case 3: {
            cout << "Введите имя бинарного файла:\n";
            inp_file = "";
            cin >> inp_file;
            ifstream check(inp_file);
            if (check.is_open()) {
                int key;
                cout << "Введите значение элемента для поиска: \n";
                cin >> key;
                int pos_num = 0;
                ifstream tmp(inp_file, ios::binary | ios::in);
                int c = line_counter(tmp);
                //cout << c << endl;
                tmp.close();
                if (pos_num < c) {

                        // подсчет времени
                        auto start_time = chrono::steady_clock::now();

                    // функция поиска КЧД
                    Node_ptr elem = RBTree.search_brt(key);

                        auto end_time = chrono::steady_clock::now();
                        auto interval = chrono::duration_cast <chrono::nanoseconds> (end_time - start_time);

                    cout << "Ваш элемент -> " << elem->data << " пвф -> " << elem->fpos << "\n";
                    pos_num = elem->fpos;
                    Schedule tt = get_struct(inp_file, pos_num);

                    cout << "Ваша запись (бинарный файл): \n";
                    cout << tt.gr_num << ' ' << tt.sub_name << ' ' << tt.les_num << ' '
                        << tt.week_num << ' ' << tt.day_num << ' ' << tt.sub_type << ' ' << tt.class_num << '\n';
                    
                    cout << "\nВремя: " << interval.count() / pow(10, 6) << " ms\n\n";
                }
                else {
                    cout << "Найденной позиции в файле не существует.\n";
                }
            }
            else {
                cout << "Файла с таким именем не существует";            
            }
            break;
        }
        case 4: {
            cout << "Введите имя бинарного файла: \n";
            inp_file = "";
            cin >> inp_file;
            ifstream check(inp_file);
            if (check.is_open()) {
                check.close();
                int key;
                cout << "Введите значение элемента для удаления: \n";
                cin >> key;
                remove_struct(inp_file, key);
                RBTree.deleteNode(key);
                cout << "\nИтоговое дерево: \n";
                RBTree.printTree();
                inp.close();
            }
            else {
                cout << "Файла с таким именем не существует";
                inp.close();
            }
            break;
        }
        case 5: {
            cout << "Построенное дерево: \n";
            RBTree.printTree();
            break;
        }
        default:
            tmp = false;
            break;
        }
    }
}
