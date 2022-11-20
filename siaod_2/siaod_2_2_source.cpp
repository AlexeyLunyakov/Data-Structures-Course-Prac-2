#include "siaod_2_head.h"

void txt_to_bin(ifstream& txt_file, ofstream& bin_file) { // 1 задание
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

void bin_to_txt(ifstream& bin_file, ofstream& txt_file) { // 2 задание
    //Проверка на существование;
    Schedule tt;
    while (true) {
        bin_file.read((char*)&tt, sizeof(tt));
        if (!bin_file.eof())
            txt_file << tt.gr_num << " " << tt.sub_name << " " << tt.les_num << " " << tt.week_num
                     << " " << tt.day_num << " " << tt.sub_type << " " << tt.class_num << "\n";
        else break;
    }
}

void print_bin(ifstream& bin_file) {            // 3 задание
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
    while (!file.eof()) {
        while (getline(file, num_string)) {
            counter++;
        }
    }

    return counter;
}

Schedule get_struct(string filename, int position) { // 4 задание
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


void remove_struct(string bin_name, int key) { // 5 задание

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

void add_to_bin(ifstream& old_file, ofstream& new_file, int key_gr, int key_day) {    // 6 задание
    Schedule tt;
    string answer;
    while (true) {
        old_file.read((char*)&tt, sizeof(tt));
        if (!old_file.eof()) {
            if (tt.gr_num == key_gr && tt.day_num == key_day) {
                new_file.write((char*)&tt, sizeof(Schedule));
            }
        }
        else break;
    }
}

void new_cab(string name_file) { // 7 задание
    fstream old_sch(name_file, ios::binary | ios::out | ios::in);
    ofstream tmp("tmp_sch.txt");
    old_sch.seekg(0, ios::end);
    int size = old_sch.tellg();
    size = size / sizeof(Schedule);
    old_sch.seekg(0, ios::beg);
    Schedule* tts = new Schedule[size];
    Schedule tt;
    int flag;
    old_sch.read((char*)tts, sizeof(Schedule) * size);
    for (int i = 0; i < size - 1; i++) {
        for (int j = i+1; j < size; ++j) {
            if ((tts[j].les_num == tts[i].les_num) && (tts[j].class_num == tts[i].class_num)) {

                tts[j].class_num = tts[j].class_num + 1;
                tmp << tts[j].gr_num << " " << tts[j].sub_name << " " << tts[j].les_num << " " << tts[j].week_num
                    << " " << tts[j].day_num << " " << tts[j].sub_type << " " << tts[j].class_num << "\n";
                continue;
            }
        }
        tmp << tts[i].gr_num << " " << tts[i].sub_name << " " << tts[i].les_num << " " << tts[i].week_num
            << " " << tts[i].day_num << " " << tts[i].sub_type << " " << tts[i].class_num << "\n";
    }
    tmp.close();
    old_sch.close();
    ifstream txt("tmp_sch.txt", ios::in);
    ofstream bin(name_file, ios::binary);
    txt_to_bin(txt, bin);
    txt.close();
    bin.close();
}
