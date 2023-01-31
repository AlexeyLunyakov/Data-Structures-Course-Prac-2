#include <iostream>
#include <iomanip>
#include <string>
#include "compr_head.h"
using namespace std;

// Types of compressions:

string RLE(const string& str);
vector<LZ77_strct> LZ77(string user_str); 
vector<LZ78_strct> LZ78(string user_str);
void SF_alg(int begin, int end);
Node* Huff_alg(int size);

// RLE (run length encoding/кодирование длин серий) 
string RLE(const string& user_str) {
	int i = user_str.size();
	string rle_str;		// new rle string 
	for (int x = 0; x < i; ++x) {
		int count = 1;	// char counter
		while (user_str[x] == user_str[x + 1]) {
			count++;
			x++;
		}
		rle_str += to_string(count);
		rle_str.push_back(user_str[x]);
	}
	return rle_str;
}

// Алгоритм Лемпеля-Зива LZ77
vector<LZ77_strct> LZ77(string user_str) {
	int maxWindow = 10;	// размер скользящего окна
	vector<LZ77_strct> lz77_str;
	int sizeBuffer;	// размер текущей строки
	int sizeUnchecked;	// размер непроверенной строки
	/* 
	Идея алгоритма это замена повторного вхождения 
	строки ссылкой на одну из предыдущих позиций вхождения.
	Кодируемая пара трактуется, как команда копирования 
	символов из скользящего окна с определенной позиции.
	*/
	for (int i = 0; i < user_str.length(); i++) {
		// обновление размера текущего размера строки
		if (i + 1 <= maxWindow) {
			sizeBuffer = i;	
		}
		else {
			sizeBuffer = maxWindow;
		}
		if (i + sizeBuffer < user_str.length()) {
			sizeUnchecked = sizeBuffer;
		}
		else {
			sizeUnchecked = user_str.length() - i;
		}
		//формирование буферной строки и непроверенной строки
		string buffer = user_str.substr(i - sizeBuffer, sizeBuffer);
		string unchecked = user_str.substr(i, sizeUnchecked);
		//флаг нахождения новой строки в текущей - с указанием места в подстроке
		int find_flag = -1;
		while (true) {
			if (!sizeUnchecked) break;
			//формирование символьной подстроки
			string str3 = unchecked.substr(0, sizeUnchecked);
			//проверка на наличие этой подстроки в текущей
			find_flag = buffer.find(str3);
			//если нашли
			if (find_flag != -1) break;
			//если не нашли - уменьшаем подстроку и проходим еще раз
			sizeUnchecked--;
			if (sizeUnchecked <= 0) break;
		}
		LZ77_strct value;
		//создаем следущий элемент массива размером с учетом размер найденной подстроки
		value.next = user_str[i + sizeUnchecked];
		//если нашли подстроку:
		if (find_flag != -1) {
			value.length = sizeUnchecked;
			value.offset = sizeBuffer - find_flag;
			lz77_str.push_back(value);
			i += sizeUnchecked;
		}
		else {
			//если нет, начинаем поиск заново
			value.length = 0;
			value.offset = 0;
			lz77_str.push_back(value);
		}
	}
	return lz77_str;
}

// Алгоритм Лимпеля-Зива LZ78 
vector<LZ78_strct> LZ78(string user_str) {

	string buffer = "";			
	map<string, int> dict = {}; // словарь из уже просмотренных фраз
	vector<LZ78_strct> lz78_str;
	/*
	Алгоритм считывает символы сообщения до тех пор, 
	пока накапливаемая подстрока входит целиком 
	в одну из фраз словаря. И следующая итерация начинается,
	как только эта строка перестанет соответствовать 
	хотя бы одной фразе словаря
	*/
	for (int i = 0; i < user_str.size(); ++i) {
		//поиск по словарь исследуемой подстроки
		if (dict.find(buffer + user_str[i]) != dict.end()) {
			buffer += user_str[i];
		}
		else {
			LZ78_strct value;
			value.next = user_str[i];
			if (dict[buffer] == 0) {
				value.pos = dict[buffer];
			}
			else {
				value.pos = dict[buffer] - 1;
			}
			lz78_str.push_back(value);
			dict[buffer + user_str[i]] = dict.size() + 1;
			buffer = "";
		}
	}
	//формирование подстроки
	if (buffer != "") {
		char last_ch = buffer[buffer.size() - 1];
		buffer.pop_back();
		LZ78_strct value;
		if (dict.find(buffer + user_str[user_str.size() - 1]) != dict.end()) {
			value.next = '$';
			value.pos = dict[buffer + user_str[user_str.size() - 1]] - 1;
		}
		else {
			value.next = last_ch;
			value.pos = dict[buffer];
		}
		lz78_str.push_back(value);
	}
	return lz78_str;
}

Node** node_ptr = nullptr;
string encodeText(string value, int size) {
	string ans = "";
	for (int i = 0; i < value.size(); ++i)
		for (int j = 0; j < size; ++j)
			if (value[i] == node_ptr[j]->symbol)
				ans += node_ptr[j]->arr;
	return ans;
}

