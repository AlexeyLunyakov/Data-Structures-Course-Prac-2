#include "siaod_3_hesh_head.h"

void hash_menu() {
    setlocale(LC_ALL, "Russian");
    cout << "\nРаздел управления хеш-таблицей. \nСписок команд для выполнения: \n"
        "1. Вставить ключ и элемент в таблицу. \n"
        "2. Удалить ключ из таблицы. \n"
        "3. Найти ключ в таблице. \n"
        "4. Рехешировать таблицу. \n"
		"5. Показать таблицу. \n"
        "Любой другой номер приводит к выходу к главному меню.\n";
}

void testHeshT(bool flag) {
	cout << "\nТестирование таблицы. \nВведите размер таблицы: ";
	int sizee;
	cin >> sizee;
	HashTable Table(sizee);
	int num;
	hash_menu();
	while (flag) {
		cout << "\nВведите новую команду:\n";
		cin >> num;
		switch (num) {
		case 1: {
			string answ = "y";
			int pos_key = 0;
			while (answ == "y" || answ == "Y") {
				cout << "Введите структуру (ключевое значение): \n";
				int key;
				pos_key++;
				cin >> key;
				/*cout << "Введите код позиции элемента в файле:  \n";
				cin >> pos_key;*/
				Table.insertItem(key, pos_key);
				cout << "Продолжить ввод? (y/n): ";
				cin >> answ;
			}
			
			break;
		}
		case 2: {
			cout << "Введите ключевое значение (удаление): \n";
			int key;
			cin >> key;
			int value = Table.deleteItem(key);
			if (value != -1)
				cout << "Позиция в файле удаленного элемента: " << value;
			else cout << "Этого значения нет в таблице. \n";
			break;
		}
		case 3: {
			cout << "Введите ключевое значение (поиск): \n";
			int key;
			cin >> key;
			Node* ans = Table.searchItem(key);
			cout << "Ключевое значение структуры: " << key << "\nПозиция в файле: " << ans->position << "\n";
			break;
		}
		case 4: {
			cout << "Рехеширование таблицы..\nТаблица рехеширована. \n";
			Table.rehashing();
			break;
		}
		case 5: {
			cout << "Вывод содержания таблицы: \n";
			Table.displayHash();
			break;
		}
		default:
			flag = false;
			break;
		}
	}
}


bool list::is_empty() {
	return first == nullptr;
}

void list::deleteList() {
	if (!is_empty()) {
		Node* current = first;
		while (current != nullptr) {
			Node* tmp = current->next;
			delete current;
			current = tmp;
		}
	}
	first = nullptr;
}

int list::remove_first() {
	int value = first->position;
	Node* ans = first->next;
	delete[] first;
	first = ans;
	return value;
}

int list::remove_last() {
	int value = last->position;
	Node* tmp_next = first->next;
	Node* tmp = first;
	while (tmp_next != last) {
		tmp = tmp->next;
		tmp_next = tmp_next->next;
	}
	tmp->next = nullptr;
	delete[]last;
	last = tmp;
	return value;
}

int list::remove(int find_key) {
	if (is_empty())
		return -1;
	if (first->key == find_key)
		return remove_first();
	else if (last->key == find_key)
		return remove_last();
	Node* slow = first;
	Node* fast = first->next;
	while (fast && fast->key != find_key) {
		fast = fast->next;
		slow = slow->next;
	}
	if (!fast)
		return -1;
	int value = fast->position;
	slow->next = fast->next;
	delete[] fast;
	return value;
}

void list::push_back(int new_key, int new_pos) {
	Node* p = new Node(new_key, new_pos);
	if (is_empty()) {
		first = p;
		last = p;
		return;
	}
	last->next = p;
	last = p;
	size++;
}

Node* list::find(int find_key) {
	Node* tmp = first;
	while (tmp && tmp->key != find_key)
		tmp = tmp->next;
	return (tmp && tmp->key == find_key) ? tmp : nullptr;
}

void list::printList() {
	if (is_empty())
		return;
	Node* p = first;
	while (p) {
		cout << p->key << " ";
		p = p->next;
	}
	cout << "\n";
}

int Node::get_position() {
	return position;
}

int HashTable::hash_func(int key) { // !!
	double k_num = 0.0566318;
	int hash_num = this->size * fmod(key * k_num, 1);
	return hash_num;
}

HashTable::HashTable(int size) {
	this->size = size;
	this->hash_t_arr = new list[size];
	this->cur_elem_num = 0;
}

void HashTable::rehashing() {

	int prev_size = this->size;
	this->size = size * 2;
	list* rehash_list = new list[size];

	for (int i = 0; i < prev_size; ++i) {
		if (hash_t_arr[i].is_empty() == 0) {
			Node* tmp = hash_t_arr[i].first;
			do {
				int index = hash_func(tmp->key);
				rehash_list[index].push_back(tmp->key, tmp->position);
				tmp = tmp->next;

			} while (tmp != nullptr);
		}
	}
	for (int i = 0; i < prev_size; ++i)	{
		hash_t_arr[i].deleteList();
	}
	delete[] hash_t_arr;
	hash_t_arr = rehash_list;
	cout << "Новый размер рехэшированной таблицы: " << size;
}

void HashTable::insertItem(int key, int position) {

	if (cur_elem_num > 4 / 3 * this->size) {
		cout << "Рехеширование таблицы\n";
		rehashing();
	}

	hash_t_arr[hash_func(key)].push_back(key, position);
	cur_elem_num++;
}

int HashTable::deleteItem(int key) {
	return hash_t_arr[hash_func(key)].remove(key);
}

Node* HashTable::searchItem(int key) {

	Node* found = hash_t_arr[hash_func(key)].find(key);
	return found;
}

void HashTable::displayHash() {
	cout << "\n-------------------------------\n";
	for (unsigned long long index = 0; index < size; index++) {
		cout << "    " << index << " | ";
		if (!hash_t_arr[index].is_empty()) {
			hash_t_arr[index].printList();
		}
		else cout << "Нет элементов\n";
	}
	cout << "\n-------------------------------\n";
}