#ifndef SIAOD_HEAD_7_H
#define SIAOD_HEAD_7_H
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

//��������� ������ ��� ��������� LZ77
struct LZ77_strct {
    int offset;	 // ��������
    int length;	//����� ���������� 
    char next; //�������� �������
};

//��������� ������ ��� ��������� LZ78
struct LZ78_strct {
    int pos;	 // ����� ����� � �������
    char next;	//�������� �������
};

vector<LZ77_strct> LZ77(string s);

vector<LZ78_strct> LZ78(string s);

string dec_LZ77(vector<LZ77_strct>);

string dec_LZ78(vector<LZ78_strct>);


//--------------------------------
//��������� ���� ��� ��������� �������-����
struct Node {
    char symbol;
    double rate;
    string arr = "";
    Node* left;
    Node* right;
    Node(char s, double f, Node* l = nullptr, Node* r = nullptr) : symbol(s), rate(f), left(l), right(r) {};
};

struct NodeQueue {
    Node* value;
    NodeQueue* next;
    NodeQueue(Node* newValue) : value(newValue), next(nullptr) {};
};

class Queue {
private:
    NodeQueue* head = nullptr;
public:
    void push(Node*);
    Node* pop();
    bool checkSize();
};

//-----------------------
void Queue::push(Node* newValue) {
	NodeQueue* top = new NodeQueue(newValue);
	if (!head) {
		head = top;
		return;
	}
	NodeQueue* current = head;
	while (current->next && current->value->rate < newValue->rate)
		current = current->next;
	if (!current->next)
		current->next = top;
	else {
		NodeQueue* tmp = current->next;
		current->next = top;
		top->next = tmp;
	}
}

Node* Queue::pop() {
	NodeQueue* tmp = head;
	head = head->next;
	return tmp->value;
}

bool Queue::checkSize() {
	if (head && head->next)
		return true;
	return false;
}

#endif //SIAOD_HEAD_7_H