// Алгоритм Шеннона-Фано
void SF_alg(int start, int end) {
	if (start == end || (start + 1) == end || start > end) {
		if (start == end || start > end) {
			return;
		}
		node_ptr[end]->arr += '0';
		node_ptr[start]->arr += '1';
		return;
	}
	else {
		int cnt;
		double part1 = 0, part2 = 0, dif1 = 0, dif2 = 0;

		for (int i = start; i <= end - 1; i++) {
			part1 = part1 + node_ptr[i]->rate;
		}

		dif1 = part1 - part2;
		part2 = part2 + node_ptr[end]->rate;
		
		if (dif1 < 0)
			dif1 = dif1 * -1;
		
		for (int i = 2; i != end - start + 1; i++) {
			cnt = end - i;
			part1 = 0;
			part2 = 0;
			for (int k = start; k <= cnt; k++) {
				part1 = part1 + node_ptr[k]->rate;
			}
			for (int j = end; j > cnt; j--) {
				part2 = part2 + node_ptr[j]->rate;
			}
			dif2 = part1 - part2;
			if (dif2 >= dif1)
				break;
			if (dif2 < 0) {
				dif2 = dif2 * -1;
			}
			dif1 = dif2;
		}
		cnt++;
		for (int i = start; i <= cnt; i++) {
			node_ptr[i]->arr += '1';
		}
		for (int i = cnt + 1; i <= end; i++) {
			node_ptr[i]->arr += '0';
		}
		SF_alg(start, cnt);
		SF_alg(cnt + 1, end);
	}
}

void SF_syb(int size) {
	cout << "\n    Символ\t Частота     Двоичный код";
	for (int i = size - 1; i >= 0; i--) {
		//if (node_ptr[i]) {
			cout << "\n    " << " <" << node_ptr[i]->symbol << ">" << "\t" << node_ptr[i]->rate << "\t";

			for (int j = 0; j <= node_ptr[i]->arr.size(); j++) {
				cout << node_ptr[i]->arr[j];
			}
		//}
	}
}


// Декодирование Фано
string SF_decode(string user_str, int size) {
	string ans = "";
	string buffer = "";
	vector<int> candidates;
	for (int i = 0; i < user_str.size(); ++i) {
		buffer += user_str[i];
		for (int j = 0; j < size; ++j) {
			if (buffer.size() != node_ptr[j]->arr.size())
				continue;
			bool isCandidate = true;
			for (int k = 0; k < buffer.size(); ++k) {
				if (buffer[k] != node_ptr[j]->arr[k])
					isCandidate = false;
			}
			if (isCandidate && find(candidates.begin(), candidates.end(), j) == candidates.end())
				candidates.push_back(j);
			else candidates.erase(remove(candidates.begin(), candidates.end(), j), candidates.end());
		}
		if (candidates.size() == 1) {
			ans += node_ptr[candidates[0]]->symbol;
			candidates.erase(candidates.begin());
			buffer = "";
		}
	}
	return ans;
}

// Алгоритм Хаффмана
Node* Huff_alg(int size) {
	Queue ans;
	int current = size;
	for (int i = 0; i <= size; ++i) {
		ans.push(node_ptr[i]);
	}
	while (ans.checkSize()) {
		Node* first = ans.pop();
		Node* second = ans.pop();
		Node* tmp = new Node('!', first->rate + second->rate, first, second);
		ans.push(tmp);
	}
	return ans.pop();
}

void printLeaves(Node* root, string path, int str_size) {
	if (!root->left && !root->right) {
		cout << " '" << root->symbol << "' \t - \t '" << path << "' \t - \t '" << root->rate  << "'\n";
		root->arr = path;
		return;
	}
	//else { cout << path << endl; }
	if (root->left != nullptr)
		printLeaves(root->left, path + "0", str_size);
	if (root->right != nullptr)
		printLeaves(root->right, path + "1", str_size);
}

//Подсчет уникальных символов строки 
int uniq_sybl_c(string user_str) {
	string tmp = "";
	tmp += user_str[0];
	for (int i = 0; i < user_str.size(); i++) {
		if (count(tmp.begin(), tmp.end(), user_str[i]) == 0) {
			tmp += user_str[i];
		}
	}
	node_ptr = new Node * [tmp.size()];
	for (int i = 0; i < tmp.size(); ++i)
		node_ptr[i] = new Node(tmp[i], double(count(user_str.begin(), user_str.end(), tmp[i])) / double(user_str.size()));
	return tmp.size();
}

//Сортировка по частоте
void rate_sort(int size) {
	for (int j = 1; j < size; j++) {
		for (int i = 0; i < size - 1; i++) {
			if (node_ptr[i]->rate > node_ptr[i + 1]->rate) {
				swap(node_ptr[i], node_ptr[i + 1]);
			}
		}
	}
}

// Декодирование Хаффмана
string Huff_dec(string user_str, Node* root_main, bool flag_ex) {
	int counter = 0;
	int k = counter;
	string ans = "";
	while (k < user_str.size()) {
		Node* temp = root_main;
		while (true) {
			if (user_str[k] == '0') {
				if (temp->left != nullptr) {
					temp = temp->left;
				}
				else {
					ans += temp->symbol;
					break;
				}
			}
			else {
				if (temp->right != nullptr)
					temp = temp->right;
				else {
					ans += temp->symbol;
					break;
				}
			}
			k++;
			counter = k;
		}
		if (flag_ex)
			k++;
		else
			k = counter;
	}
	return ans;
}
