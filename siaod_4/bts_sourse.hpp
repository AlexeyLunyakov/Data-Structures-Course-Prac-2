/*!
\file
\brief Source file describing the functions that can be used to interact with BTS
*/
#include "bts_head.h"

// Rules for creating BTS:
// all nodes of the node's left subtree have data key values less than the data key value of the node itself
// for all nodes of the right subtree of the node, the values of the data keys are greater than or equal to the value of the data key of the node itself

/*!
\brief BTS construction function
\param val Incoming parameter of new tree element
\param new_tree Incoming parameter of new tree branch
*/
/*!
\code
    Used in the main function in case:
    ...
        buildBinTree(val, &Tree);
    ...
\endcode
*/

void buildBinTree(int val, BinTree** new_tree) {
    if ((*new_tree) == nullptr) {
        (*new_tree) = new BinTree;
        //Putting a new value into the allocated space
        (*new_tree)->value = val;
        //Create empty branches from the current element
        (*new_tree)->left = (*new_tree)->right = nullptr;
        return;
    }
    if (val > (*new_tree)->value) {
        buildBinTree(val, &(*new_tree)->right); //If the argument is greater than the current element, push it to the right
    }
    else {
        buildBinTree(val, &(*new_tree)->left); //Else put it to the left
    }
}

/*!
\brief BTS printing function
\param Tree Incoming parameter of new tree branch
\param l Incoming parameter of the level of element on tree
*/
/*!
\code
    Used in the main function in case:
    ...
    print_BT(&Tree, 0);
    ...
\endcode
*/

void print_BT(BinTree** Tree, int l) {
    int i;
    if (*Tree != nullptr) {
        // Calling this function from the right subtree of the current
        print_BT(&((**Tree).right), l + 1);
        // Indentation increases depending on the level of the element in the tree
        for (i = 1; i <= l; i++) cout << "   ";
        cout << (**Tree).value << endl;
        // Calling this function from the left subtree of the current
        print_BT(&((**Tree).left), l + 1);
    }
}

/*!
\brief Auxiliary variable storage function
\param tmp_sum Incoming parameter of saved amount
*/
/*!
\code
    Used in ReverseBypass_count function
    ...
    summa = main_summ(summa+a);
    ...
\endcode
*/

int main_summ(int tmp_sum) {
    return tmp_sum;
}

/*!
\brief Function to calculate the sum of values in leaves using reverse tree traversal
\param Tree Incoming parameter of new tree branch
\param summa Incoming parameter of the calculated amount
*/
/*!
\code
    Used in the main function in case:
    ...
    int summa = 0;
    cout << ReverseBypass_count(Tree, summa);
    ...
\endcode
*/

int ReverseBypass_count(BinTree* Tree, int& summa) {
    if (Tree != nullptr) {
        ReverseBypass_count(Tree->left, summa);
        ReverseBypass_count(Tree->right, summa);
        int a = Tree->value;
        summa = main_summ(summa+a);
        return summa;
    }
}   

/*!
\brief Function to calculate the number of leaves in a tree
\param Tree Incoming parameter of new tree branch
*/
/*!
\code
    Used in the main function in case:
    ...
    int b = Leaf_count(Tree);
    cout << b << endl;
    ...
\endcode
*/

int Leaf_count(BinTree* Tree) {
    if (!Tree) return 0;
    if (!Tree->left && !Tree->right)
        return 1;
    return  Leaf_count(Tree->left) + Leaf_count(Tree->right);
}

/*!
\brief Function to calculate the number of nodes in a tree
\param Tree Incoming parameter of new tree branch
*/
/*!
\code
    Used in the main function in case:
    ...
    int a = Node_count(Tree);
    cout << a << "\n";
    ...
\endcode
*/

int Node_count(BinTree* Tree) {
    if (Tree == nullptr) return 0;
    return Node_count(Tree->left) + 1 + Node_count(Tree->right);
}

/*!
\brief Function for finding the maximum element of BTS
\param Tree Incoming parameter of new tree branch
*/
/*!
\code
    Used in the main function in case:
    ...
    BinTree* max = MaxValue(Tree);
    int key = max->value;
    ...
\endcode
*/

BinTree* MaxValue(BinTree* Tree) {
    if (Tree->right != nullptr) {
        return  MaxValue(Tree->right);
    }
    else {
        return Tree;
    }
}

/*!
\brief Function to remove the maximum element of BTS
\param Tree Incoming parameter of new tree branch
\param key Incoming parameter of the value to be removed from the tree
*/
/*!
\code
    Used in the main function in case:
    ...
    MaxValue_del(Tree, key);
    ...
\endcode
*/

void MaxValue_del(BinTree* Tree, int key) {
    if (Tree->right->value != key) {
        MaxValue_del(Tree->right, key);
    }
    else {
        Tree->right = nullptr;
    }
}