#include <iostream>
#include "LinkedList.h"


using namespace std;


typedef LinkedListNode<int> IntNode;
typedef LinkedList<int> IntList;


void printHeader() {
    cout << endl << "#####################################" << endl;
}


int main(int argc, char** argv) {
    cout << endl << "Beginning LinkedList Test." << endl;

    IntList linkedList;

    // Test insertions
    int zero = 0;
    int one = 1;
    int two = 2;
    int three = 3;

    IntNode* threeIntNode = linkedList.insertBeginning(three);
    IntNode* zeroIntNode = linkedList.insertBeginning(zero);
    IntNode* oneIntNode = linkedList.insertAfter(zeroIntNode, one);
    IntNode* twoIntNode = linkedList.insertAfter(oneIntNode, two);

    printHeader();
    cout << endl << "Output Should Match..." << endl;
    cout << "0 -> 1 -> 2 -> 3" << endl;
    cout << endl << "Test Output..." << endl;
    linkedList.print();

    // Test deletions
    printHeader();
    cout << endl << "Output Should Match..." << endl;
    cout << "0 -> 1 -> 3" << endl;
    linkedList.removeAfter(oneIntNode);
    cout << endl << "Test Output..." << endl;
    linkedList.print();

    printHeader();
    cout << endl << "Output Should Match..." << endl;
    cout << "0 -> 1" << endl;
    linkedList.removeAfter(oneIntNode);
    cout << endl << "Test Output..." << endl;
    linkedList.print();

    cout << endl << "Done With LinkedList Test." << endl;
}

