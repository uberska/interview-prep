#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>


using namespace std;


void printHeader() {
    cout << endl << "#####################################" << endl;
}


void printFound(bool found) {
    if (found) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}


int main(int /*argc*/, char** /*argv*/) {
    cout << endl << "Beginning STL Coding." << endl;

    string aString("A");
    string bString("B");
    string cString("C");
    string dString("D");

    //
    // Use a set
    //
    printHeader();

    set<string> aSet;

    aSet.insert(aString);
    aSet.insert(bString);
    aSet.insert(cString);
    aSet.insert(cString);

    cout << endl << "Set Contents:" << endl;
    for (set<string>::iterator iter = aSet.begin();
        iter != aSet.end();
        iter++) {
        cout << *iter << endl;
    }

    //
    // Use a map
    //
    printHeader();

    map<string, string> aMap;
    aMap[aString] = bString;
    aMap[cString] = dString;

    cout << endl << "Map Contents:" << endl;
    for (map<string, string>::iterator iter = aMap.begin();
        iter != aMap.end();
        iter++) {
        cout << iter->first << " = " << iter->second << endl;
    }

    //
    // Use a vector
    //
    printHeader();

    vector<string> aVector;
    aVector.push_back(aString);
    aVector.push_back(bString);

    cout << endl << "Vector Contents:" << endl;
    for (vector<string>::iterator iter = aVector.begin();
        iter != aVector.end();
        iter++) {
        cout << *iter << endl;
    }

    //
    // Use a list
    //
    printHeader();

    list<string> aList;

    aList.push_back(aString);
    aList.push_back(bString);
    aList.push_back(cString);

    cout << endl << "List Contents:" << endl;
    for (list<string>::iterator iter = aList.begin();
        iter != aList.end();
        iter++) {
        cout << *iter << endl;
    }

    //
    // Testing binary search
    //
    printHeader();

    sort(aVector.begin(), aVector.end());

    cout << endl << "Is A in the vector?" << endl;
    bool found = binary_search(aVector.begin(), aVector.end(), aString);
    printFound(found);

    cout << endl << "Is D in the vector?" << endl;
    found = binary_search(aVector.begin(), aVector.end(), dString);
    printFound(found);

    printHeader();

    cout << endl << "Done With STL Coding." << endl;
}

