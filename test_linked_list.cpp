#include <iostream>
#include "LinkedList.h"


using namespace std;


typedef LinkedListNode<int> IntNode;
typedef LinkedList<int> IntList;


void printHeader() {
    cout << endl << "#####################################" << endl;
}


int main(int /*argc*/, char** /*argv*/) {
    cout << endl << "Beginning LinkedList Test." << endl;

    IntList linkedList;

    // Print initial list
    printHeader();
    cout << endl << "Initial List..." << endl;

    linkedList.print();

    // Test insertions
    printHeader();
    cout << endl << "Testing Insertions..." << endl;

    cout << endl << "Expected: 3";
    cout << endl << "Actual:   ";
    linkedList.insertBeginning(3);
    linkedList.print();

    cout << endl << "Expected: 0 -> 3";
    cout << endl << "Actual:   ";
    IntNode* zeroIntNode = linkedList.insertBeginning(0);
    linkedList.print();

    cout << endl << "Expected: 0 -> 1 -> 3";
    cout << endl << "Actual:   ";
    IntNode* oneIntNode = linkedList.insertAfter(zeroIntNode, 1);
    linkedList.print();

    cout << endl << "Expected: 0 -> 1 -> 2 -> 3";
    cout << endl << "Actual:   ";
    linkedList.insertAfter(oneIntNode, 2);
    linkedList.print();

    // Test deletions
    printHeader();
    cout << endl << "Testing Deletions..." << endl;

    cout << endl << "Expected: 0 -> 1 -> 3";
    cout << endl << "Actual:   ";
    linkedList.removeAfter(oneIntNode);
    linkedList.print();

    cout << endl << "Expected: 0 -> 1";
    cout << endl << "Actual:   ";
    linkedList.removeAfter(oneIntNode);
    linkedList.print();

    cout << endl << "Expected: 1";
    cout << endl << "Actual:   ";
    linkedList.removeBeginning();
    linkedList.print();

    cout << endl << "Expected: NULL";
    cout << endl << "Actual:   ";
    linkedList.removeAfter(0);
    linkedList.print();

    cout << endl << "Expected: NULL";
    cout << endl << "Actual:   ";
    linkedList.removeBeginning();
    linkedList.print();

    printHeader();
    cout << endl << "Done With LinkedList Test." << endl;

    return EXIT_SUCCESS;
}

