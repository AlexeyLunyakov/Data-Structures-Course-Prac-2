#include "siaod_21_head.h"

void menu() {
    setlocale(LC_ALL, "Russian");
    cout << "Практическая работа №2 'Внешние структуры данных: текстовый и двоичный файлы'. Луняков Алексей\nУпражнение 1";
    cout << "Список команд для выполнения: \n"
            "1. Создание текстового файла (с авто-генерацией содержимого). \n"
            "2. Вывод содержимого текстового файла. \n"
            "3. Добавление новой строки в конец файла. \n"
            "4. Нахождение числа по его порядковому номеру. \n"
            "5. Определение количества чисел в файле. \n"
            "6. (Личный вариант) Создать новый файл из значений исходного, \n"
            "размещая в одной строке исходное число и через пробел количество цифр в числе.\n"
            "Любой другой номер приводит к завершению программы.\n";
}
int main(){
    string file_name;
    ifstream inp;
    ofstream outp;
    menu();
    int num;
    bool flag = true;
    while (flag) {
        cout << "\nEnter new command: \n";
        cin >> num;
        switch (num) {
            case 1:{
                file_name = "";
                cout << "Enter a name for the new file: \n"; //Введите имя нового файла:
                cin >> file_name;
                file_cr(file_name);
                outp.open(file_name, ios::out);
                auto_file_fill(outp);
                bool isGood = outp.good();
                if (isGood) outp.close();
                else cout << "\nОшибка вывода \n";
                break;
            }
            case 2:{
                file_name = "";
                cout << "Enter a name of the file: \n"; //Введите имя файла:
                cin >> file_name;
                inp.open(file_name, ios::in);
                if (inp) {
                    cout << "\nFile content output: \n"; //Вывод содержимого файла:
                    print_file(inp);
                }
                else {
                    cout << "File with this name does not exist. "; // Файла с таким именем не существует
                }
                bool isGood = inp.good();
                if (isGood) inp.close();
                else cout << "\nОшибка ввода \n";
                break;
            }
            case 3:{
                file_name = "";
                cout << "Enter a name of the file: \n"; //Введите имя файла:
                cin >> file_name;
                outp.open(file_name, ios::app);
                if (outp) {
                    string new_line;
                    cout << "\nEnter your new line: \n"; //Введите новую строку:
                    cin >> new_line;
                    new_str(outp, new_line);
                }
                else {
                    cout << "File with this name does not exist. "; // Файла с таким именем не существует
                }
                bool isGood = outp.good();
                if (isGood) outp.close();
                else cout << "\nОшибка вывода \n";
                break;
            }
            case 4:{
                int ordi_num;
                file_name = "";
                cout << "Enter a name of the file: \n"; //Введите имя файла:
                cin >> file_name;
                inp.open(file_name, ios::in);
                if (inp) {
                    cout << "Enter a ordinal number: \n"; //Введите номер нужного числа:
                    cin >> ordi_num;
                    // Числом под номером .. является:
                    cout << "The number under the number '" << ordi_num << "' in the file is: \n";
                    cout << file_num_find(inp, ordi_num) << endl;
                }
                else {
                    cout << "File with this name does not exist. "; // Файла с таким именем не существует
                }
                bool isGood = inp.good();
                if (isGood) inp.close();
                else cout << "\nОшибка ввода \n";
                break;
            }
            case 5:{
                file_name = "";
                cout << "Enter a name of the file: \n"; //Введите имя файла:
                cin >> file_name;
                inp.open(file_name, ios::in);
                if (inp) {
                    int count_of_numbers = num_counter(inp);
                    cout << "Characters: " << count_of_numbers << endl; //Количество символов:
                }
                else {
                    cout << "File with this name does not exist. "; // Файла с таким именем не существует
                }
                bool isGood = inp.good();
                if (isGood) inp.close();
                else cout << "\nОшибка ввода \n";
                break;
            }
            case 6: {
                file_name = "";
                cout << "Enter a name of the file: \n"; //Введите имя файла:
                cin >> file_name;
                inp.open(file_name, ios::in);
                if (inp) {
                    //cout << "Enter a name of the new file: \n"; //Введите имя файла:
                    string new_file = "new_" + file_name;
                    //cin >> new_file;
                    ofstream new_outp;
                    file_cr(new_file);
                    new_outp.open(new_file, ios::out);
                    send_to_new(inp, new_outp);
                    bool isGood = new_outp.good();
                    if (isGood) new_outp.close();
                    else cout << "\nОшибка вывода \n";
                }
                else {
                    cout << "File with this name does not exist. "; // Файла с таким именем не существует
                }
                bool isGood = inp.good();
                if (isGood) inp.close();
                else cout << "\nОшибка ввода \n";
                break;
            }
            default:
                flag = false;
                break;
        }
    }

    return 0;
}