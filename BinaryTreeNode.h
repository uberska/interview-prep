template <class DataType>
class BinaryTreeNode {
public:
    BinaryTreeNode(const DataType& data, BinaryTreeNode* pLeft = 0,
        BinaryTreeNode* pRight = 0) :
        mData(data),
        mpLeft(pLeft),
        mpRight(pRight) {}

    const DataType& getData() const { return mData; }

    void setData(const DataType& data) { mData = data; }

    BinaryTreeNode* getLeft() { return mpLeft; }
    const BinaryTreeNode* const getLeft() const { return mpLeft; }

    void setLeft(BinaryTreeNode* pLeft) { mpLeft = pLeft; }

    BinaryTreeNode* getRight() { return mpRight; }
    const BinaryTreeNode* const getRight() const { return mpRight; }

    void setRight(BinaryTreeNode* pRight) { mpRight = pRight; }
private:
    DataType mData;
    BinaryTreeNode<DataType>* mpLeft;
    BinaryTreeNode<DataType>* mpRight;
};

