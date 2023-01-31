#include "siaod_5_head.h"
#include "siaod_5_bt_head.h"

// binary

void bin_menu() {
    setlocale(LC_ALL, "Russian");
    cout << "������ ���������� �������� ������. \n������ ������ ��� ����������: \n"
        "1. �������������� �������� ������ �� ���������� ����� � �������� ����. \n"
        "2. ��������� ������ � �������� ����. \n"
        "3. ����� ���� ������� ��������� �����. \n"
        "4. ������ � ������ �� �� ����������� ������ � �����, ��������� �������� ������� ������� � ������ � �������� �����. \n"
        "5. �������� ������ � �������� ��������� �����, ��������� ����� ������ �� ��������� ������ \n"
        "����� ������ ����� �������� � ������ � �������� ����.\n";
}

void testBinF(bool flag) {
    string inp_file, outp_file;
    ifstream inp;
    ofstream outp;
    int num;
    bin_menu();
    while (flag) {
        cout << "\n������� ����� �������:\n";
        cin >> num;
        switch (num) {
        case 1: {
            inp_file = "";
            outp_file = "";
            cout << "������� ��� ���������� �����: \n";
            cin >> inp_file;
            inp.open(inp_file, ios::in);
            if (inp.good()) {
                cout << "������� ��� ��������� �����: \n";
                cin >> outp_file;
                outp.open(outp_file, ios::binary);
                if (outp.good()) {
                    txt_to_bin(inp, outp);
                }
                else cout << "���� �� ������ ��� �� ������.";
                outp.close();
                inp.close();
            }
            else {
                cout << "����� � ����� ������ �� ����������.";
            }
            break;
        }
        case 2: {
            inp_file = "";
            outp_file = "";
            cout << "������� ��� ��������� �����:\n";
            cin >> outp_file;
            fstream file;
            add_binary(outp_file);
            cout << "������ ���������. ��� ��������� ����������� ������� 3\n";
            break;
        }
        case 3: {
            inp_file = "";
            cout << "������� ��� ��������� �����:\n";
            cin >> inp_file;
            inp.open(inp_file, ios::in | ios::binary);
            if (inp.good()) {
                cout << "\n����� ����������� ��������� �����:\n";
                print_bin(inp);
                inp.close();
            }
            else {
                cout << "����� � ����� ������ �� ����������.";
            }
            break;
        }
        case 4: {
            inp_file = "";
            int pos_num;
            cout << "������� ��� ��������� �����: \n";
            cin >> inp_file;
            ifstream check(inp_file);
            if (check.is_open()) {
                cout << "������� ����� ������ ������: \n";
                cin >> pos_num;
                ifstream tmp(inp_file, ios::binary | ios::in);
                int c = line_counter(tmp);
                //cout << c << endl;
                tmp.close();
                if (pos_num < c) {
                    Schedule tt = get_struct(inp_file, pos_num);
                    cout << "���� ������: \n";
                    cout << tt.gr_num << ' ' << tt.sub_name << ' ' << tt.les_num << ' '
                        << tt.week_num << ' ' << tt.day_num << ' ' << tt.sub_type << ' ' << tt.class_num << '\n';
                }
                else {
                    cout << "������� ������� ������� �����.\n";
                }
            }
            else {
                cout << "����� � ����� ������ �� ����������. ";
            }
            break;
        }
        case 5: {
            inp_file = "";
            int key_val;
            cout << "������� ��� ��������� �����: \n";
            cin >> inp_file;

            ifstream check(inp_file);
            if (check.is_open()) {
                cout << "������� �������� ��������:\n";
                cin >> key_val;

                remove_struct(inp_file, key_val);
                cout << "������ �������.";
            }
            else {
                cout << "����� � ����� ������ �� ����������. ";
            }
            break;
        }
        default:
            flag = false;
            break;
        }
    }
}

