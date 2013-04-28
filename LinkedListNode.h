#pragma once

template <class DataType>
class LinkedListNode {
public:
    LinkedListNode(const DataType& data, LinkedListNode<DataType>* pNext = 0) :
        mData(data),
        mpNext(pNext) {}

    const DataType& data() const { return mData; }

    LinkedListNode<DataType>* next() { return mpNext; }
    const LinkedListNode<DataType>* const next() const { return mpNext; }

    void setNext(LinkedListNode<DataType>* newNext) {
        mpNext = newNext;
    }

private:
    DataType mData;

    LinkedListNode<DataType>* mpNext;
};

