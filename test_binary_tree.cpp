#include <iostream>
#include "BinaryTree.h"


using namespace std;


typedef BinaryTreeNode<int> IntNode;
typedef BinaryTree<int> IntTree;


void printHeader() {
    cout << endl << "#####################################" << endl;
}


const char* printFound(bool fFound) {
    if (fFound) {
        return "FOUND";
    } else {
        return "NOT FOUND";
    }
}


int main(int /*argc*/, char** /*argv*/) {
    cout << endl << "Beginning BinaryTree Test." << endl;

    //
    // Test insertions and traversal
    //
    printHeader();

    IntTree tree;

    cout << endl << "Testing Insertions And Traversal..." << endl;

    cout << endl << "Inserting 50";
    tree.insert(50);
    cout << endl << "Inserting 30";
    tree.insert(30);
    cout << endl << "Inserting 80";
    tree.insert(80);
    cout << endl << "Inserting 80";
    tree.insert(80);
    cout << endl << "Inserting 40";
    tree.insert(40);
    cout << endl << "Inserting 10";
    tree.insert(10);
    cout << endl << "Inserting 100";
    tree.insert(100);
    cout << endl << "Inserting 0";
    tree.insert(0);
    cout << endl;

    cout << endl << "PRE ORDER:";
    cout << endl << "Expected: 50, 30, 10, 0, 40, 80, 100";
    cout << endl << "Actual:   ";
    tree.print(IntTree::PRE_ORDER);

    cout << endl << "IN ORDER:";
    cout << endl << "Expected: 0, 10, 30, 40, 50, 80, 100";
    cout << endl << "Actual:   ";
    tree.print(IntTree::IN_ORDER);

    cout << endl << "POST ORDER:";
    cout << endl << "Expected: 0, 10, 40, 30, 100, 80, 50";
    cout << endl << "Actual:   ";
    tree.print(IntTree::POST_ORDER);

    //
    // Testing finds
    //
    printHeader();
    cout << endl << "Testing Searches...";

    int shouldFind[] = { 50, 30, 80, 40, 10, 100, 0 };
    int shouldFindSize = sizeof(shouldFind) / sizeof(shouldFind[0]);
    int shouldNotFind[] = { 51, 3, 87 };
    int shouldNotFindSize = sizeof(shouldNotFind) / sizeof(shouldNotFind[0]);

    for (int index = 0; index < shouldFindSize; index++) {
        const IntNode* const pNode = tree.find(shouldFind[index]);
        bool fFound = pNode != NULL;
        if (pNode) {
            assert(pNode->data == shouldFind[index]);
        }

        cout << endl;
        cout << endl << shouldFind[index];
        cout << endl << "Expected: FOUND";
        cout << endl << "Actual:   " << printFound(fFound);
    }

    for (int index = 0; index < shouldNotFindSize; index++) {
        const IntNode* const pNode = tree.find(shouldNotFind[index]);
        bool fFound = pNode != NULL;

        cout << endl;
        cout << endl << shouldNotFind[index];
        cout << endl << "Expected: NOT FOUND";
        cout << endl << "Actual:   " << printFound(fFound);
    }

    cout << endl;

    //
    // Test deletions
    //
    printHeader();
    cout << endl << "Testing Deletions (Traversals IN ORDER)..." << endl;

    cout << endl << "Expected: 0, 10, 30, 40, 80, 100";
    cout << endl << "Actual:   ";
    tree.remove(50);
    tree.print(IntTree::IN_ORDER);

    cout << endl << "Expected: 0, 10, 30, 40, 80";
    cout << endl << "Actual:   ";
    tree.remove(100);
    tree.print(IntTree::IN_ORDER);

    cout << endl << "Expected: 0, 30, 40, 80";
    cout << endl << "Actual:   ";
    tree.remove(10);
    tree.print(IntTree::IN_ORDER);

    cout << endl << "Expected: 0, 30, 40, 80";
    cout << endl << "Actual:   ";
    tree.remove(3);
    tree.print(IntTree::IN_ORDER);

    cout << endl << "Expected: 0, 40, 80";
    cout << endl << "Actual:   ";
    tree.remove(30);
    tree.print(IntTree::IN_ORDER);

    cout << endl << "Expected: 0, 40";
    cout << endl << "Actual:   ";
    tree.remove(80);
    tree.print(IntTree::IN_ORDER);

    cout << endl << "Expected: 40";
    cout << endl << "Actual:   ";
    tree.remove(0);
    tree.print(IntTree::IN_ORDER);

    cout << endl << "Expected: NULL Root";
    cout << endl << "Actual:   ";
    tree.remove(40);
    tree.print(IntTree::IN_ORDER);

    cout << endl << "Expected: NULL Root";
    cout << endl << "Actual:   ";
    tree.remove(3);
    tree.print(IntTree::IN_ORDER);

    //
    // Test deletion of node with two children
    //
    printHeader();

    IntTree deleteTree;

    cout << endl << "Testing Deletion Of Node With Two Children..." << endl;

    cout << endl << "Inserting 30";
    deleteTree.insert(30);
    cout << endl << "Inserting 5";
    deleteTree.insert(5);
    cout << endl << "Inserting 10";
    deleteTree.insert(10);
    cout << endl << "Inserting 0";
    deleteTree.insert(0);
    cout << endl;

    cout << endl << "Initial Tree..." << endl;
    deleteTree.print();

    cout << endl << "Expected: 0, 10, 30";
    cout << endl << "Actual:   ";
    deleteTree.remove(5);
    deleteTree.print();

    //
    // Done.
    //
    printHeader();
    cout << endl << "Done With BinaryTree Test." << endl;
}

