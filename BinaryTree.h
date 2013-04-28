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
        // Handle the root case
        if (mpRootNode && data == mpRootNode->data) {
            if (!mpRootNode->pLeft && !mpRootNode->pRight) {
                // The root node doesn't have any children. Just delete it.
                delete mpRootNode;
                mpRootNode = 0;
            } else if (mpRootNode->pLeft && mpRootNode->pRight) {
                // The root node has two children.
                removeNodeWithTwoChildren(*mpRootNode);
            } else {
                // The root node has one child.

                Node* pDelete = mpRootNode;

                // Get our new root node.
                if (mpRootNode->pLeft) {
                    // The root node has only one child (the left node).
                    mpRootNode = mpRootNode->pLeft;
                } else {
                    // The root node has only one child (the right node).
                    mpRootNode = mpRootNode->pRight;
                }

                // Delete the old root node.
                delete pDelete;
            }
        } else {
            this->removeChild(data, mpRootNode);
        }
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

    const Node* const getRoot() const { return mpRootNode; }

private:
    Node* mpRootNode;

    typedef void (BinaryTree::*ProcessTreeNodeCallback)(
        Node* pNode, const bool&, bool&);

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
                node.pRight = new Node(data);
            } else {
                this->insert(data, *node.pRight);
            }
        }
    }

    // Check the children of pNode to see if they match data. If so, delete
    // them. We operate at this level because there are instances where we need
    // to update the parent of the deleted node, but nodes don't have back
    // pointers to their parents.
    void removeChild(const DataType& data, Node* pNode) {

        if (!pNode) {
            return;
        }

        if (pNode->pLeft && data == pNode->pLeft->data) {
            // Our left child is the node to delete. Delete it.

            Node* pDelete = pNode->pLeft;

            if (!pDelete->pLeft && !pDelete->pRight) {
                // It doesn't have any children. Delete the node and update
                // our left pointer.
                pNode->pLeft = NULL;
                delete pDelete;
            } else if (pDelete->pLeft && pDelete->pRight) {
                // The node has two children.
                removeNodeWithTwoChildren(*pDelete);
            } else {
                // The node must only have one child.
                removeNodeWithOneChild(pDelete, pNode,
                    true /*fDeleteNodeLeftOfParent*/);
            }
        } else if (pNode->pRight && data == pNode->pRight->data) {
            // Our right child is the node to delete. Delete it.

            Node* pDelete = pNode->pRight;

            if (!pDelete->pLeft && !pDelete->pRight) {
                // It doesn't have any children. Delete the node and update
                // our left pointer.
                pNode->pRight = NULL;
                delete pDelete;
            } else if (pDelete->pLeft && pDelete->pRight) {
                // The node has two children.
                removeNodeWithTwoChildren(*pDelete);
            } else {
                // The node must only have one child.
                removeNodeWithOneChild(pDelete, pNode,
                    false /*fDeleteNodeLeftOfParent*/);
            }
        } else {
            // It's neither of the children of this node. Continue down the tree
            if (data < pNode->data) {
                this->removeChild(data, pNode->pLeft);
            } else {
                this->removeChild(data, pNode->pRight);
            }
        }
    }

    void removeNodeWithOneChild(Node* pDelete, Node* pParent,
        bool fDeleteNodeLeftOfParent) {

        // Update the parent of the delete node to point at the single child
        // of the deleted node.
        if (fDeleteNodeLeftOfParent) {
            if (pDelete->pLeft) {
                pParent->pLeft = pDelete->pLeft;
            } else {
                pParent->pLeft = pDelete->pRight;
            }
        } else {
            if (pDelete->pLeft) {
                pParent->pRight = pDelete->pLeft;
            } else {
                pParent->pRight = pDelete->pRight;
            }
        }

        // Delete the node
        delete pDelete;
    }

    void removeNodeWithTwoChildren(Node& pNode) {
        Node* pParent = &pNode;
        Node* pInOrderPredecessor = pNode.pLeft;

        while (pInOrderPredecessor->pRight) {
            pParent = pInOrderPredecessor;
            pInOrderPredecessor = pInOrderPredecessor->pRight;
        }

        // Copy the in-order predecessor's data into our node
        pNode.data = pInOrderPredecessor->data;

        // Delete the in-order predecessor (which we know has no children)
        pParent->pRight = NULL;
        delete pInOrderPredecessor;
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

