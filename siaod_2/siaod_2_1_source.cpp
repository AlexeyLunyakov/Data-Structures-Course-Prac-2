#include "siaod_21_head.h"

// создание текстового файла
void file_cr(string name) {
    ofstream file(name);
    file.close();
}

// добавление новой строки
void new_str(ofstream& file, string str) {
    file << str;
}

// автоматическое заполнение
void auto_file_fill(ofstream &file) {
    int row = rand() % 12 + 1;
    file << to_string(rand() % 10000) << " ";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < rand()%10; j++) { //int j = 0; j < 2 * (rand() % 3); j++
            file << to_string(rand() % 10000) << " ";
        }
        file << '\n';
    }
}

// вывод содержимого файла
void print_file(ifstream& file) {
    string line;
    if (!file.eof()){
        while (getline(file, line)){
            cout << line << endl;
        }
    }
}

// подсчёт символов в файле
int num_counter(ifstream& file){
    string num_string = "";
    int counter = 0;
    while (!file.eof()) {
        // проходим по файлу считывая строки
        getline(file, num_string);
        // проходим итератором по строке
        for (string::iterator it = num_string.begin(); it != num_string.end(); ++it){
            if (*it == ' ') counter++;
        }
    }
    return counter;
}

// поиск и чтение числа по номеру
string file_num_find(ifstream& file, int num) {
    int counter = 0;
    string number = "";
    string temp_str = "";
    while (!file.eof()) {
        getline(file, temp_str);
        // анализ каждого символа строки с посимвольным формированием каждого числа
        for (string::iterator it = temp_str.begin(); it != temp_str.end(); ++it) {
            if (*it != ' ') number += *it;
            if (*it == ' ') {
                counter++;
                if (counter == num) return number;
                // не совпало с введенным номером - обнуление строки
                number = "";
            }
        }
    }
    if (number == "")
        number = "Invalid number entered"; //Введено некорректное число
    return number;
}

//Создать новый файл из значений исходного,
// размещая в одной строке исходное число
// и через пробел количество цифр в числе.

// запись из старого файла в новый, по заданию
void send_to_new(ifstream& file0, ofstream& file1) {
    string temp_str = "";
    while (!file0.eof()) {
        getline(file0, temp_str);
        istringstream ss(temp_str.substr(0, temp_str.size() - 1));
        string num;
        while (ss >> num) {
            file1 << num << " " << num.size() << "\n";
        }
    }
}