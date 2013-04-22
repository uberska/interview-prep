#include <iostream>
#include "binaryTreeNode.h"


using namespace std;


template <class DataType>
class BinaryTree {
public:
    BinaryTree() : mpRootNode(0) {}

    ~BinaryTree() {
        bool fVisitedANode = false;
        this->traverse(POST_ORDER, &BinaryTree::deleteTreeNode, mpRootNode,
            true /*fRootOfTree*/, fVisitedANode);
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

    void remove(const DataType& data) {
        cout << "BinaryTree::remove Not Yet Implemented" << endl;
    }

    void print(TraversalType traversalType = PRE_ORDER) {
        if (mpRootNode) {
            bool fVisitedANode = false;
            this->traverse(traversalType, &BinaryTree::printTreeNode,
                mpRootNode, true /*fRootOfTree*/, fVisitedANode);
        } else {
            cout << "NULL Root";
        }

        cout << endl;
    }

private:
    typedef void (BinaryTree::*ProcessTreeNodeCallback)(
        BinaryTreeNode<DataType>* pNode, const bool&, bool&);

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

    void traverse(TraversalType traversalType,
        ProcessTreeNodeCallback processTreeNode,
        BinaryTreeNode<DataType>* pRootNode,
        const bool& fRootOfTree,
        bool& fVisitedANode) {

        if (pRootNode) {
            if (traversalType == PRE_ORDER) {
                // Root
                (this->*processTreeNode)(pRootNode, fRootOfTree, fVisitedANode);

                // Left
                this->traverse(traversalType, processTreeNode,
                    pRootNode->getLeft(), false /*fRootOfTree*/,
                    fVisitedANode);

                // Right
                this->traverse(traversalType, processTreeNode,
                    pRootNode->getRight(), false /*fRootOfTree*/,
                    fVisitedANode);
            } else if (traversalType == IN_ORDER) {
                // Left
                this->traverse(traversalType, processTreeNode,
                    pRootNode->getLeft(), false /*fRootOfTree*/,
                    fVisitedANode);

                // Root
                (this->*processTreeNode)(pRootNode, fRootOfTree, fVisitedANode);

                // Right
                this->traverse(traversalType, processTreeNode,
                    pRootNode->getRight(), false /*fRootOfTree*/,
                    fVisitedANode);
            } else if (traversalType == POST_ORDER) {
                // Left
                this->traverse(traversalType, processTreeNode,
                    pRootNode->getLeft(), false /*fRootOfTree*/,
                    fVisitedANode);

                // right
                this->traverse(traversalType, processTreeNode,
                    pRootNode->getRight(), false /*fRootOfTree*/,
                    fVisitedANode);

                // Root
                (this->*processTreeNode)(pRootNode, fRootOfTree, fVisitedANode);
            }
        }
    }

    void printTreeNode(BinaryTreeNode<DataType>* pNode,
        const bool& fRootOfTree,
        bool& fVisitedANode) {

        if (pNode) {
            if (fVisitedANode) {
                cout << ", ";
            }
            cout << pNode->getData();

            fVisitedANode = true;
        }
    }

    void deleteTreeNode(BinaryTreeNode<DataType>* pNode,
        const bool& /*fRootOfTree*/,
        bool& /*fVisitedNode*/) {

        delete pNode;
    }

    BinaryTreeNode<DataType>* mpRootNode;
};

