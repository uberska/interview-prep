#include <iostream>


using namespace std;


void printHeader() {
    cout << endl << "#####################################" << endl;
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
        char temp = *aString;
        *aString = *endChar;
        *endChar = temp;
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

