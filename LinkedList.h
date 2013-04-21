#include <iostream>
#include "LinkedListNode.h"


using namespace std;


template <class DataType>
class LinkedList {
public:
    LinkedList() :
        mpFirstNode(0) {}

    ~LinkedList() {
        LinkedListNode<DataType>* deleteNode = mpFirstNode;
        while (deleteNode != 0) {
            LinkedListNode<DataType>* nextNode = deleteNode->next();
            delete deleteNode;
            deleteNode = nextNode;
        }
    }

    const LinkedListNode<DataType>* const firstNode() const
        { return mpFirstNode; }

    LinkedListNode<DataType>* insertAfter(LinkedListNode<DataType>* pAfterNode,
        DataType& data) {
        if (pAfterNode == 0) {
            return 0;
        }

        LinkedListNode<DataType>* pInsertNode =
            new LinkedListNode<DataType>(data, pAfterNode->next());

        pAfterNode->setNext(pInsertNode);

        return pInsertNode;
    }

    LinkedListNode<DataType>* insertBeginning(DataType& data) {
        LinkedListNode<DataType>* pInsertNode =
            new LinkedListNode<DataType>(data, mpFirstNode);

        mpFirstNode = pInsertNode;

        return pInsertNode;
    }

    void removeAfter(LinkedListNode<DataType>* pAfterNode) {
        if (pAfterNode == 0) {
            return;
        }

        LinkedListNode<DataType>* pNextNode = pAfterNode->next();

        if (pNextNode == 0) {
            return;
        }

        LinkedListNode<DataType>* pNextNextNode = pNextNode->next();

        if (pNextNextNode != 0) {
            pAfterNode->setNext(pNextNextNode);
        } else {
            pAfterNode->setNext(0);
        }

        delete pNextNode;
    }

    void print() {
        if (mpFirstNode == 0) {
            cout << "NULL";
        } else {
            cout << mpFirstNode->data();

            LinkedListNode<DataType>* currentNode = mpFirstNode->next();
            while (currentNode != 0) {
                cout << " -> " << currentNode->data();
                currentNode = currentNode->next();
            }
        }

        cout << endl;
    }

private:
    LinkedListNode<DataType>* mpFirstNode;
};
