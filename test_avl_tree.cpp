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


int main(int argc, char** argv) {
    cout << endl << "Beginning AVLTree Test." << endl;

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
    cout << endl << "Actual: " << tree.height(tree.getRoot()) << endl;

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
    // Create tree with up to 1000 nodes to really test insertion and balancing
    //
    printHeader();
    cout << endl << "Testing Large Tree Insertions..." << endl;

    IntTree bigTree;

    bool alwaysBalanced = true;
    for (int index = 0; index < 1000; index++) {
        bigTree.insert(rand() % 1000);
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
    cout << bigTree.height(bigTree.getRoot()) << endl;

    //
    // Delete all the nodes and ensure the tree is balanced the whole time
    //
    printHeader();
    cout << endl << "Testing Large Tree Deletions..." << endl;

    alwaysBalanced = true;
    for (int anInt = 0; anInt < 1000; anInt++) {
        bigTree.remove(anInt);
        alwaysBalanced = alwaysBalanced && bigTree.isBalanced();
    }

    if (alwaysBalanced) {
        cout << endl << "Tree was balanced after every delete." << endl;
    } else {
        cout << endl << "Tree went out of balance after a delete." << endl;
    }

    cout << endl << "Tree Contents...";
    cout << endl << "Expected: NULL Root";
    cout << endl << "Actual:   ";
    bigTree.print();

    //
    // Done
    //
    printHeader();
    cout << endl << "Done With AVLTree Test." << endl;
}

