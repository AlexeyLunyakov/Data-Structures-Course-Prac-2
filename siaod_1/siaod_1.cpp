#include <iostream>
using namespace std;

void coutp(unsigned int x)
{
    int n = sizeof(int) * 8;
    unsigned  maska = (1 << (n - 1));
    for(int i = 1; i <= n; i++)  {
        cout << ((x & maska) >> (n - i));
        maska = maska >> 1;
    }
    cout << endl;
}

int com1(int x, int m){
    x =  x | m;
    return x;
}

int com2(int x, int m){
    x =  x & m;
    return x;
}
int com3(int x){
    x = x << 3;
    return x;
}
int com4(int x){
    x = x >> 3;
    return x;
}
int com5(int x, int maska1, int n){
    maska1 = maska1 << n;
    maska1 = ~ maska1;
    x = x & maska1;
    return x;
}

int main(int argc, const char * argv[]) {
    unsigned int value;
    int num;
    setlocale(LC_ALL, "Russian");
    cout << "Практическая работа №1 'Поразрядные операции и их применение'. Луняков Алексей";
    cout << "Списко команд для выполнения: \n"
            "1.Установка 1, 2 и 7 битам значения равного 1. \n"
            "2.Обнуление битов с 7го три слева. \n"
            "3.Умножение введенного числа на 8. \n"
            "4.Деление введенного числа на 8. \n"
            "5.Обнуление n-ого бита, используя маску 1. \n"
            "\n\nВведите номер команды: \n";
    cin >> num;
    switch (num) {
        case 1:{
            int m = 0x86;
            cout << "Введите ваше число:";
            cin >> value;
            cout << "x = " << value << "\nm = " << m << endl;
            cout << "x (bin) = ";
            coutp(value);
            cout << "m (bin) = ";
            coutp(m);
            value = com1(value, m);
            cout << "Результат x | m = " << value;
            break;
        }
        case 2:{
            int m = 0xFFFFFF8F;
            cout << "Введите ваше число: \n";
            cin >> value;
            cout << "x = " << value << "\nm = " << m << endl;
            cout << "x (bin) = ";
            coutp(value);
            cout << "m (bin) = ";
            coutp(m);
            value = com2(value, m);
            cout << "Результат x & m = " << value;
            break;
        }
        case 3:{
            cout << "Введите ваше число: \n";
            cin >> value;
            cout << "x = " << value << endl;
            cout << "x (bin) = ";
            coutp(value);
            value = com3(value);
            cout << "Результат x << 3 = ";
            coutp(value);

            break;
        }
        case 4:{
            cout << "Введите ваше число: \n";
            cin >> value;
            cout << "x = " << value << endl;
            cout << "x (bin) = ";
            coutp(value);
            value = com4(value);
            cout << "Результат x >> 3 = ";
            coutp(value);
            break;
        }
        case 5:{
            int m1 = 0x1;
            int n;
            cout << "Введите ваше число: \n";
            cin >> value;
            cin >> n;
            cout << "x = " << value << "\nn =" << n;
            cout << "\nx (bin) = ";
            coutp(value);
            value = com5(value, m1, n);
            cout << "Res ";
            coutp(value);
            break;
        }
        default:
            break;
    }
}

//cout << "x (bin) = " << bitset<16> (x) << endl;
/*cout << "List of commands: \n"
            "1.Set bits 1, 2 and 7 to 1. \n"
            "2.Zero bits from the 7th three from the left.\n"
            "3.Multiply the entered number by 8.\n"
            "4.Divide the entered number by 8. \n"
            "5.Set bit n to zero using mask 1.\n";*/