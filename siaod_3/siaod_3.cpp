#include "siaod_3_head.h"
#include "siaod_3_hesh_head.h"
#include "siaod_3_source.cpp"
#include "siaod_3_hashsource.cpp"

void main_menu() {
    setlocale(LC_ALL, "Russian");
    cout << "Практическая работа №3 'Хеш-таблица для поиска записи в файле'. Луняков Алексей\n";
    cout << "Список команд для выполнения: \n"
        "1. Управление хэш-таблицей. \n"
        "2. Управление двоичным файлом. \n"
        "3. Управление двоичным файлом с помощью хэш-таблицы. \n"
        "Любой другой номер приводит к завершению программы.\n";
}

void file_to_table(string BinName, HashTable& hash_t) {
    
    ifstream fileBin(BinName, ios::binary);
    Schedule TT;
    unsigned long long count = 0;
    string new_str;

    fileBin.read((char*)&TT, sizeof(Schedule));
    while (!fileBin.eof()) {
        int key = TT.gr_num;
        hash_t.insertItem(key, count);
        fileBin.read((char*)&TT, sizeof(Schedule));
        count++;
    }
    fileBin.close();
}

void bin_hash_menu() {
    setlocale(LC_ALL, "Russian");
    cout << "Раздел управления двоичным файлом с помощью хеш-таблицы. \nСписок команд для выполнения: \n"
        "1. Прочитать записи из файла и вставить элементы в таблицу \n"
        "2. Добавление элемента в конец файла и таблицы\n"
        "3. Удалить запись из таблицы при заданном значении ключа и соответственно из файла. \n"
        "4. Найти запись в файле по значению хеш-ключа. \n"
        "5. Вывести таблицу. \n"
        "Любой другой номер приводит к выходу к главному меню.\n";
}

int main() {
    string inp_file, outp_file;
    ifstream inp;
    ofstream outp;
    int mnum, num;
    bool main = true;
    bool flag = true;
    main_menu();
    while (main) {
        cout << "\nВведите команду главного меню:\n";
        cin >> mnum;
        switch (mnum) {
        case 1: {
            // Управление хеш-таблицей
            testHeshT(true);
            break;
        }
        case 2: {
            // Управление двоичным файлом (2 работа)
            testBinF(true);
            break;
        }
        case 3: {
            // Управление двоичным файлом с помошью хеш-таблицы
            bin_hash_menu();
            int size = 15;
            HashTable TT(size);
            while (flag) {
                cout << "\nВведите новую команду:\n";
                cin >> num;
                switch (num) {
                case 1: {
                    inp_file = "";
                    cout << "Введите имя бинарного файла:\n";
                    cin >> inp_file;
                    if (inp.good()) {
                        cout << "\nПеревод всей структуры из файла в таблицу:\n";
                        file_to_table(inp_file, TT);
                        TT.displayHash();
                    }
                    else {
                        cout << "Файла с таким именем не существует.";
                    }
                    break;
                }
                case 2: {
                    inp_file = "";
                    int tmp, tmp_h;
                    cout << "Введите имя бинарного файла:\n";
                    cin >> inp_file;
                    if (inp.good()) {
                        cout << "\nВведите номер записи в файле:\n";
                        cin >> tmp;
                        Schedule tt = get_struct(inp_file, tmp);
                        tmp = tt.gr_num;
                        cout << "\nВведите номер в таблице:\n";
                        cin >> tmp_h; 
                        TT.insertItem(tmp, tmp_h);
                        inp.close();
                    }
                    else {
                        cout << "Файла с таким именем не существует.";
                    }
                    break;
                }
                case 3: {
                    inp_file = "";
                    int key_val;
                    cout << "Введите имя бинарного файла: \n";
                    cin >> inp_file;

                    ifstream check(inp_file);
                    if (check.is_open()) {
                        cout << "Введите ключевое значение структуры:\n";
                        cin >> key_val;
                        TT.deleteItem(key_val);
                        remove_struct(inp_file, key_val);
                    }
                    else {
                        cout << "Файла с таким именем не существует. ";
                    }
                    break;
                }
                case 4: {
                    inp_file = "";
                    int pos_num, h_num;
                    cout << "Введите имя бинарного файла: \n";
                    cin >> inp_file;
                    ifstream check(inp_file);
                    if (check.is_open()) {
                        cout << "Введите ключ: \n";
                        cin >> h_num;
                        Node* ans = TT.searchItem(h_num);
                        pos_num = ans->position;
                        cout << "Ключевое значение структуры: " << h_num << "\nПозиция в файле: " << ans->position << "\n";
                        /*cout << "Введите номер нужной строки: \n";
                        cin >> pos_num;*/
                        ifstream tmp(inp_file, ios::binary | ios::in);
                        int c = line_counter(tmp);
                        //cout << c << endl;
                        tmp.close();
                        if (pos_num < c) {
                            

                            Schedule tt = get_struct(inp_file, pos_num);
                            cout << "Ваша запись (бинарный файл): \n";
                            cout << tt.gr_num << ' ' << tt.sub_name << ' ' << tt.les_num << ' '
                                << tt.week_num << ' ' << tt.day_num << ' ' << tt.sub_type << ' ' << tt.class_num << '\n';
                        }
                        else {
                            cout << "Введено слишком большое число.\n";
                        }

                    }
                    else {
                        cout << "Файла с таким именем не существует. ";
                    }
                    break;
                }   
                case 5: {
                    TT.displayHash();
                    break;
                }
                default:
                    flag = false;
                    break;
                }
            }
            break;
        }
        default:
            main = false;
            break;
        }
    }
}
