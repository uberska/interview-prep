#include <iostream>


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



int main(int argc, char** argv) {
    cout << endl << "Beginning Whiteboard Coding." << endl;

    printHeader();
    cout << endl << "Reverse String (Even Chars)" << endl;
    char* evenString = "Backwards Day (Even)";
    cout << "Original: " << evenString << endl;
    reverseString(evenString);
    cout << "Reversed: " << evenString << endl;

    printHeader();
    cout << endl << "Reverse String (Odd Chars)" << endl;
    char* oddString = "Backwards Day (Odd)";
    cout << "Original: " << oddString << endl;
    reverseString(oddString);
    cout << "Reversed: " << oddString << endl;

    printHeader();
    cout << endl << "Done With Whiteboard Coding." << endl;
}

