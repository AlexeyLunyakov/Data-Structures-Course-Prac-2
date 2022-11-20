/*!
\file
\brief The source file with the main function.
*/
#include "bts_sourse.hpp"

/*!
\brief Visual program control menu
*/
/*!
\code
    Used in the main function:
    ...
        bts_menu();
    ...
\endcode
*/

void bts_menu() {
    setlocale(LC_ALL, "Russian");
    cout << "Practical work №4 'Nonlinear data structures. Binary tree'. Alexey Lunyakov\n";
    cout << "List of commands to execute: \n"
        "1. Create a binary tree. \n"
        "2. Sum of values in leaves (reverse bypass).\n"
        "3. Removing the maximum element. \n"
        "4. Inserting a new element. \n"
        "5. Determining the number of nodes in each subtree. \n"
        "Any other number terminates the program.\n";
}



/// \brief Main function

int main() {
    string inp_file, outp_file;
    int mnum;
    BinTree* Tree = nullptr;
    bool main = true;
    bool flag = true;
    bts_menu();
    while (main) {
        /// ­­
        /// Части работы с бинарным деревом:
        /// ­­
        int val;
        cout << "\nEnter the main menu command:\n";
        cin >> mnum;
        switch (mnum) {
        case 1: {
            /// ¤ Создание дерева
            /*!
            \code
                cout << "To test a tree, you need to create it" << endl;
                while (_getch() != 27) {
                    cout << "Enter value (press ESC to complete entry) ";
                    cin >> val;
                    buildBinTree(val, &Tree);
                }
                print_BT(&Tree, 0);
            \endcode
            */
            cout << "To test a tree, you need to create it" << endl;
            while (_getch() != 27) {
                cout << "Enter value (press ESC to complete entry) ";
                cin >> val;
                buildBinTree(val, &Tree);
            }
            print_BT(&Tree, 0);
            break;
        }
        case 2: {
            /// ¤ Сумма значений в листьях (обратный обход)
            /*!
            \code
                cout << "Sum of values: \n";
                int summa = 0;
                cout << ReverseBypass_count(Tree, summa);
            \endcode
            */
            cout << "Sum of values: \n";
            int summa = 0;
            cout << ReverseBypass_count(Tree, summa);
            
            break;
        }
        case 3: {
            /// ¤ Удаление максимального элемента.
            /*!
            \code
                cout << "Maximum element: \n";
                BinTree* max = MaxValue(Tree);
                int key = max->value;
                cout << key << endl;
                cout << "\nFinal tree: \n";
                MaxValue_del(Tree, key);
                print_BT(&Tree, 0);
            \endcode
            */
            cout << "Maximum element: \n";
            BinTree* max = MaxValue(Tree);
            int key = max->value;
            cout << key << endl;
            cout << "\nFinal tree: \n";
            MaxValue_del(Tree, key);
            print_BT(&Tree, 0);
            break;
        }
        case 4: {
            /// ¤ Вставка нового элемента.
            /*!
            \code
                cout << "Adding a new element to the current tree: \n";
                while (_getch() != 27) {
                    cout << "Enter value (press ESC to complete entry) ";
                    cin >> val;
                    buildBinTree(val, &Tree);
                }
                cout << "Final tree: \n";
                print_BT(&Tree, 0);
            \endcode
            */
            cout << "Adding a new element to the current tree: \n";
            while (_getch() != 27) {
                cout << "Enter value (press ESC to complete entry) ";
                cin >> val;
                buildBinTree(val, &Tree);
            }
            cout << "Final tree: \n";
            print_BT(&Tree, 0);
            break;
        }
        case 5: {
            /// ¤ Определение количества узлов в поддереве.
             /*!
            \code
                cout << "\n\nNumber of nodes in the tree -> ";
                int a = Node_count(Tree);
                cout << a << "\n\nNumber of leaves in a tree -> ";
                int b = Leaf_count(Tree);
                cout << b << endl;
            \endcode
            */
            cout << "\n\nNumber of nodes in the tree -> ";
            int a = Node_count(Tree);
            cout << a << "\n\nNumber of leaves in a tree -> ";
            int b = Leaf_count(Tree);
            cout << b << endl;
            break;
        }
        default:
            main = false;
            break;
        }
    }
}

