#include <iostream>
#include <math.h>
#include "Tree.h"

using namespace std;


void printResult(int *out, int length) {
    for (int i = 0; i < length; i++) {
        cout << out[i];
    }
    cout << endl;
}

char *toBinaryText(unsigned int num, char *buf, int size) {
    int r = 0;
    while (num != 0) {
        r = num % 2;
        num /= 2;
        buf[size - 1] = (r == 1 ? '1' : '0');
        size--;
    }
    for (int i = 0; i < size; i++)
        buf[i] = '0';
    return buf;
}


char *copyText(char *source, int size) {
    char *result = new char[size];
    for (int i = 0; i < size; i++)
        result[i] = source[i];
    return result;
}

int *copyItem(int *out, int length) {
    int *result = new int[length];
    for (int i = 0; i < length; i++)
        result[i] = out[i];
    return result;
}

int fibonacci(int pos, int a, int b) {
    if (pos == 0)
        return b;
    return fibonacci(pos - 1, b, a + b);
}

int fibonacci(int pos) {
    return fibonacci(pos - 2, 1, 1);
}

int downCountPowMethod(char *out, unsigned int from, unsigned int acomulator, int count, int limit) {
    int result = 0;
    if (from == 0)
        return 0;
    if (limit == 0)
        return 0;

    while (from > 0) {
        result++;
        cout << toBinaryText(acomulator + from, out, count) << endl;
        result += downCountPowMethod(out, from >> 2, acomulator + from, count, limit - 1);
        from >>= 1;
    }
    return result;
}

int countCombinationByPow(int count) {
    char *out = new char[count + 1];
    for (int i = 0; i < count; i++)
        out[i] = '0';
    out[count] = '\0';

    int result = 1;
    cout << toBinaryText(0, out, count) << endl;

    int limit = count / 2;
    unsigned int counter = 1;
    unsigned int final = (unsigned int) pow(2, count);
    while (counter < final) {
        cout << toBinaryText(counter, out, count) << endl;
        result++;
        result += downCountPowMethod(out, counter >> 2, counter, count, limit - 1);
        counter <<= 1;
    }
    return result;
}

int countCombination(double length, int *out, int currentPosition, double sum) {
    if (sum > length / 2) {
        delete[]out;
        return 0;
    }
    if (length == currentPosition) {
        printResult(out, length);
        delete[]out;
        return 1;
    }
    int oneWay = 0;
    if (currentPosition == 0 || out[currentPosition - 1] != 1) {
        int *copy = copyItem(out, length);
        copy[currentPosition] = 1;
        oneWay = countCombination(length, copy, currentPosition + 1, sum + 1);
    }
    out[currentPosition] = 0;
    int zeroWay = countCombination(length, out, currentPosition + 1, sum);
    return zeroWay + oneWay;
}



int countWithTree(Tree *tree, int bufPos, char *buf, int bufSize, int maxOneLenth) {
    int result = 0;
    if (tree->isLastLevel()) {
        int result = 1;
        int value = tree->value();
        if (value == 1)
            maxOneLenth--;
        if (maxOneLenth >= 0) {
            buf[bufPos] = value == 0 ? '0' : '1';
            cout << buf << endl;
        } else {
            result = 0;
        }
        delete[] buf;
        delete tree;
        return result;
    }

    if (tree->value() == 0) {
        buf[bufPos] = '0';
        result += countWithTree(tree->getNewFork()->right(), bufPos + 1, copyText(buf, bufSize), bufSize, maxOneLenth);
        result += countWithTree(tree->left(), bufPos + 1, buf, bufSize, maxOneLenth);
    } else {
        maxOneLenth--;
        buf[bufPos] = '1';
        result += countWithTree(tree->left(), bufPos + 1, buf, bufSize, maxOneLenth);
    }
    return result;
}

int countWithTree(int size) {
    Tree *tree = new Tree(size * 2);

    char *text = new char[size + 1];
    text[size] = '\0';
    int leftSide = countWithTree(tree->getNewFork()->moveToRootZero(), 0, text, size, size / 2);

    text = new char[size + 1];
    text[size] = '\0';
    int rightSide = countWithTree(tree->getNewFork()->moveToRootOne(), 0, text, size, size / 2);

    delete tree;
    return leftSide + rightSide;
}

int main() {

    int count;
    cout << "enter num size :: ";
    cin >> count;
    char answer = ' ';


    int treeResult = -1;
    cout << "enter t for count with tree :: ";
    cin >> answer;
    if (answer == 't') {
        treeResult = countWithTree(count);
        cout << "answer :: " << treeResult << endl << endl;
    }


    int powResult = -1;
    cout << "enter p for count with pow :: ";
    cin >> answer;
    if (answer == 'p') {
        powResult = countCombinationByPow(count);
        cout << "answer :: " << powResult << endl << endl;
    }


    int combinationResult = -1;
    cout << "enter c for count with combination :: ";
    cin >> answer;
    if (answer == 'c') {
        combinationResult = countCombination(count, new int[count], 0, 0);
        cout << "answer :: " << combinationResult << endl << endl;
    }


    int fibonacciResult = -1;
    cout << "enter f for count by fibonacci  method:: ";
    cin >> answer;
    if (answer == 'f') {
        fibonacciResult = fibonacci(count + 2) - 1 * (count % 2);
        cout << "answer :: " << fibonacciResult << endl << endl;
    }

    if (powResult == -1 && combinationResult == -1 && fibonacciResult == -1 && treeResult == -1) {
        cout << "sorry, but we have not one more method ;(";
    } else {
        cout << "summary :: \n";
        cout
                << "________________________________________________________________________________________________________________________________________________\n\n";

        if (treeResult != -1)
            cout << "tree result \t\t\t\t\t\t\t" << treeResult << endl;
        if (powResult != -1)
            cout << "check all combination with pow method \t" << powResult << endl;
        if (combinationResult != -1)
            cout << "check all combination result \t\t\t" << combinationResult << endl;
        if (fibonacciResult != -1)
            cout << "analytic result \t\t\t\t\t\t" << fibonacciResult << endl;
    }
    return 0;
}