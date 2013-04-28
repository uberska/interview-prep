#include <cstdlib>
#include <ctime>
#include <iostream>


using namespace std;


// Swap values with a temporary variable
template <typename DataType>
void swap(DataType* one, DataType* two) {
    if (!one || !two) {
        return;
    }

    DataType temp(*one);
    *one = *two;
    *two = temp;
}


void printHeader() {
    cout << endl << "#####################################" << endl;
}


void populateArray(int* array, int size) {
    for (int index = 0; index < size; index++) {
        array[index] = rand() % 100;
    }
}


void printSubarray(const int* const array, int leftIndex, int rightIndex) {
    for (int index = leftIndex; index <= rightIndex; index++) {
        if (index != leftIndex) {
            cout << ", ";
        }
        cout << array[index];
    }
}


void printArray(const int* const array, int size) {
    printSubarray(array, 0, size - 1);
}


void bubbleSort(int* array, int size) {
    bool didSwap = true;
    while (didSwap == true) {
        didSwap = false;
        for (int index = 0; index < size - 1; index++) {
            if (array[index] > array[index + 1]) {
                int temp = array[index];
                array[index] = array[index + 1];
                array[index + 1] = temp;
                didSwap = true;
            }
        }
    }
}


int quickSortPartition(int* array, int leftIndex, int rightIndex,
    int pivotIndex) {

    int pivotValue = array[pivotIndex];

    swap(array[pivotIndex], array[rightIndex]);
    int storeIndex = leftIndex;
    for (int index = leftIndex; index < rightIndex; index++) {
        if (array[index] <= pivotValue) {
            swap(array[index], array[storeIndex]);
            storeIndex++;
        }
    }
    swap(array[storeIndex], array[rightIndex]);

    return storeIndex;
}


void quickSortSubarray(int* array, int leftIndex, int rightIndex) {
    if (leftIndex < rightIndex) {
        int pivotIndex = (leftIndex + rightIndex) / 2;

        int pivotNewIndex = quickSortPartition(array, leftIndex, rightIndex,
            pivotIndex);

        quickSortSubarray(array, leftIndex, pivotNewIndex - 1);

        quickSortSubarray(array, pivotNewIndex + 1, rightIndex);
    }
}


void quickSort(int* array, int size) {
    quickSortSubarray(array, 0, size - 1);
}


void mergeSubarrays(int* array, int* outputArray, int oneLeftIndex,
    int oneRightIndex, int twoLeftIndex, int twoRightIndex) {

    int oneIndex = oneLeftIndex;
    int twoIndex = twoLeftIndex;

    int storeIndex = 0;

    while (oneIndex <= oneRightIndex || twoIndex <= twoRightIndex) {
        if (oneIndex <= oneRightIndex &&
            (twoIndex > twoRightIndex || array[oneIndex] < array[twoIndex])) {
            outputArray[storeIndex] = array[oneIndex];
            oneIndex++;
        } else {
            outputArray[storeIndex] = array[twoIndex];
            twoIndex++;
        }
        storeIndex++;
    }
}


void copyArray(int* srcArray, int* destArray, int size) {
    for (int index = 0; index < size; index++) {
        destArray[index] = srcArray[index];
    }
}


void mergeSort(int* array, int size) {
    int* contents = array;
    int* buffer = new int[size];

    for (int width = 1; width < size; width = 2 * width) {
        for (int index = 0; index < size; index = index + 2 * width) {
            int twoLeftIndex = min(index + width, size - 1);
            int twoRightIndex = min((index + 2 * width) - 1, size - 1);
            mergeSubarrays(contents, buffer + index, index,  twoLeftIndex - 1,
                twoLeftIndex, twoRightIndex);
        }

        int* temp = contents;
        contents = buffer;
        buffer = temp;
    }

    if (array == buffer) {
        copyArray(contents, buffer, size);
        delete [] contents;
    } else {
        delete [] buffer;
    }
}


int main(int argc, char** argv) {
    cout << endl << "Beginning Sort Coding." << endl;

    srand(time(NULL));

    int arraySize = 20;
    int array[arraySize];

    //
    // Bubble Sort
    //
    printHeader();

    cout << endl << "Bubble Sort" << endl;

    populateArray(array, arraySize);

    cout << endl << "Initial Array Contents:" << endl;
    printArray(array, arraySize);
    cout << endl;

    bubbleSort(array, arraySize);

    cout << endl << "Sorted Contents:" << endl;
    printArray(array, arraySize);
    cout << endl;

    //
    // Quick Sort
    //
    printHeader();

    cout << endl << "Quick Sort" << endl;

    populateArray(array, arraySize);

    cout << endl << "Initial Array Contents:" << endl;
    printArray(array, arraySize);
    cout << endl;

    quickSort(array, arraySize);

    cout << endl << "Sorted Contents:" << endl;
    printArray(array, arraySize);
    cout << endl;

    //
    // Merge Sort
    //
    printHeader();

    cout << endl << "Merge Sort" << endl;

    populateArray(array, arraySize);

    cout << endl << "Initial Array Contents:" << endl;
    printArray(array, arraySize);
    cout << endl;

    mergeSort(array, arraySize);

    cout << endl << "Sorted Contents:" << endl;
    printArray(array, arraySize);
    cout << endl;

    //
    // We're done.
    //
    printHeader();

    cout << endl << "Done With Sort Coding." << endl;
}

