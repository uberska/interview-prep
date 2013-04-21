#include <iostream>
#include "binaryTreeNode.h"


using namespace std;


template <class DataType>
class BinaryTree {
public:
    BinaryTree() : mpRootNode(0) {}

    enum TraversalType {
        PRE_ORDER,
        IN_ORDER,
        POST_ORDER
    };

    void insert(const DataType& data) {
        if (mpRootNode == 0) {
            mpRootNode = new BinaryTreeNode<DataType>(data);
        } else {
            this->insert(data, *mpRootNode);
        }
    }

    void print(TraversalType traversalType = PRE_ORDER) {
        if (mpRootNode) {
            this->traverse(traversalType, &BinaryTree::printNode, mpRootNode,
                true /*fRootOfTree*/, false /*fVisitedANode*/);
        } else {
            cout << "NULL Root";
        }

        cout << endl;
    }

    typedef void (BinaryTree::*ProcessNodeCallback)(const DataType&,
        bool, bool);

private:
    void insert(const DataType& data, BinaryTreeNode<DataType>& afterNode) {
        if (data < afterNode.getData()) {
            if (afterNode.getLeft() == 0) {
                afterNode.setLeft(new BinaryTreeNode<DataType>(data));
            } else {
                this->insert(data, *afterNode.getLeft());
            }
        } else {
            if (afterNode.getRight() == 0) {
                afterNode.setRight(new BinaryTreeNode<DataType>(data));
            } else {
                this->insert(data, *afterNode.getRight());
            }
        }
    }

    bool traverse(TraversalType traversalType,
        ProcessNodeCallback processNode, BinaryTreeNode<DataType>* pRootNode,
        bool fRootOfTree = false, bool fVisitedANode = false) {

        if (pRootNode) {
            if (traversalType == PRE_ORDER) {
                // Root
                const DataType& data = pRootNode->getData();
                (this->*processNode)(data, fRootOfTree, fVisitedANode);
                fVisitedANode = true;

                // Left
                fVisitedANode |= this->traverse(traversalType, processNode,
                    pRootNode->getLeft(), false /*fRootOfTree*/,
                    fVisitedANode);

                // Right
                fVisitedANode |= this->traverse(traversalType, processNode,
                    pRootNode->getRight(), false /*fRootOfTree*/,
                    fVisitedANode);
            } else if (traversalType == IN_ORDER) {
                // Left
                fVisitedANode |= this->traverse(traversalType, processNode,
                    pRootNode->getLeft(), false /*fRootOfTree*/,
                    fVisitedANode);

                // Root
                (this->*processNode)(pRootNode->getData(), fRootOfTree,
                    fVisitedANode);
                fVisitedANode = true;

                // Right
                fVisitedANode |= this->traverse(traversalType, processNode,
                    pRootNode->getRight(), false /*fRootOfTree*/,
                    fVisitedANode);
            } else if (traversalType == POST_ORDER) {
                // Left
                fVisitedANode |= this->traverse(traversalType, processNode,
                    pRootNode->getLeft(), false /*fRootOfTree*/,
                    fVisitedANode);

                // right
                fVisitedANode |= this->traverse(traversalType, processNode,
                    pRootNode->getRight(), false /*fRootOfTree*/,
                    fVisitedANode);

                // Root
                (this->*processNode)(pRootNode->getData(), fRootOfTree,
                    fVisitedANode);
                fVisitedANode = true;
            }
        }

        return fVisitedANode;
    }

    void printNode(const DataType& data, bool fRootOfTree, bool fVisitedANode) {
        if (fVisitedANode) {
            cout << ", ";
        }
        cout << data;
    }

    BinaryTreeNode<DataType>* mpRootNode;
};

