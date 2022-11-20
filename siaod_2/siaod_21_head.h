#ifndef SIAOD_HEAD_2_1_H
#define SIAOD_HEAD_2_1_H

#include <iostream>
#include <random>
#include <sstream>
#include <fstream>
using namespace std;

void file_cr(string name);
void new_str(ofstream& file, string str);
void auto_file_fill(ofstream& file);
void print_file(ifstream& file);
int num_counter(ifstream& file);
string file_num_find(ifstream& file, int num);
void send_to_new(ifstream& file0, ofstream& file1);


#endif //SIAOD_HEAD_2_1_H
