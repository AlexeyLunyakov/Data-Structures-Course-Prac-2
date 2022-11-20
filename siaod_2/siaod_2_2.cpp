#include "siaod_2_head.h"

/*struct Schedule{
    int gr_num; //example: 1234 or etc
    char sub_name[10]; //example: math or phys or armv or tfya or ciod
    int les_num;    //example: 1 or 2 ... or 6
    int week_num;   //example: 1 or 2 .. or 17
    int day_num;    //example: 1 or 2 .. or 7
    char sub_type[10]; //example: lec or prc or lab
    int class_num; //example: 123 or 2953 or etc
};*/

void menu() {
    setlocale(LC_ALL, "Russian");
    cout << "Практическая работа №2 'Внешние структуры данных: текстовый и двоичный файлы'. Луняков Алексей\nУпражнение 2\n";
    cout << "Список команд для выполнения: \n"
            "1. Преобразование тестовых данных из текстового файла в двоичный файл. \n"
            "2. Преобразование данных из двоичного файла в текстовый. \n"
            "3. Вывод всех записей двоичного файла. \n"
            "4. Доступ к записи по ее порядковому номеру в файле, используя механизм прямого доступа к записи в двоичном файле. \n"
            "5. Удаление записи с заданным значением ключа, выполнить путем замены на последнюю запись \n"
            "\n(Личный вариант)\n"
            "6. Сформировать в двоичном файле расписание заданной группы на заданный день недели \n"
            "7. Обновить расписание, найти дисциплины, которые стоят на одинаковых парах в одной аудитории, и определить для них новые аудитории..\n"
            "Любой другой номер приводит к завершению программы.\n";
}

int main() {
    string inp_file, outp_file;
    ifstream inp;
    ofstream outp;
    menu();
    int num;
    bool flag = true;
    while (flag) {
        cout << "\nВведите новую команду:\n";
        cin >> num;
        switch (num) {
            case 1: {
                inp_file = "";
                outp_file = "";
                cout << "Введите имя текстового файла: \n";
                cin >> inp_file;
                inp.open(inp_file, ios::in);
                if (inp.good()) {
                    cout << "Введите имя бинарного файла: \n";
                    cin >> outp_file;
                    outp.open(outp_file, ios::binary);
                    if (outp.good()) {
                        txt_to_bin(inp, outp);
                    }
                    else cout << "Файл не найден или не создан.";

                    outp.close();
                    inp.close();
                }
                else {
                    cout << "Файла с таким именем не существует.";
                }
                break;
            }
            case 2: {
                inp_file = "";
                outp_file = "";
                cout << "Введите имя бинарного файла:\n";
                cin >> inp_file;
                inp.open(inp_file, ios::binary | ios::in);
                if (inp.good()) {
                    cout << "Введите имя текстового файла:\n";
                    cin >> outp_file;
                    outp.open(outp_file, ios::out);
                    if (outp.good()) {
                        bin_to_txt(inp, outp);
                    }
                    else cout << "Файл не найден или не создан.";

                    outp.close();
                    inp.close();
                }
                else {
                    cout << " Файла с таким именем не существует.";
                }
                break;
            }
            case 3: {
                inp_file = "";
                cout << "Введите имя бинарного файла:\n";
                cin >> inp_file;
                inp.open(inp_file, ios::in | ios::binary);
                if (inp.good()) {
                    cout << "\nВывод содержимого бинарного файла:\n";
                    print_bin(inp);
                    inp.close();
                }
                else {
                    cout << "Файла с таким именем не существует.";
                }
                break;
            }
            case 4: {
                inp_file = "";
                int pos_num;
                cout << "Введите имя бинарного файла: \n";
                cin >> inp_file;
                //inp.open(inp_file);
                ifstream check(inp_file);
                if (check.is_open()) {
                    cout << "Введите номер нужной строки: \n";
                    cin >> pos_num;
                    ifstream tmp(inp_file, ios::binary | ios::in);
                    int c = line_counter(tmp);
                    if (pos_num < c) {
                        Schedule tt = get_struct(inp_file, pos_num);
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
                inp_file = "";
                int key_val;
                cout << "Введите имя бинарного файла: \n";
                cin >> inp_file;

                ifstream check(inp_file);
                if (check.is_open()) {
                    cout << "Введите ключевой параметр:\n";
                    cin >> key_val;

                    remove_struct(inp_file, key_val);
                }
                else {
                    cout << "Файла с таким именем не существует. ";
                }
                break;
            }
            case 6: {
                outp_file = "";
                inp_file = "";
                int key_gr, key_day;
                cout << "Введите имя файла старого расписания: \n";
                cin >> inp_file;
                inp.open(inp_file, ios::binary | ios::in);
                if (inp.good()) {
                    cout << "Введите имя файла нового расписания: \n";
                    cin >> outp_file;
                    outp.open(outp_file, ios::binary | ios::out);
                    if (outp.good()) {
                        cout << "Введите номер группы и дня: \n";
                        cin >> key_gr >> key_day;
                        add_to_bin(inp, outp, key_gr, key_day);
                    }
                    else cout << "Файл не найден или не создан.";
                    outp.close();
                    inp.close();
                }
                else {
                    cout << "Файла с таким именем не существует. ";
                }
                break;
            }
            case 7: {
                string name_file;
                cout << "Введите имя файла старого расписания: \n";
                cin >> name_file;
                ifstream check(inp_file);
                if (check.is_open()) {
                    new_cab(name_file);
                }
                else {
                    cout << "Файла с таким именем не существует. ";
                }
                break;
            }
            default:
                flag = false;
                break;
        }
    }

    return 0;
}