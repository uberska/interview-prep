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
        // Handle the root case
        if (mpRootNode && data == mpRootNode->getData()) {
            if (!mpRootNode->getLeft() && !mpRootNode->getRight()) {
                // The root node doesn't have any children. Just delete it.
                delete mpRootNode;
                mpRootNode = 0;
            } else if (mpRootNode->getLeft() && mpRootNode->getRight()) {
                // The root node has two children.
                removeNodeWithTwoChildren(*mpRootNode);
            } else {
                // The root node has one child.

                BinaryTreeNode<DataType>* pDelete = mpRootNode;

                // Get our new root node.
                if (mpRootNode->getLeft()) {
                    // The root node has only one child (the left node).
                    mpRootNode = mpRootNode->getLeft();
                } else {
                    // The root node has only one child (the right node).
                    mpRootNode = mpRootNode->getRight();
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

private:
    typedef void (BinaryTree::*ProcessTreeNodeCallback)(
        BinaryTreeNode<DataType>* pNode, const bool&, bool&);

    void insert(const DataType& data, BinaryTreeNode<DataType>& node) {
        if (data == node.getData()) {
            // We don't allow duplicates.
        } else if (data < node.getData()) {
            if (node.getLeft() == 0) {
                node.setLeft(new BinaryTreeNode<DataType>(data));
            } else {
                this->insert(data, *node.getLeft());
            }
        } else {
            if (node.getRight() == 0) {
                node.setRight(new BinaryTreeNode<DataType>(data));
            } else {
                this->insert(data, *node.getRight());
            }
        }
    }

    // Check the children of pNode to see if they match data. If so, delete
    // them. We operate at this level because there are instances where we need
    // to update the parent of the deleted node, but nodes don't have back
    // pointers to their parents.
    void removeChild(const DataType& data,
        BinaryTreeNode<DataType>* pNode) {

        if (!pNode) {
            return;
        }

        if (pNode->getLeft() && data == pNode->getLeft()->getData()) {
            // Our left child is the node to delete. Delete it.

            BinaryTreeNode<DataType>* pDelete = pNode->getLeft();

            if (!pDelete->getLeft() && !pDelete->getRight()) {
                // It doesn't have any children. Delete the node and update
                // our left pointer.
                pNode->setLeft(0);
                delete pDelete;
            } else if (pDelete->getLeft() && pDelete->getRight()) {
                // The node has two children.
                removeNodeWithTwoChildren(*pDelete);
            } else {
                // The node must only have one child.
                removeNodeWithOneChild(pDelete, pNode,
                    true /*fDeleteNodeLeftOfParent*/);
            }
        } else if (pNode->getRight() && data == pNode->getRight()->getData()) {
            // Our right child is the node to delete. Delete it.

            BinaryTreeNode<DataType>* pDelete = pNode->getRight();

            if (!pDelete->getLeft() && !pDelete->getRight()) {
                // It doesn't have any children. Delete the node and update
                // our left pointer.
                pNode->setRight(0);
                delete pDelete;
            } else if (pDelete->getLeft() && pDelete->getRight()) {
                // The node has two children.
                removeNodeWithTwoChildren(*pDelete);
            } else {
                // The node must only have one child.
                removeNodeWithOneChild(pDelete, pNode,
                    false /*fDeleteNodeLeftOfParent*/);
            }
        } else {
            // It's neither of the children of this node. Continue down the tree
            if (data < pNode->getData()) {
                this->removeChild(data, pNode->getLeft());
            } else {
                this->removeChild(data, pNode->getRight());
            }
        }
    }

    void removeNodeWithOneChild(BinaryTreeNode<DataType>* pDelete,
        BinaryTreeNode<DataType>* pParent, bool fDeleteNodeLeftOfParent) {

        // Update the parent of the delete node to point at the single child
        // of the deleted node.
        if (fDeleteNodeLeftOfParent) {
            if (pDelete->getLeft()) {
                pParent->setLeft(pDelete->getLeft());
            } else {
                pParent->setLeft(pDelete->getRight());
            }
        } else {
            if (pDelete->getLeft()) {
                pParent->setRight(pDelete->getLeft());
            } else {
                pParent->setRight(pDelete->getRight());
            }
        }

        // Delete the node
        delete pDelete;
    }

    void removeNodeWithTwoChildren(BinaryTreeNode<DataType>& pNode) {
        BinaryTreeNode<DataType>* pParent = &pNode;
        BinaryTreeNode<DataType>* pInOrderPredecessor = pNode.getLeft();

        while (pInOrderPredecessor->getRight()) {
            pParent = pInOrderPredecessor;
            pInOrderPredecessor = pInOrderPredecessor->getRight();
        }

        // Copy the in-order predecessor's data into our node
        pNode.setData(pInOrderPredecessor->getData());

        // Delete the in-order predecessor (which we know has no children)
        pParent->setRight(0);
        delete pInOrderPredecessor;
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

