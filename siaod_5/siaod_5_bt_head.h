#ifndef SIAOD_5_BTS_HEAD_H
#define SIAOD_5_BTS_HEAD_H

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <cmath>
using namespace std;

// БДП
struct BinTreeS {
    //Информационная часть по варианту:
    int value;
    int file_pos;
    //Адреса левой и правой веток
    BinTreeS* left;
    BinTreeS* right;
};

// КЧД
struct Node {
    int data;
    int fpos;
    Node* parent;
    Node* left;
    Node* right;
    int color;
};

typedef Node* Node_ptr;

class RedBlackTree {
private:
    Node_ptr root;
    Node_ptr TNULL;

    void initializeNULLNode(Node_ptr node, Node_ptr parent) {
        node->data = 0;
        node->fpos = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = 0;
    }

    // Прямой обход
    void pre_ord_func(Node_ptr node) {
        if (node != TNULL) {
            cout << node->data << " ";
            pre_ord_func(node->left);
            pre_ord_func(node->right);
        }
    }

    // Центрированный обход
    void in_ord_func(Node_ptr node) {
        if (node != TNULL) {
            in_ord_func(node->left);
            cout << node->data << " ";
            in_ord_func(node->right);
        }
    }

    // Обратный обход
    void post_ord_func(Node_ptr node) {
        if (node != TNULL) {
            post_ord_func(node->left);
            post_ord_func(node->right);
            cout << node->data << " ";
        }
    }

    Node_ptr search_func(Node_ptr node, int key) {
        if (node == TNULL || key == node->data) {
            return node;
        }

        if (key < node->data) {
            return search_func(node->left, key);
        }
        return search_func(node->right, key);
    }

    // Для балансировки дерева после удаления
    void del_fix_func(Node_ptr cur_node) {
        Node_ptr s;
        while (cur_node != root && cur_node->color == 0) {
            if (cur_node == cur_node->parent->left) {
                s = cur_node->parent->right;
                if (s->color == 1) {
                    s->color = 0;
                    cur_node->parent->color = 1;
                    leftRotate(cur_node->parent);
                    s = cur_node->parent->right;
                }

                if (s->left->color == 0 && s->right->color == 0) {
                    s->color = 1;
                    cur_node = cur_node->parent;
                }
                else {
                    if (s->right->color == 0) {
                        s->left->color = 0;
                        s->color = 1;
                        rightRotate(s);
                        s = cur_node->parent->right;
                    }

                    s->color = cur_node->parent->color;
                    cur_node->parent->color = 0;
                    s->right->color = 0;
                    leftRotate(cur_node->parent);
                    cur_node = root;
                }
            }
            else {
                s = cur_node->parent->left;
                if (s->color == 1) {
                    s->color = 0;
                    cur_node->parent->color = 1;
                    rightRotate(cur_node->parent);
                    s = cur_node->parent->left;
                }

                if (s->right->color == 0) {
                    s->color = 1;
                    cur_node = cur_node->parent;
                }
                else {
                    if (s->left->color == 0) {
                        s->right->color = 0;
                        s->color = 1;
                        leftRotate(s);
                        s = cur_node->parent->left;
                    }

                    s->color = cur_node->parent->color;
                    cur_node->parent->color = 0;
                    s->left->color = 0;
                    rightRotate(cur_node->parent);
                    cur_node = root;
                }
            }
        }
        cur_node->color = 0;
    }

    void rbTransplant(Node_ptr u, Node_ptr v) {
        if (u->parent == nullptr) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void del_Node_func(Node_ptr node, int key) {
        Node_ptr z = TNULL;
        Node_ptr x, y;
        while (node != TNULL) {
            if (node->data == key) {
                z = node;
            }

            if (node->data <= key) {
                node = node->right;
            }
            else {
                node = node->left;
            }
        }

        if (z == TNULL) {
            cout << "Ключ не найден в дереве" << endl;
            return;
        }

        y = z;
        int y_original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == TNULL) {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else {
            y = min_brt(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            }
            else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0) {
            del_fix_func(x);
        }
    }

    // Для балансировки дерева после вставки
    void insert_fix_func(Node_ptr k) {
        Node_ptr u;
        while (k->parent->color == 1) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            }
            else {
                u = k->parent->parent->right;

                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = 0;
    }

    void print_func(Node_ptr root, string inf_field, bool last) {
        if (root != TNULL) {
            cout << inf_field;
            if (last) {
                cout << "R ----";
                inf_field += "   ";
            }
            else {
                cout << "L ----";
                inf_field += "|  ";
            }

            string cur_colour = root->color ? "Red" : "Black";
            cout << root->data << " " << root->fpos << " (" << cur_colour << ")" << endl;
            print_func(root->left, inf_field, false);
            print_func(root->right, inf_field, true);
        }
    }

public:
    RedBlackTree() {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    void pre_ord() {
        pre_ord_func(this->root);
    }

    void in_ord() {
        in_ord_func(this->root);
    }

    void post_ord() {
        post_ord_func(this->root);
    }

    Node_ptr search_brt(int k) {
        return search_func(this->root, k);
    } 

    Node_ptr min_brt(Node_ptr node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    Node_ptr max_brt(Node_ptr node) {
        while (node->right != TNULL) {
            node = node->right;
        }
        return node;
    }

    Node_ptr successor(Node_ptr x) {
        if (x->right != TNULL) {
            return min_brt(x->right);
        }

        Node_ptr y = x->parent;
        while (y != TNULL && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    Node_ptr predecessor(Node_ptr x) {
        if (x->left != TNULL) {
            return max_brt(x->left);
        }

        Node_ptr y = x->parent;
        while (y != TNULL && x == y->left) {
            x = y;
            y = y->parent;
        }

        return y;
    }

    void leftRotate(Node_ptr x) {
        Node_ptr y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node_ptr x) {
        Node_ptr y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // Ввод узла
    void insert(int key, int val) {
        Node_ptr node = new Node;
        node->parent = nullptr;
        node->data = key;
        node->fpos = val;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1;

        Node_ptr y = nullptr;
        Node_ptr x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        }
        else if (node->data < y->data) {
            y->left = node;
        }
        else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = 0;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        insert_fix_func(node);
    }

    /*Node_ptr getRoot() {
        return this->root;
    }*/

    void deleteNode(int data) {
        del_Node_func(this->root, data);
    }

    void printTree() {
        if (root) {
            print_func(this->root, "\t", true);
        }
    }
};

#endif //SIAOD_5_BTS_HEAD_H
