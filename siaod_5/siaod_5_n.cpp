#include "siaod_5_head.h"
#include "siaod_5_bt_head.h"
#include "siaod_5_source.cpp"
#include "siaod_5_btsource.hpp"

// генератор больших файлов
string sub_name[10] = { "math", "physic", "armv", "tfya",
                    "sadpa", "java", "history", "lang", "conf", "fizra" };
string sub_type[3] = { "lec", "prac", "lab" };

void create_file(string& file_name) {
    ofstream file;
    file.open(file_name);
    srand(time(NULL));
    string str = "";
    int n;
    cout << "\nВведите количество строк в файле: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        int i1 = rand() % 10;
        int i2 = rand() % 3;
        // для 100.000
        str = to_string((rand() % 9 + 1) * 10000 + (rand() % 10000))
            + " " + sub_name[i1] + " " + to_string(rand() % 6 + 1) + " "
            + to_string(rand() % 16 + 1) + " " + to_string(rand() % 7 + 1) + " " +
            sub_type[i2] + " " + to_string((rand() % 9 + 1) * 1000 + (rand() % 1000)) + "\n";
        file << str;
        /*
        // для 10000
        str = to_string((rand() % 9 + 1) * 1000 + (rand() % 1000))
            + " " + sub_name[i1] + " " + to_string(rand() % 6 + 1) + " "
            + to_string(rand() % 16 + 1) + " " + to_string(rand() % 7 + 1) + " " +
            sub_type[i2] + " " + to_string((rand() % 9 + 1) * 1000 + (rand() % 1000)) + "\n";
        file << str;*/
    }
    file.close();
}

void main_menu() {
    setlocale(LC_ALL, "Russian");
    cout << "Практическая работа №5 'СДП и их применение для поиска данных в файле'. Луняков Алексей\n";
    cout << "Список команд для выполнения: \n"
        "1. Управление двоичным файлом. \n"
        "2. Управление двоичным файлом с помощью бинарных деревьев. \n"
        "3. Создать большой текстовый файл."
        "Любой другой номер приводит к завершению программы.\n";
}

int main() {
    string inp_file, outp_file;
    ifstream inp;
    ofstream outp;
    int mnum;
    bool main = true;
    main_menu();
    while (main) {
        cout << "\nВведите команду главного меню:\n";
        cin >> mnum;
        switch (mnum) {
        case 1: {
            // Управление двоичным файлом (2 работа)
            testBinF(true);
            break;
        }
        case 2: {
            bool flag = true;
            while (flag) {
                // Управление двоичным файлом с помошью бинарных деревьев
                int num;
                cout << "\nДерево для работы с файлом: \n"
                    "1. БДП\n2. КЧД\nНомер выбранного дерева: ";
                cin >> num;
                cout << "\n";
                switch (num) {
                case 1: {
                    testTreeBTS(true);
                    break;
                }
                case 2: {
                    testTreeBRT(true);
                    break;
                }
                default:
                    flag = false;
                    break;
                }
            }
            break;
        }
        case 3: {
            string file_name;
            cout << "\nВведите название текстового файла: ";
            cin >> file_name;
            create_file(file_name);
            break;
        }
        default:
            main = false;
            break;
        }
    }
}
