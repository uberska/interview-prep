#pragma once

#include <cassert>
#include <iostream>


using namespace std;


template <typename DataType>
struct AVLTreeNode {
    DataType data;
    AVLTreeNode<DataType>* pLeft;
    AVLTreeNode<DataType>* pRight;

    AVLTreeNode(const DataType& incomingData, AVLTreeNode* pIncomingLeft = 0,
        AVLTreeNode* pIncomingRight = 0) :
        data(incomingData),
        pLeft(pIncomingLeft),
        pRight(pIncomingRight) {}
};


template <class DataType>
class AVLTree {
public:
    typedef AVLTreeNode<DataType> Node;

    AVLTree() : mpRootNode(0) {}

    ~AVLTree() {
        bool fVisitedANode = false;
        this->traverse(POST_ORDER, &AVLTree::deleteTreeNode, mpRootNode,
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
            this->insert(data, mpRootNode);
        }
    }

    void remove(const DataType& data) {
        this->remove(data, mpRootNode);
    }

    void print(TraversalType traversalType = IN_ORDER) {
        if (mpRootNode) {
            bool fVisitedANode = false;
            this->traverse(traversalType, &AVLTree::printTreeNode,
                mpRootNode, true /*fRootOfTree*/, fVisitedANode);
        } else {
            cout << "NULL Root";
        }

        cout << endl;
    }

    const Node* const getRoot() const { return mpRootNode; }

    int balanceFactor(const Node* const pNode) const {
        if (pNode == NULL) {
            return 0;
        }
        return height(pNode->pLeft) - height(pNode->pRight);
    }

    int height(const Node* const pNode) const {
        if (pNode == NULL) {
            return 0;
        }

        return max(height(pNode->pLeft),
            height(pNode->pRight)) + 1;
    }

    bool isBalanced() const {
        return isBalanced(mpRootNode);
    }

private:
    Node* mpRootNode;

    typedef void (AVLTree::*ProcessTreeNodeCallback)(
        Node* pNode, const bool&, bool&);

    bool isBalanced(const Node* const pNode) const {
        if (pNode == NULL) {
            return true;
        }

        int balanceFactor = this->balanceFactor(pNode);
        if (balanceFactor < -1 || balanceFactor > 1) {
            return false;
        }

        return isBalanced(pNode->pLeft) && isBalanced(pNode->pRight);
    }

    void insert(const DataType& data, Node*& pNode) {
        assert(pNode != NULL);

        if (data == pNode->data) {
            // We don't allow duplicates.
        } else if (data < pNode->data) {
            if (pNode->pLeft == 0) {
                pNode->pLeft = new Node(data);
            } else {
                this->insert(data, pNode->pLeft);
            }
        } else {
            if (pNode->pRight == 0) {
                pNode->pRight = new Node(data);
            } else {
                this->insert(data, pNode->pRight);
            }
        }

        int balanceFactor = this->balanceFactor(pNode);
        assert(balanceFactor >= -2 || balanceFactor <= 2);
        if (balanceFactor == -2) {
            int rightBalanceFactor = this->balanceFactor(pNode->pRight);
            if (rightBalanceFactor == -1) {
                pNode = leftRotation(pNode);
            } else if (rightBalanceFactor == 1) {
                pNode->pRight = rightRotation(pNode->pRight);
                pNode = leftRotation(pNode);
            }
        } else if (balanceFactor == 2) {
            int leftBalanceFactor = this->balanceFactor(pNode->pLeft);
            if (leftBalanceFactor == 1) {
                pNode = rightRotation(pNode);
            } else if (leftBalanceFactor == -1) {
                pNode->pLeft = leftRotation(pNode->pLeft);
                pNode = rightRotation(pNode);
            }
        }
    }

    Node* leftRotation(Node* pNode) {
        Node* pRightChild = pNode->pRight;
        pNode->pRight = pRightChild->pLeft;
        pRightChild->pLeft = pNode;
        return pRightChild;
    }

    Node* rightRotation(Node* pNode) {
        Node* pLeftChild = pNode->pLeft;
        pNode->pLeft = pLeftChild->pRight;
        pLeftChild->pRight = pNode;
        return pLeftChild;
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

    void printTreeNode(Node* pNode, const bool& fRootOfTree,
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

