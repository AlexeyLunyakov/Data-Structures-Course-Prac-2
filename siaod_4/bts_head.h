/*!
\file
\brief Header file describing the structure of a binary tree
*/
#ifndef SIAOD_4_BTS_HEAD_H
#define SIAOD_4_BTS_HEAD_H

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <cmath>
using namespace std;

/// <summary>
///  Structure of the Binary Search Tree
/// </summary>
struct BinTree {
    ///Information part
    int value;
    ///Addresses of the left branch
    BinTree* left;
    ///Addresses of the right branch
    BinTree* right;
};

#endif //SIAOD_4_BTS_HEAD_H