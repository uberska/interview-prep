#include <iostream>
#include "BinaryTree.h"


using namespace std;


typedef BinaryTreeNode<int> IntNode;
typedef BinaryTree<int> IntTree;


void printHeader() {
    cout << endl << "#####################################" << endl;
}


int main(int argc, char** argv) {
    cout << endl << "Beginning BinaryTree Test." << endl;

    IntTree tree;

    // Print initial tree
    printHeader();
    cout << endl << "Initial Tree..." << endl;

    tree.print();

    // Test insertions
    printHeader();
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

    // Test deletions
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

    printHeader();
    cout << endl << "Done With BinaryTree Test." << endl;
}

