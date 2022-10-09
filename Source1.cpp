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
    vector <string> partOSpeech;
    string frontDelim = "> ";
    string rearDelim = ".|";
    string endDelim = ".";
    string posFrontDelim = "|";
    string posRearDelim = " -";

    int startIndex;
    int endIndex;
    int speechStartIndex;
    int speechEndIndex;

    while ((endIndex = line.find(endDelim) != string::npos)) {
        startIndex = line.find(frontDelim);
        endIndex = line.find(rearDelim);
        speechStartIndex = line.find(posFrontDelim);
        speechEndIndex = line.find(posRearDelim);

        cout << "startIndex: " << startIndex << endl << "EndIndex: " << endIndex << endl;

        partOSpeech.push_back(line.substr(speechStartIndex +1, speechEndIndex));
        definitions.push_back(line.substr(startIndex + 1, endIndex - startIndex));
        line.erase(startIndex + 1, endIndex);
        cout << line << endl;
        
        
    }
    
    printData(partOSpeech);
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
