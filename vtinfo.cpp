#include <cctype>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>


using namespace std;


typedef map<char, int> CharCountMap;


//
// Populate the given CharCountMap with the number of alphanumeric characters
// in aString.
//
void populateCharCountMap(CharCountMap& characterMap, const string& aString) {
    for (unsigned int index = 0; index < aString.length(); index++) {
        char aChar = tolower(aString[index]);

        if (!isalnum(aChar)) {
            continue;
        }

        characterMap[aChar]++;
    }
}


//
// Return a boolean specifying if the strings one and two are anagrams of each
// other.
//
bool isAnagram(const string& one, const string& two) {
    CharCountMap oneMap;
    populateCharCountMap(oneMap, one);

    CharCountMap twoMap;
    populateCharCountMap(twoMap, two);

    return oneMap.size() != 0 && oneMap == twoMap;
}


//
// Return the next index of an alpha numeric character in aString. Start
// searching at startIndex. If we reach the end of the string without finding
// an alphanumeric character, return -1.
//
int getNextAlphaNumericIndex(const string& aString, int startIndex) {
    for (unsigned int index = startIndex; index < aString.length(); index++) {
        if (isalnum(aString[index])) {
            return index;
        }
    }

    return -1;
}


//
// Loop backwards searching for an alphanumeric character. Start searching at
// startIndex. If we reach the beginning of the string without finding an
// alphanumeric character, return -1.
//
int getPreviousAlphaNumericIndex(const string& aString, int startIndex) {
    for (int index = startIndex; index >= 0; index--) {
        if (isalnum(aString[index])) {
            return index;
        }
    }

    return -1;
}


//
// Return a boolean specifying whether aString is a palindrome.
//
bool isPalindrome(const string& aString) {
    int startIndex = getNextAlphaNumericIndex(aString, 0);
    int endIndex = getPreviousAlphaNumericIndex(aString, aString.length() - 1);

    // Check if we didn't find any alphanumeric characters in the entire string.
    if (startIndex == -1) {
        return false;
    }

    while (startIndex < endIndex) {
        if (tolower(aString[startIndex]) != tolower(aString[endIndex])) {
            return false;
        }

        startIndex = getNextAlphaNumericIndex(aString, startIndex + 1);
        endIndex = getPreviousAlphaNumericIndex(aString, endIndex - 1);
    }

    return true;
}


//
// Output whether two strings passed in are:
//
// 1. both palindromes
// 2. one word is a palindrome but not the other
// 3. the two words are anagrams for one another
// 4. the two words are both palindrome and anagram for one another
// 5. neither word is a palindrome or an anagram for each other.
//
void questionTwo(const string& one, const string& two) {
    bool fOneIsPalindrome = isPalindrome(one);
    bool fTwoIsPalindrome = isPalindrome(two);

    bool fIsAnagram = isAnagram(one, two);

    cout << "\n\"" << one << "\" \"" << two << "\"";


    if (fIsAnagram && fOneIsPalindrome && fTwoIsPalindrome) {
        cout << "\nThe two words are both palindrome and anagram of one"
            " another.\n";
    } else if (fOneIsPalindrome && fTwoIsPalindrome) {
        cout << "\nBoth are palindromes.\n";
    } else if (fIsAnagram) {
        cout << "\nThe two words are anagrams for one another.\n";
    } else if (fOneIsPalindrome ^ fTwoIsPalindrome) {
        cout << "\nOne word is a palindrome but not the other.\n";
    } else if (!fOneIsPalindrome && !fTwoIsPalindrome && !fIsAnagram) {
        cout << "\nNeither word is a palindrome or an anagram of each other.\n";
    }
}


//
// Print a human readable representation of a boolean.
//
void printBool(bool fBool) {
    if (fBool) {
        cout << "Yes";
    } else {
        cout << "No";
    }
}


//
// Print whether aString is a palindrome.
//
void printPalindromeStatus(const string& aString) {
    cout << "\n\"" << aString << "\" Is Palindrome? - ";
    printBool(isPalindrome(aString));
}


//
// Print whether one and two are anagrams of each other.
//
void printAnagramStatus(const string& one, const string& two) {
    cout << "\n\"" << one << "\" \"" << two << "\" Are Anagrams? - ";
    printBool(isAnagram(one, two));
}


int main(int argc, char** argv) {
    if (argc == 3) {
        // If the user specified two strings, answer the question posed about
        // the two strings.

        string one(argv[1]);
        string two(argv[2]);

        questionTwo(one, two);
    } else {
        // If the user didn't specify two strings, perform some tests to make
        // sure the code is working properly.

        printPalindromeStatus(" a .!&@#$ ");
        printPalindromeStatus("aA");
        printPalindromeStatus("ab");
        printPalindromeStatus("abba");
        printPalindromeStatus("abc");
        printPalindromeStatus("Race car");
        printPalindromeStatus("Elite Tile");
        printPalindromeStatus("1234");
        printPalindromeStatus("1234321");
        printPalindromeStatus("12344321");
        printPalindromeStatus("ab121ba");
        printPalindromeStatus("");
        printPalindromeStatus("  ");

        cout << "\n\n";

        printAnagramStatus("Eleven plus two", "Twelve plus one");
        printAnagramStatus("meat", "team");
        printAnagramStatus("Eleven plus two...", "Twelve plus    one!");
        printAnagramStatus("abcdefg", "gfedcba");
        printAnagramStatus("abcd", "CABD");
        printAnagramStatus("a", "aa");
        printAnagramStatus("Un", "Related");
        printAnagramStatus("a1b2", "12AB");
        printAnagramStatus("", "");

        cout << "\n\n";

        questionTwo("abcddcba", "dcbaabcd");
        questionTwo("un", "related");
        questionTwo("abcddcba", "notAPalindrome");
        questionTwo("race car", "elite tile");
        questionTwo("Eleven plus two", "Twelve plus one");
    }

    return EXIT_SUCCESS;
}

