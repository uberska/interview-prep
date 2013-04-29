#pragma once

#include <iostream>


using namespace std;


template <typename DataType>
struct BinaryTreeNode {
    DataType data;
    BinaryTreeNode<DataType>* pLeft;
    BinaryTreeNode<DataType>* pRight;

    BinaryTreeNode(const DataType& incomingData,
        BinaryTreeNode* pIncomingLeft = 0,
        BinaryTreeNode* pIncomingRight = 0) :
        data(incomingData),
        pLeft(pIncomingLeft),
        pRight(pIncomingRight) {}
};


template <class DataType>
class BinaryTree {
public:
    typedef BinaryTreeNode<DataType> Node;

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
            mpRootNode = new Node(data);
        } else {
            this->insert(data, *mpRootNode);
        }
    }

    void remove(const DataType& data) {
        this->remove(data, mpRootNode);
    }

    void print(TraversalType traversalType = IN_ORDER) {
        if (mpRootNode) {
            bool fVisitedANode = false;
            this->traverse(traversalType, &BinaryTree::printTreeNode,
                mpRootNode, true /*fRootOfTree*/, fVisitedANode);
        } else {
            cout << "NULL Root";
        }

        cout << endl;
    }

    const Node* const find(const DataType& data) const {
        return this->find(data, mpRootNode);
    }

    const Node* const getRoot() const { return mpRootNode; }

private:
    Node* mpRootNode;

    typedef void (BinaryTree::*ProcessTreeNodeCallback)(
        Node* pNode, const bool&, bool&);

    const Node* const find(const DataType& data,
        const Node* const pNode) const {

        if (pNode == NULL) {
            return NULL;
        }

        if (data == pNode->data) {
            return pNode;
        } else if (data < pNode->data) {
            return this->find(data, pNode->pLeft);
        } else {
            return this->find(data, pNode->pRight);
        }
    }

    void insert(const DataType& data, Node& node) {
        if (data == node.data) {
            // We don't allow duplicates.
        } else if (data < node.data) {
            if (node.pLeft == 0) {
                node.pLeft = new Node(data);
            } else {
                this->insert(data, *node.pLeft);
            }
        } else {
            if (node.pRight == 0) {
                cout << endl << data;
                node.pRight = new Node(data);
                cout << endl << "done creating new node" << endl;
            } else {
                this->insert(data, *node.pRight);
            }
        }
    }

    void remove(const DataType& data, Node*& pNode) {
        if (!pNode) {
            return;
        }

        if (data == pNode->data) {
            if (!pNode->pLeft && !pNode->pRight) {
                removeNodeWithZeroChildren(pNode);
            } else if (pNode->pLeft && pNode->pRight) {
                removeNodeWithTwoChildren(pNode);
            } else {
                removeNodeWithOneChild(pNode);
            }
        } else if (data < pNode->data) {
            this->remove(data, pNode->pLeft);
        } else {
            this->remove(data, pNode->pRight);
        }
    }

    void removeNodeWithZeroChildren(Node*& pNode) {
        Node* pDelete = pNode;
        pNode = NULL;
        delete pDelete;
    }

    void removeNodeWithOneChild(Node*& pNode) {
        Node* pDelete = pNode;

        // Update the parent of the delete node to point at the single child
        // of the deleted node.
        if (pNode->pLeft) {
            pNode = pNode->pLeft;
        } else {
            pNode = pNode->pRight;
        }

        delete pDelete;
    }

    void removeNodeWithTwoChildren(Node* pNode) {
        // In this function, predecessor refers to the in-order predecessor of
        // the node passed in.

        Node* pPredecessorParent = pNode;
        Node* pPredecessor = pNode->pLeft;

        while (pPredecessor->pRight) {
            pPredecessorParent = pPredecessor;
            pPredecessor = pPredecessor->pRight;
        }

        // Copy the in-order predecessor's data into our node
        pNode->data = pPredecessor->data;

        // Delete the in-order predecessor (which we know has 0 or 1 child. If
        // it had 2 children, one of them would be the predecessor)
        if (!pPredecessor->pLeft && !pPredecessor->pRight) {
            if (pPredecessorParent == pNode) {
                removeNodeWithZeroChildren(pPredecessorParent->pLeft);
            } else {
                removeNodeWithZeroChildren(pPredecessorParent->pRight);
            }
        } else {
            if (pPredecessorParent == pNode) {
                removeNodeWithOneChild(pPredecessorParent->pLeft);
            } else {
                removeNodeWithOneChild(pPredecessorParent->pRight);
            }
        }
    }

    void traverse(TraversalType traversalType,
        ProcessTreeNodeCallback processTreeNode,
        Node* pRootNode,
        const bool& fRootOfTree,
        bool& fVisitedANode) {

        if (pRootNode) {
            if (traversalType == PRE_ORDER) {
                // Root
                (this->*processTreeNode)(pRootNode, fRootOfTree, fVisitedANode);

                // Left
                this->traverse(traversalType, processTreeNode,
                    pRootNode->pLeft, false /*fRootOfTree*/,
                    fVisitedANode);

                // Right
                this->traverse(traversalType, processTreeNode,
                    pRootNode->pRight, false /*fRootOfTree*/,
                    fVisitedANode);
            } else if (traversalType == IN_ORDER) {
                // Left
                this->traverse(traversalType, processTreeNode,
                    pRootNode->pLeft, false /*fRootOfTree*/,
                    fVisitedANode);

                // Root
                (this->*processTreeNode)(pRootNode, fRootOfTree, fVisitedANode);

                // Right
                this->traverse(traversalType, processTreeNode,
                    pRootNode->pRight, false /*fRootOfTree*/,
                    fVisitedANode);
            } else if (traversalType == POST_ORDER) {
                // Left
                this->traverse(traversalType, processTreeNode,
                    pRootNode->pLeft, false /*fRootOfTree*/,
                    fVisitedANode);

                // right
                this->traverse(traversalType, processTreeNode,
                    pRootNode->pRight, false /*fRootOfTree*/,
                    fVisitedANode);

                // Root
                (this->*processTreeNode)(pRootNode, fRootOfTree, fVisitedANode);
            }
        }
    }

    void printTreeNode(Node* pNode, const bool& /*fRootOfTree*/,
        bool& fVisitedANode) {

        if (pNode) {
            if (fVisitedANode) {
                cout << ", ";
            }
            cout << pNode->data;

            fVisitedANode = true;
        }
    }

    void deleteTreeNode(Node* pNode,
        const bool& /*fRootOfTree*/,
        bool& /*fVisitedNode*/) {

        delete pNode;
    }
};

