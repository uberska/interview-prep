#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sys/time.h>
#include "AVLTree.h"
#include "BinaryTree.h"


using namespace std;


typedef AVLTreeNode<int> AVLIntNode;
typedef AVLTree<int> AVLIntTree;

typedef BinaryTreeNode<int> BSTIntNode;
typedef BinaryTree<int> BSTIntTree;


void printHeader() {
    cout << endl << "#####################################" << endl;
}


const char* const getYesNo(bool value) {
    if (value) {
        return "Yes";
    } else {
        return "No";
    }
}


// Populate array with integers. If fRandom is true, the values will be
// from 0 to range. If fRandom is false, the integer will match the index in
// the array (completely sorted ascending).
void populateArray(int* array, int size, int range, bool fRandom) {
    for (int index = 0; index < size; index++) {
        if (fRandom) {
            array[index] = rand() % range;
        } else {
            array[index] = index;
        }
    }
}


double diffTime(timeval t1, timeval t2) {
    // http://stackoverflow.com/questions/2150291/how-do-i-measure-a-time-interval-in-c
    double elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;  // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;      // us to ms
    return elapsedTime / 1000.0; // to seconds
}


void compareTrees(int numNodesAndRange, bool fRandom) {
    //
    // Test insertions
    //
    printHeader();
    cout << endl << numNodesAndRange << " Insertions..." << endl;

    AVLIntTree avlTree;
    BSTIntTree bstTree;

    int* array = new int[numNodesAndRange];
    populateArray(array, numNodesAndRange, numNodesAndRange, fRandom);

    timeval start;
    timeval end;

    // BinaryTree
    gettimeofday(&start, NULL);
    for (int index = 0; index < numNodesAndRange; index++) {
        bstTree.insert(array[index]);
    }
    gettimeofday(&end, NULL);

    cout << endl << "BST Elapsed: " << diffTime(start, end) << endl;

    // AVLTree
    gettimeofday(&start, NULL);
    for (int index = 0; index < numNodesAndRange; index++) {
        avlTree.insert(array[index]);
    }
    gettimeofday(&end, NULL);

    cout << "AVL Elapsed: " << diffTime(start, end) << endl;

    //
    // Test searches
    //
    cout << endl << numNodesAndRange << " Searches..." << endl;

    // BinaryTree
    gettimeofday(&start, NULL);
    for (int index = 0; index < numNodesAndRange; index++) {
        bstTree.find(array[index]);
        //assert(pNode != NULL);
    }
    gettimeofday(&end, NULL);

    cout << endl << "BST Elapsed: " << diffTime(start, end) << endl;

    // AVLTree
    gettimeofday(&start, NULL);
    for (int index = 0; index < numNodesAndRange; index++) {
        avlTree.find(array[index]);
        //assert(pNode != NULL);
    }
    gettimeofday(&end, NULL);

    cout << "AVL Elapsed: " << diffTime(start, end) << endl;

    //
    // Test deletions
    //
    cout << endl << numNodesAndRange << " Deletions..." << endl;

    // BinaryTree
    gettimeofday(&start, NULL);
    for (int index = 0; index < numNodesAndRange; index++) {
        bstTree.remove(array[index]);
    }
    gettimeofday(&end, NULL);

    cout << endl << "BST Elapsed: " << diffTime(start, end) << endl;

    // AVLTree
    gettimeofday(&start, NULL);
    for (int index = 0; index < numNodesAndRange; index++) {
        avlTree.remove(array[index]);
    }
    gettimeofday(&end, NULL);

    cout << "AVL Elapsed: " << diffTime(start, end) << endl;

    //
    // Cleanup
    //
    delete [] array;
}


int main(int /*argc*/, char** /*argv*/) {
    cout << endl << "Beginning Tree Perf Test." << endl;

    srand(time(NULL));

    printHeader();
    cout << endl << "SORTED NUMBERS" << endl;

    compareTrees(1000, false /*fRandom*/);
    compareTrees(10000, false /*fRandom*/);
    compareTrees(100000, false /*fRandom*/);
    compareTrees(1000000, false /*fRandom*/);
    compareTrees(10000000, false /*fRandom*/);
    compareTrees(100000000, false /*fRandom*/);

    printHeader();
    cout << endl << "RANDOMLY GENERATED NUMBERS" << endl;

    compareTrees(1000, true /*fRandom*/);
    compareTrees(10000, true /*fRandom*/);
    compareTrees(100000, true /*fRandom*/);
    compareTrees(1000000, true /*fRandom*/);
    compareTrees(10000000, true /*fRandom*/);
    compareTrees(100000000, true /*fRandom*/);

    printHeader();
    cout << endl << "Done With Tree Perf Test." << endl;
}

