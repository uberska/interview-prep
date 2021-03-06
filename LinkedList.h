#pragma once

#include <iostream>
#include "LinkedListNode.h"


using namespace std;


template <class DataType>
class LinkedList {
public:
    LinkedList() :
        mpFirstNode(0),
        mpLastNode(0) {}

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

    LinkedListNode<DataType>* firstNode() { return mpFirstNode; }

    LinkedListNode<DataType>* insertAfter(LinkedListNode<DataType>* pAfterNode,
        const DataType& data) {

        if (pAfterNode == 0) {
            // If we're inserting after NULL, interpret that as "insert at the
            // begninning of the list"
            LinkedListNode<DataType>* pInsertNode =
                new LinkedListNode<DataType>(data, mpFirstNode);

            if (mpFirstNode == 0) {
                mpLastNode = pInsertNode;
            }

            mpFirstNode = pInsertNode;

            return pInsertNode;
        } else {
            LinkedListNode<DataType>* pInsertNode =
                new LinkedListNode<DataType>(data, pAfterNode->next());

            pAfterNode->setNext(pInsertNode);

            if (pInsertNode->next() == 0) {
                mpLastNode = pInsertNode;
            }

            return pInsertNode;
        }
    }

    LinkedListNode<DataType>* insertEnd(const DataType& data) {
        return this->insertAfter(mpLastNode, data);
    }

    LinkedListNode<DataType>* insertBeginning(const DataType& data) {
        return this->insertAfter(0, data);
    }

    void removeAfter(LinkedListNode<DataType>* pAfterNode) {
        if (pAfterNode == 0) {
            // If pAfterNode is 0, then delete the first item in the list
            if (mpFirstNode != 0) {
                LinkedListNode<DataType>* pDeleteNode = mpFirstNode;
                mpFirstNode = mpFirstNode->next();
                delete pDeleteNode;

                if (mpFirstNode == 0) {
                    mpLastNode = 0;
                }
            }
        } else {
            LinkedListNode<DataType>* pNextNode = pAfterNode->next();

            if (pNextNode != 0) {
                if (pNextNode->next() == 0) {
                    mpLastNode = pAfterNode;
                }
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
    LinkedListNode<DataType>* mpLastNode;
};