void txt_to_bin(ifstream& txt_file, ofstream& bin_file) { // 1 �������
    Schedule tt;
    while (true) {
        txt_file >> tt.gr_num;
        if (!txt_file.eof()) {
            txt_file >> tt.sub_name >> tt.les_num >> tt.week_num >>
                tt.day_num >> tt.sub_type >> tt.class_num;
            bin_file.write((char*)&tt, sizeof(Schedule));
        }
        else break;
    }
}

void bin_to_txt(ifstream& bin_file, ofstream& txt_file) {
    //�������� �� �������������;
    Schedule tt;
    while (true) {
        bin_file.read((char*)&tt, sizeof(tt));
        if (!bin_file.eof())
            txt_file << tt.gr_num << " " << tt.sub_name << " " << tt.les_num << " " << tt.week_num
            << " " << tt.day_num << " " << tt.sub_type << " " << tt.class_num << " ";
        else break;
    }
}

void new_str(ofstream& file, string str) {
    file << str;
}

void add_binary(string bin_name) {    // 2 �������
    //Schedule tt;
    string str;
    ifstream bin_file(bin_name, ios::binary | ios::in);
    ofstream tmp("tmp_bin.txt");

    bin_to_txt(bin_file, tmp);
    cout << "������� ����� ������ (����������� �������):\n";
    cin.get();
    getline(cin, str);
    new_str(tmp, str);
    tmp.close();
    bin_file.close();

    ifstream txt("tmp_bin.txt", ios::in);
    ofstream bin(bin_name, ios::binary);
    txt_to_bin(txt, bin);
    txt.close();
    bin.close();
}


void print_bin(ifstream& bin_file) {  // 3 �������
    Schedule tt;
    while (true) {
        bin_file.read((char*)&tt, sizeof(tt));
        if (!bin_file.eof()) {
            cout << tt.gr_num << ' ' << tt.sub_name << ' ' << tt.les_num << ' ' << tt.week_num
                << ' ' << tt.day_num << ' ' << tt.sub_type << ' ' << tt.class_num << '\n';
        }
        else break;
    }
}

int line_counter(ifstream& file) {
    string num_string = "";
    int counter = 1;
    Schedule tt;
    while (true) {
        file.read((char*)&tt, sizeof(tt));
        if (!file.eof())
            counter++;
        else break;
    }
    return counter;
}

Schedule get_struct(string filename, int position) { // 4 �������
    ifstream bin_file(filename, ios::binary | ios::in);
    Schedule tt;
    if (position == -1) {
        bin_file.seekg(-1 * sizeof(tt), ios::end);
    }
    else {
        bin_file.seekg((position) * sizeof(tt));
    }
    bin_file.read((char*)&tt, sizeof(Schedule));
    bin_file.close();
    return tt;
}

void remove_struct(string bin_name, int key) { // 5 �������

    Schedule tt, replace{};
    replace = get_struct(bin_name, -1);
    ifstream bin_file(bin_name, ios::binary | ios::in);
    ofstream tmp("tmp_rem.txt");
    while (true) {
        bin_file.read((char*)&tt, sizeof(tt));

        if (!bin_file.eof()) {
            if (tt.gr_num != key) {
                tmp << tt.gr_num << " " << tt.sub_name << " " << tt.les_num << " " << tt.week_num
                    << " " << tt.day_num << " " << tt.sub_type << " " << tt.class_num << "\n";
            }
            else {
                tmp << replace.gr_num << " " << replace.sub_name << " " << replace.les_num << " " << replace.week_num
                    << " " << replace.day_num << " " << replace.sub_type << " " << replace.class_num << "\n";
            }
        }
        else {
            break;
        }
    }
    tmp.close();
    bin_file.close();
    ifstream txt("tmp_rem.txt", ios::in);
    ofstream bin(bin_name, ios::binary);
    txt_to_bin(txt, bin);
    txt.close();
    bin.close();
}
