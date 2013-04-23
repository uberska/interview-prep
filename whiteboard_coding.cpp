#include <iostream>
#include <set>
#include <string>


using namespace std;


void printHeader() {
    cout << endl << "#####################################" << endl;
}


// Swap values without a temporary variable if the operands support xor.
// This may not be faster than letting the compiler optimze out a temporary
// variable, but it's still something often used in interview questions.
template <typename DataType>
void xorSwap(DataType* one, DataType* two) {
    if (one != two) {
        *one ^= *two;
        *two ^= *one;
        *one ^= *two;
    }
}

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


void reverseString(char* aString) {
    // Find the last character
    char* endChar = aString;
    while(*(endChar + 1) != '\0') {
        endChar++;
    }

    // Reverse the string in place
    //while (endChar != aString && endChar != aString - 1) {
    while (endChar > aString) {
        //swap<char>(aString, endChar);
        xorSwap<char>(aString, endChar);
        aString++;
        endChar--;
    }
}


template <typename DataType>
void printArray(DataType* array, int arrayCount) {
    for (int index = 0; index < arrayCount; index++) {
        if (index != 0) {
            cout << ", ";
        }
        cout << array[index];
    }
}


void mergeSortedIntArrays(int intArray1[], int array1Count,
    int intArray2[], int array2Count, int outputArray[]) {

    int array1Index = 0;
    int array2Index = 0;
    int outputIndex = 0;

    while (array1Index != array1Count || array2Index != array2Count) {
        if (array1Index == array1Count) {
            // Nothing left in intArray1
            outputArray[outputIndex] = intArray2[array2Index];
            array2Index++;
        } else if (array2Index == array2Count) {
            // Nothing left in intArray2
            outputArray[outputIndex] = intArray1[array1Index];
            array1Index++;
        } else {
            if (intArray1[array1Index] < intArray2[array2Index]) {
                outputArray[outputIndex] = intArray1[array1Index];
                array1Index++;
            } else {
                outputArray[outputIndex] = intArray2[array2Index];
                array2Index++;
            }
        }

        outputIndex++;
    }
}


unsigned int myStrLen(char* aString) {
    unsigned int length = 0;

    if (aString) {
        while (*aString != '\0') {
            length++;
            aString++;
        }
    }

    return length;
}


void myStrCpy(char* destString, const char* srcString) {
    if (!destString || !srcString) {
        return;
    }

    while (*srcString != '\0') {
        *destString = *srcString;
        srcString++;
        destString++;
    }

    *destString = '\0';
}


string addSpacesToStr(const set<string>& words, const string& withoutSpaces) {
    for (int charIndex = 0; charIndex <= withoutSpaces.length(); charIndex++) {
        string wordOne = withoutSpaces.substr(0, charIndex);
        string wordTwo = withoutSpaces.substr(charIndex,
            withoutSpaces.length() - charIndex);

        if (words.find(wordOne) != words.end() &&
            words.find(wordTwo) != words.end()) {
            return wordOne + " " + wordTwo;
        }
    }

    return withoutSpaces;
}


int main(int argc, char** argv) {
    //
    // Let the user know we're starting.
    //
    cout << endl << "Beginning Whiteboard Coding." << endl;

    //
    // Reverse a string with an even number of characters
    //
    printHeader();
    cout << endl << "Reverse String (Even Chars)" << endl;

    char* evenString = "Backwards Day (Even)";

    cout << "Original: " << evenString << endl;

    reverseString(evenString);

    cout << "Reversed: " << evenString << endl;

    //
    // Reverse a string with an odd number of characters
    //
    printHeader();
    cout << endl << "Reverse String (Odd Chars)" << endl;

    char* oddString = "Backwards Day (Odd)";

    cout << "Original: " << oddString << endl;

    reverseString(oddString);

    cout << "Reversed: " << oddString << endl;

    //
    // Calculate the length of a null terminated char*
    //
    printHeader();
    cout << endl << "Implement strlen" << endl;

    char* lenString1 = "This is a test string.";
    cout << endl;
    cout << "String  : " << lenString1 << endl;
    cout << "Expected: 22" << endl;
    cout << "Actual  : " << myStrLen(lenString1) << endl;

    char* lenString2 = "";
    cout << endl;
    cout << "String  : <Empty String>" << endl;
    cout << "Expected: 0" << endl;
    cout << "Actual  : " << myStrLen(lenString2) << endl;

    char* lenString3 = 0;
    cout << endl;
    cout << "String  : NULL" << endl;
    cout << "Expected: 0" << endl;
    cout << "Actual  : " << myStrLen(lenString3) << endl;

    //
    // Implement strcpy
    //
    printHeader();
    cout << endl << "Implement strcpy" << endl;

    cout << endl;
    char* srcString1 = "This is a test string.";
    cout << "Source String: " << srcString1 << endl;
    char destString1[myStrLen(srcString1) + 1];
    myStrCpy(destString1, srcString1);
    cout << "Copied String: " << destString1 << endl;

    cout << endl;
    char* srcString2 = "";
    cout << "Source String: <Empty String>" << endl;
    char destString2[myStrLen(srcString2) + 1];
    myStrCpy(destString2, srcString2);
    cout << "Copied String: " << destString2 << endl;

    //
    // Merge two sorted int arrays into one sorted int array
    //
    printHeader();
    cout << endl << "Merge Sorted Int Arrays" << endl;

    int intArray1[] = {1, 3, 6, 8, 10};
    int array1Count = sizeof(intArray1) / sizeof(intArray1[0]);
    cout << "Array1  : ";
    printArray(intArray1, array1Count);
    cout << endl;

    int intArray2[] = {2, 3, 5, 9, 9};
    int array2Count = sizeof(intArray2) / sizeof(intArray2[0]);
    cout << "Array2  : ";
    printArray(intArray2, array2Count);
    cout << endl;

    int outputArray[array1Count + array2Count];

    cout << "Expected: 1, 2, 3, 3, 5, 6, 8, 9, 9, 10" << endl;

    mergeSortedIntArrays(intArray1, array1Count, intArray2, array2Count,
        outputArray);
    cout << "Actual  : ";
    printArray(outputArray, array1Count + array2Count);

    cout << endl;

    //
    // Split a string of words without spaces into a string of words with spaces
    //
    printHeader();
    cout << endl << "Adding Spaces To String Of Words" << endl;

    set<string> wordSet;
    wordSet.insert("pea");
    wordSet.insert("nut");
    wordSet.insert("peanut");
    wordSet.insert("but");
    wordSet.insert("butter");
    wordSet.insert("awesome");

    string withoutSpacesStr("peanutbutter");

    cout << endl;
    cout << "Words Without Spaces: " << withoutSpacesStr << endl;
    string withSpacesStr = addSpacesToStr(wordSet, withoutSpacesStr);
    cout << "Words With Spaces   : " << withSpacesStr << endl;

    //
    // Let the user know we're done.
    //
    printHeader();
    cout << endl << "Done With Whiteboard Coding." << endl;
}

