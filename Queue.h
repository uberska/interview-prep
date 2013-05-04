#include <exception>
#include <iostream>
#include "LinkedList.h"


using namespace std;


class QueueAccessException : public exception {
    virtual const char* what() const throw() {
        return "You can not access elements of an empty Queue.";
    }
};


template <class DataType>
class Queue {
public:
    Queue() {}

    void enqueue(const DataType& data) {
        list.insertEnd(data);
    }

    void dequeue() {
        list.removeBeginning();
    }

    DataType front() {
        if (isEmpty()) {
            throw QueueAccessException();
        }

        return list.firstNode()->data();
    }

    bool isEmpty() const {
        return list.firstNode() == NULL;
    }

private:
    LinkedList<DataType> list;
};

