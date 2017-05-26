//
// Created by Yura Braiko on 26.05.17.
//

#include "Tree.h"

Tree::Tree(int size) {
    parent = new Tree();
    parent->tree = new int[size];
    parent->size = size;
    for (int i = 0; i < size; i += 2) {
        parent->tree[i] = 0;
        parent->tree[i + 1] = 1;
    }

    parent->parent = nullptr;

    parent->addFork();

    this->tree = parent->tree;
    this->size = size;
}

Tree *Tree::getNewFork() {
    Tree *result = new Tree();
    result->parent = this->parent;
    result->tree = this->tree;
    result->size = this->size;
    parent->addFork();
    return result;
}

int Tree::value() {
    return (*tree);
}

Tree *Tree::left() {
    return move(value() == 0 ? 2 : 1);
}

Tree *Tree::right() {
    if (value() != 0)
        throw "only zero can move to one";
    return move(3);;
}

int Tree::getCurrentSize() {
    return size;
}

Tree *Tree::moveToRootZero() {
    this->tree = parent->tree;
    this->size = parent->size;
    return this;
}

Tree *Tree::moveToRootOne() {
    this->tree = parent->tree + 1;
    this->size = parent->size - 1;
    return this;
}

Tree::~Tree() {
    if (parent != nullptr && this != parent)
        parent->removeFork();
}

bool Tree::isLastLevel() {
    return this->size <= 2;
}

void Tree::addFork() {
    forks++;
}

void Tree::removeFork() {
    forks--;
    if (forks == 0) {
        delete[]tree;
        delete this;
    }
}

Tree::Tree() {
}

Tree *Tree::move(int offset) {
    if (size < offset)
        throw "can not move by tree";
    this->tree = tree + offset;
    this->size = size - offset;
    return this;
}
