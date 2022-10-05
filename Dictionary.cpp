#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void printData(vector<string> data) {
    for (auto& i : data) {
        cout << i << endl << endl;
    }
}

void findAllDef(string line) {
    vector <string> definitions;
    string frontDelim = "> ";
    string rearDelim = ".";

    int startIndex;
    int endIndex;
    
    while ((endIndex = line.find(rearDelim) != string::npos)) {
        startIndex = line.find(frontDelim);
        endIndex = line.find(rearDelim);
        if(startIndex < endIndex){
            definitions.push_back(line.substr(startIndex + 1, endIndex - startIndex));
            line.erase(startIndex, endIndex);
        }
        else
            break;
        
    }
    
    printData(definitions);
}

void findPos(vector<string> data, string userIn) {
    string key;
    string posWord;
    string definition;
    string delimiterKey = "|";
    string delimPos = "> ";
    string delimDef = ".";

    int pos = 0;
    int secondPos = 0;
    int thirdPos = 0;

    for (auto& i : data) {
        key = i;
        pos = i.find(delimiterKey);
        
        key = i.substr(0, pos);
        string removedKey = i.erase(0, pos);

        if (key == userIn) {
            cout << key << endl << endl;
            cout << removedKey << endl;
            findAllDef(removedKey);
        }
    }
}




int main()
{
    vector<string> data;
    int count = 1;
    bool exit = false;
    string userInput = "";
    fstream ioFile;
    bool end = false;

    ioFile.open("Data.CS.SFSU.txt", ios::in);

    if (ioFile.is_open()) {
        string temp;
        while (getline(ioFile, temp)) {
            data.push_back(temp);
        }
    }

    cout << "! Loading Complete...\n" << endl << "===== DICTIONARY 340 JAVA =====" <<
        endl << "----- Keywords: " << endl << "----- Definitions: " << endl;

    while (!end) {
        cout << "enter entry: ";
        cin >> userInput;
        if (userInput == "end") {
            end = true;
        }
        else {
            findPos(data, userInput);
        }
    }
    return 0;
}


///parsing function which looks for keyword, pos, definition
///itterate through vector ds to find keyword, parse keyword and definition
///placing into map

///map to hold pos and defin


///output parsed data

///distinct functionality, parse user input for distinct keyword
///use distinct unordered map for unique output of definitions

///reverse function, reverse the vector 



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
