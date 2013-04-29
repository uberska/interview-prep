#include <cstdlib>
#include <ctime>
#include <iostream>
#include "AVLTree.h"


using namespace std;


typedef AVLTreeNode<int> IntNode;
typedef AVLTree<int> IntTree;


void printHeader() {
    cout << endl << "#####################################" << endl;
}


const char* const getYesNo(bool value) {
    if (value) {
        return "Yes";
    } else {
        return"No";
    }
}


const char* printFound(bool fFound) {
    if (fFound) {
        return "FOUND";
    } else {
        return "NOT FOUND";
    }
}


int main(int /*argc*/, char** /*argv*/) {
    cout << endl << "Beginning AVLTree Test." << endl;

    srand(time(NULL));

    //
    // Test insertions
    //
    printHeader();
    cout << endl << "Testing Insertions And Traversal..." << endl;

    IntTree tree;

    cout << endl << "Inserting 50";
    tree.insert(50);
    cout << endl << "Tree Balanced? - " << getYesNo(tree.isBalanced()) << endl;

    cout << endl << "Inserting 30";
    tree.insert(30);
    cout << endl << "Tree Balanced? - " << getYesNo(tree.isBalanced()) << endl;

    cout << endl << "Inserting 80";
    tree.insert(80);
    cout << endl << "Tree Balanced? - " << getYesNo(tree.isBalanced()) << endl;

    cout << endl << "Inserting 80";
    tree.insert(80);
    cout << endl << "Tree Balanced? - " << getYesNo(tree.isBalanced()) << endl;

    cout << endl << "Inserting 40";
    tree.insert(40);
    cout << endl << "Tree Balanced? - " << getYesNo(tree.isBalanced()) << endl;

    cout << endl << "Inserting 10";
    tree.insert(10);
    cout << endl << "Tree Balanced? - " << getYesNo(tree.isBalanced()) << endl;

    cout << endl << "Inserting 100";
    tree.insert(100);
    cout << endl << "Tree Balanced? - " << getYesNo(tree.isBalanced()) << endl;

    cout << endl << "Inserting 5";
    tree.insert(5);
    cout << endl << "Tree Balanced? - " << getYesNo(tree.isBalanced()) << endl;

    cout << endl << "Inserting 0";
    tree.insert(0);
    cout << endl << "Tree Balanced? - " << getYesNo(tree.isBalanced()) << endl;

    cout << endl;

    cout << endl << "PRE ORDER:";
    cout << endl << "Expected: 50, 30, 5, 0, 10, 40, 80, 100";
    cout << endl << "Actual:   ";
    tree.print(IntTree::PRE_ORDER);

    cout << endl << "IN ORDER:";
    cout << endl << "Expected: 0, 5, 10, 30, 40, 50, 80, 100";
    cout << endl << "Actual:   ";
    tree.print();

    cout << endl << "POST ORDER:";
    cout << endl << "Expected: 0, 10, 5, 40, 30, 100, 80, 50";
    cout << endl << "Actual:   ";
    tree.print(IntTree::POST_ORDER);

    cout << endl << "Tree Height:";
    cout << endl << "Expected: 4";
    cout << endl << "Actual: " << tree.computeHeight(tree.getRoot()) << endl;

    //
    // Testing finds
    //
    printHeader();
    cout << endl << "Testing Searches...";

    int shouldFind[] = { 0, 5, 10, 30, 40, 50, 80, 100 };
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
    // Testing deltions
    //
    printHeader();
    cout << endl << "Testing Deletions (Traversals IN ORDER)..." << endl;

    cout << endl << "Expected: 0, 10, 30, 40, 50, 80, 100";
    cout << endl << "Actual:   ";
    tree.remove(5);
    tree.print();

    cout << endl << "Tree Balanced? - " << getYesNo(tree.isBalanced()) << endl;

    cout << endl << "Expected: 0, 10, 30, 40, 80, 100";
    cout << endl << "Actual:   ";
    tree.remove(50);
    tree.print();

    cout << endl << "Tree Balanced? - " << getYesNo(tree.isBalanced()) << endl;

    cout << endl << "Expected: 0, 10, 30, 40, 80";
    cout << endl << "Actual:   ";
    tree.remove(100);
    tree.print();

    cout << endl << "Tree Balanced? - " << getYesNo(tree.isBalanced()) << endl;

    cout << endl << "Expected: 0, 30, 40, 80";
    cout << endl << "Actual:   ";
    tree.remove(10);
    tree.print();

    cout << endl << "Tree Balanced? - " << getYesNo(tree.isBalanced()) << endl;

    cout << endl << "Expected: 0, 30, 40, 80";
    cout << endl << "Actual:   ";
    tree.remove(3);
    tree.print();

    cout << endl << "Tree Balanced? - " << getYesNo(tree.isBalanced()) << endl;

    cout << endl << "Expected: 0, 40, 80";
    cout << endl << "Actual:   ";
    tree.remove(30);
    tree.print();

    cout << endl << "Tree Balanced? - " << getYesNo(tree.isBalanced()) << endl;

    cout << endl << "Expected: 0, 40";
    cout << endl << "Actual:   ";
    tree.remove(80);
    tree.print();

    cout << endl << "Tree Balanced? - " << getYesNo(tree.isBalanced()) << endl;

    cout << endl << "Expected: 40";
    cout << endl << "Actual:   ";
    tree.remove(0);
    tree.print();

    cout << endl << "Tree Balanced? - " << getYesNo(tree.isBalanced()) << endl;

    cout << endl << "Expected: NULL Root";
    cout << endl << "Actual:   ";
    tree.remove(40);
    tree.print();

    cout << endl << "Tree Balanced? - " << getYesNo(tree.isBalanced()) << endl;

    cout << endl << "Expected: NULL Root";
    cout << endl << "Actual:   ";
    tree.remove(3);
    tree.print();

    cout << endl << "Tree Balanced? - " << getYesNo(tree.isBalanced()) << endl;

    //
    // Create tree with up to numNodesAndRange nodes to really test insertion
    // and balancing
    //
    printHeader();
    cout << endl << "Testing Large Tree Insertions..." << endl;

    IntTree bigTree;

    int numNodesAndRange = 1000;

    bool alwaysBalanced = true;
    for (int index = 0; index < numNodesAndRange; index++) {
        bigTree.insert(rand() % numNodesAndRange);
        alwaysBalanced = alwaysBalanced && bigTree.isBalanced();
    }

    cout << endl << "Tree Contents:" << endl;
    bigTree.print();

    if (alwaysBalanced) {
        cout << endl << "Tree was balanced after every insert." << endl;
    } else {
        cout << endl << "Tree went out of balance after an insert." << endl;
    }

    cout << endl << "Tree Height: ";
    cout << bigTree.computeHeight(bigTree.getRoot()) << endl;

    //
    // Delete all the nodes and ensure the tree is balanced the whole time
    //
    printHeader();
    cout << endl << "Testing Large Tree Deletions..." << endl;

    alwaysBalanced = true;
    while (bigTree.getRoot() != NULL) {
        bigTree.remove(rand() % numNodesAndRange);
        alwaysBalanced = alwaysBalanced && bigTree.isBalanced();
    }

    if (alwaysBalanced) {
        cout << endl << "Tree was balanced after every delete." << endl;
    } else {
        cout << endl << "Tree went out of balance after a delete." << endl;
    }

    //
    // Done
    //
    printHeader();
    cout << endl << "Done With AVLTree Test." << endl;
}

