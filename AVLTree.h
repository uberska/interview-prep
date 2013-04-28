#pragma once

#include <cassert>
#include <iostream>


using namespace std;


template <typename DataType>
struct AVLTreeNode {
    DataType data;
    AVLTreeNode<DataType>* pLeft;
    AVLTreeNode<DataType>* pRight;
    unsigned int height;

    AVLTreeNode(const DataType& incomingData, AVLTreeNode* pIncomingLeft = 0,
        AVLTreeNode* pIncomingRight = 0) :
        data(incomingData),
        pLeft(pIncomingLeft),
        pRight(pIncomingRight),
        height(1) {}
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

    int computeHeight(const Node* const pNode) const {
        if (pNode == NULL) {
            return 0;
        }

        return max(computeHeight(pNode->pLeft),
            computeHeight(pNode->pRight)) + 1;
    }

    bool isBalanced() const {
        return isBalanced(mpRootNode);
    }

private:
    Node* mpRootNode;

    typedef void (AVLTree::*ProcessTreeNodeCallback)(
        Node* pNode, const bool&, bool&);

    int balanceFactor(const Node* const pNode) const {
        if (pNode == NULL) {
            return 0;
        }
        return height(pNode->pLeft) - height(pNode->pRight);
    }

    int height(const Node* const pNode) const {
        return pNode == NULL ? 0 : pNode->height;
    }

    int computeBalanceFactor(const Node* const pNode) const {
        if (pNode == NULL) {
            return 0;
        }
        return computeHeight(pNode->pLeft) - computeHeight(pNode->pRight);
    }

    bool isBalanced(const Node* const pNode) const {
        if (pNode == NULL) {
            return true;
        }

        int nodeBalanceFactor = computeBalanceFactor(pNode);
        if (nodeBalanceFactor < -1 || nodeBalanceFactor > 1) {
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

        rebalanceNode(pNode, false /*fForRemove*/);
    }

    void updateNodeHeight(Node* pNode) {
        if (pNode == NULL) {
            return;
        }

        unsigned int leftHeight = pNode->pLeft ? pNode->pLeft->height : 0;
        unsigned int rightHeight = pNode->pRight ? pNode->pRight->height : 0;
        pNode->height = max(leftHeight, rightHeight) + 1;
    }

    Node* leftRotation(Node* pNode) {
        // Perform the rotation
        Node* pRightChild = pNode->pRight;
        pNode->pRight = pRightChild->pLeft;
        pRightChild->pLeft = pNode;

        // Update node heights
        updateNodeHeight(pRightChild->pLeft);
        updateNodeHeight(pRightChild->pRight);
        updateNodeHeight(pRightChild);

        // Return our new root
        return pRightChild;
    }

    Node* rightRotation(Node* pNode) {
        // Perform the rotation
        Node* pLeftChild = pNode->pLeft;
        pNode->pLeft = pLeftChild->pRight;
        pLeftChild->pRight = pNode;

        // Update node heights
        updateNodeHeight(pLeftChild->pLeft);
        updateNodeHeight(pLeftChild->pRight);
        updateNodeHeight(pLeftChild);

        // Return our new root
        return pLeftChild;
    }

    void rebalanceNode(Node*& pNode, bool fForRemove) {
        if (pNode) {
            int nodeBalanceFactor = balanceFactor(pNode);

            assert(nodeBalanceFactor >= -2 || nodeBalanceFactor <= 2);

            if (nodeBalanceFactor == -2) {
                int rightBalanceFactor = balanceFactor(pNode->pRight);

                if (rightBalanceFactor == -1 ||
                    (fForRemove && rightBalanceFactor == 0)) {
                    pNode = leftRotation(pNode);
                } else if (rightBalanceFactor == 1) {
                    pNode->pRight = rightRotation(pNode->pRight);
                    pNode = leftRotation(pNode);
                }
            } else if (nodeBalanceFactor == 2) {
                int leftBalanceFactor = balanceFactor(pNode->pLeft);

                if (leftBalanceFactor == 1 ||
                    (fForRemove && leftBalanceFactor == 0)) {
                    pNode = rightRotation(pNode);
                } else if (leftBalanceFactor == -1) {
                    pNode->pLeft = leftRotation(pNode->pLeft);
                    pNode = rightRotation(pNode);
                }
            }

            updateNodeHeight(pNode);
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

        rebalanceNode(pNode, true /*fForRemove*/);
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

    void rebalancePredecessorParentsForRemove(Node*& pNode) {
        if (!pNode) {
            return;
        }

        if (pNode->pRight != NULL) {
            rebalancePredecessorParentsForRemove(pNode->pRight);
        }

        rebalanceNode(pNode, true /*fForRemove*/);
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

        // Now that we've removed the node, we need to rebalance from the
        // parent of the node we removed to the current node's left child.
        // The caller calling us with take care of balancing from us upward.
        if (pNode && pNode->pLeft) {
            rebalancePredecessorParentsForRemove(pNode->pLeft);
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

