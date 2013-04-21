#include <iostream>
#include "binaryTreeNode.h"


using namespace std;


template <class DataType>
class BinaryTree {
public:
    BinaryTree() : mpRootNode(0) {}

    ~BinaryTree() {
        this->traverse(POST_ORDER, &BinaryTree::deleteTreeNode, mpRootNode,
            true /*fRootOfTree*/, false /*fVisitedANode*/);
    }

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
            this->traverse(traversalType, &BinaryTree::printTreeNode,
                mpRootNode, true /*fRootOfTree*/, false /*fVisitedANode*/);
        } else {
            cout << "NULL Root";
        }

        cout << endl;
    }

private:
    typedef void (BinaryTree::*ProcessTreeNodeCallback)(
        BinaryTreeNode<DataType>* pNode, bool, bool);

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
        ProcessTreeNodeCallback processTreeNode,
        BinaryTreeNode<DataType>* pRootNode,
        bool fRootOfTree,
        bool fVisitedANode) {

        if (pRootNode) {
            if (traversalType == PRE_ORDER) {
                // Root
                (this->*processTreeNode)(pRootNode, fRootOfTree, fVisitedANode);
                fVisitedANode = true;

                // Left
                fVisitedANode |= this->traverse(traversalType, processTreeNode,
                    pRootNode->getLeft(), false /*fRootOfTree*/,
                    fVisitedANode);

                // Right
                fVisitedANode |= this->traverse(traversalType, processTreeNode,
                    pRootNode->getRight(), false /*fRootOfTree*/,
                    fVisitedANode);
            } else if (traversalType == IN_ORDER) {
                // Left
                fVisitedANode |= this->traverse(traversalType, processTreeNode,
                    pRootNode->getLeft(), false /*fRootOfTree*/,
                    fVisitedANode);

                // Root
                (this->*processTreeNode)(pRootNode, fRootOfTree, fVisitedANode);
                fVisitedANode = true;

                // Right
                fVisitedANode |= this->traverse(traversalType, processTreeNode,
                    pRootNode->getRight(), false /*fRootOfTree*/,
                    fVisitedANode);
            } else if (traversalType == POST_ORDER) {
                // Left
                fVisitedANode |= this->traverse(traversalType, processTreeNode,
                    pRootNode->getLeft(), false /*fRootOfTree*/,
                    fVisitedANode);

                // right
                fVisitedANode |= this->traverse(traversalType, processTreeNode,
                    pRootNode->getRight(), false /*fRootOfTree*/,
                    fVisitedANode);

                // Root
                (this->*processTreeNode)(pRootNode, fRootOfTree, fVisitedANode);
                fVisitedANode = true;
            }
        }

        return fVisitedANode;
    }

    void printTreeNode(BinaryTreeNode<DataType>* pNode,
        bool fRootOfTree,
        bool fVisitedANode) {

        if (pNode) {
            if (fVisitedANode) {
                cout << ", ";
            }
            cout << pNode->getData();
        }
    }

    void deleteTreeNode(BinaryTreeNode<DataType>* pNode,
        bool /*fRootOfTree*/,
        bool /*fVisitedNode*/) {
        delete pNode;
    }

    BinaryTreeNode<DataType>* mpRootNode;
};

