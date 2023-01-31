#include "compr_source.hpp"
#include <fstream>
#include <sstream>
/*Вариант 16.
Сжатие данных методом RLE на разных строках

Сжатие данных по методу Лемпеля-Зива LZ77
0100101010010000101

Закодировать следующую фразу, используя код LZ78
roporopoterropoterter

Закодировать фразу методами Шеннона-Фано
Зуба зуба, зуба зуба,
Зуба дони дони мэ,
А шарли буба раз два три,
А ми раз два три замри.

Сжатие данных алгоритмоом Хаффмана
*/

void local_menu() {
    cout << "Практикум №7 'Кодирование и сжатие данных методами без потерь'. Алексей Луняков\n";
    cout << "Список команд для выполнения: \n"
        "\n"
        "1. Сжатие текста методом RLE.\n"
        "2. Сжатие текста методом Лемеля-Зива LZ77. \n"
        "3. Сжатие текста методом LZ78.\n"
        "4. Сжатие текста алгоритмом Шеннона-Фано. \n"
        "5. Сжатие текста алгоритмом Хаффмана. \n"
        "6. Сжатие большого файла Хаффман. \n"
        "7. Повторить главное меню. \n"
        "Любое другое число завершает работу программы.\n";
}

int main() {
    int mnum;
    string user_str;
    bool main = true;
    setlocale(LC_ALL, "Russian");
    local_menu();
    ifstream inp_file;
    while (main) {
        int val;
        cout << "\nВведите вашу команду меню: \n";
        cin >> mnum;
        switch (mnum) {
        case 1: {
            // RLE
            char c;
            cout << "\nВведите вашу строку из символов: \n";
            cin >> user_str; 
            // qqqqqqqqqqqqqqeeeeeeerrrrrxxxxxaaaaa
            // qwertyuioplkjhgfdsazxcvbnm
            cout << "\nКодирование: " << RLE(user_str) << "\n";
            break;
        }
        case 2: {
            // LZ77
            cout << "\nВведите вашу строку из символов: \n";
            cin >> user_str;
            // 0100101010010000101
            vector<LZ77_strct> lz77 = LZ77(user_str);
            
            cout << "Кодирование:\n";
            cout << "<смещение в окне, длина буфера, последний символ буфера>\n";
            for (auto el : lz77) {
                cout << "\t<" << el.offset << ", " << el.length << ", " << el.next << "> ";
            }
            break;
        }
        case 3: {
            // LZ78
            cout << "\nВведите вашу строку из символов: \n";
            cin >> user_str;
            // roporopoterropoterter
            vector<LZ78_strct> lz78 = LZ78(user_str);

            cout << "Кодирование:\n";
            cout << "<номер слова в словаре, следущий симовол>\n";
            for (auto el : lz78) {
                cout << "\t<" << el.pos << ", " << el.next << "> ";
            }
            break;
        }
        case 4: {
            // Шеннона-Фано
            // Зуба зуба, зуба зуба, Зуба дони дони мэ, А шарли буба раз два три, А ми раз два три замри.
            user_str = "Зуба зуба, зуба зуба, Зуба дони дони мэ, А шарли буба раз два три, А ми раз два три замри.";
            int size = uniq_sybl_c(user_str);
            rate_sort(size);

            cout << "Кодирование: ";
            SF_alg(0, size - 1);
            string Fano = encodeText(user_str, size);
            SF_syb(size);
            cout << endl;
            cout << Fano << " " << Fano.size() << "\n";
            cout << "Восстановление текста: " << SF_decode(Fano, size) << "\n";
            break;
        }
        case 5: {
            // Хаффмана
            user_str = "Луняков Алексей Александрович";
            cout << user_str << "\n";
            //подсчет числа уникальных символов для создания соотвествующего массива
            int size = uniq_sybl_c(user_str);
            rate_sort(size);
            Node* huff = Huff_alg(size - 1);
            cout << "Алфавит: \n(Символ - Код символа - Частота вхождений)\n";
            printLeaves(huff, "", user_str.size());
            cout << "\nКодирование: ";
            string text = encodeText(user_str, size);
            cout << text.size() << "\n";
            //cout << text << " " << text.size() << "\n";
            cout << "Восстановление текста: " << Huff_dec(text, huff, 0) << "\n";
            break;
        }

        case 6: {
            string file_name;
            cout << "Введите имя файла: ";
            cin >> file_name;
            ifstream ifs(file_name);
            string str((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
            cout << "Размер строки: " << str.size() << endl;
            int size = uniq_sybl_c(str);
            rate_sort(size);
            Node* huff = Huff_alg(size - 1);
            
            cout << "Алфавит: \n(Символ - Код символа - Частота вхождений)\n";
            printLeaves(huff, "", str.size());
            
            cout << "\nКодирование: ";
            string text = encodeText(str, size);
            cout << text << " " << text.size() << "\n";
            break;
        }
        case 7: {
            local_menu();
            break;
        }
        default:
            main = false;
            break;
        }
    }
    return 0;
}