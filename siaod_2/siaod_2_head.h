#ifndef SIAOD_HEAD_2_2_H
#define SIAOD_HEAD_2_2_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Schedule{
    int gr_num; //example: 1234 or etc
    char sub_name[10]; //example: math or phys or armv or tfya or ciod
    int les_num;    //example: 1 or 2 ... or 6
    int week_num;   //example: 1 or 2 .. or 17
    int day_num;    //example: 1 or 2 .. or 7
    char sub_type[10]; //example: lec or prc or lab
    int class_num; //example: 123 or 2953 or etc
};

void txt_to_bin(ifstream& txt_file, ofstream& bin_file);
void bin_to_txt(ifstream& bin_file, ofstream& txt_file);
void print_bin(ifstream& bin_file);
int line_counter(ifstream& file);
Schedule get_struct(string filename, int position);
void remove_struct(string bin_name, int key);
void add_to_bin(ifstream& old_file, ofstream& new_file, int key_gr, int key_day);
void new_cab(string name_file);

#endif //SIAOD_HEAD_2_2_H
