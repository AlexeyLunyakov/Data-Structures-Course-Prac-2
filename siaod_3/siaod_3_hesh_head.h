#ifndef SIAOD_HASH_HEAD_3_H
#define SIAOD_HASH_HEAD_3_H

#include <string>
#include <iostream>
using namespace std;

struct Node {
    int key, position;
    Node* next;
    Node(int new_val, int new_pos) : key(new_val), position(new_pos), next(nullptr) {}
    int get_position();
};

struct list {
    Node* first;
    Node* last;
    int size;
    list() : first(nullptr), last(nullptr) {}
    bool is_empty();
    void deleteList();
    void push_back(int new_val, int new_pos);
    void printList();
    Node* find(int find_key);
    int remove_first();
    int remove_last();
    int remove(int find_key);
};

class HashTable {
private:
    int size, cur_elem_num;
    list* hash_t_arr;
    int hash_func(int key);
public:
    
    void rehashing();
    HashTable(int);
    int deleteItem(int);
    Node* searchItem(int);
    void insertItem(int, int);
    void displayHash();
};

void testHeshT(bool flag);



#endif //SIAOD_HASH_HEAD_3_H