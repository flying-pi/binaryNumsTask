//
// Created by Yura Braiko on 26.05.17.
//

#ifndef BINARYNUMS_TREE_H
#define BINARYNUMS_TREE_H


class Tree {
public:
    Tree(int size);
    Tree *getNewFork();
    int value();
    Tree *left();
    Tree *right();
    int getCurrentSize();
    Tree *moveToRootZero();
    Tree *moveToRootOne();
    ~Tree();
    bool isLastLevel();


private:
    int *tree;
    int size;
    Tree *parent;
    int forks = 0;
    void addFork();
    void removeFork();
    Tree();
    Tree *move(int offset);
};


#endif //BINARYNUMS_TREE_H
