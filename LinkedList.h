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
            // If we're inserting after NULL, interpret that as "insert at the
            // begninning of the list"
            LinkedListNode<DataType>* pInsertNode =
                new LinkedListNode<DataType>(data, mpFirstNode);

            mpFirstNode = pInsertNode;

            return pInsertNode;
        } else {
            LinkedListNode<DataType>* pInsertNode =
                new LinkedListNode<DataType>(data, pAfterNode->next());

            pAfterNode->setNext(pInsertNode);

            return pInsertNode;
        }
    }

    LinkedListNode<DataType>* insertBeginning(DataType& data) {
        this->insertAfter(0, data);
    }

    void removeAfter(LinkedListNode<DataType>* pAfterNode) {
        if (pAfterNode == 0) {
            // If pAfterNode is 0, then delete the first item in the list
            if (mpFirstNode != 0) {
                LinkedListNode<DataType>* pDeleteNode = mpFirstNode;
                mpFirstNode = mpFirstNode->next();
                delete pDeleteNode;
            }
        } else {
            LinkedListNode<DataType>* pNextNode = pAfterNode->next();

            if (pNextNode != 0) {
                pAfterNode->setNext(pNextNode->next());
                delete pNextNode;
            }
        }
    }

    void removeBeginning() {
        this->removeAfter(0);
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
