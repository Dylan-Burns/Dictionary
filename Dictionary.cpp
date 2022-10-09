#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

class Dictionary {

private:
    map<string, vector<string>> keywordData;

public:

    void setMapData(map<string, vector<string>> data) {
        keywordData = data;
    }

    map<string, vector<string>> getMapData() {
        return keywordData;
    }


    void toString(string key, bool distinct, bool reverse, map<string, vector<string>> data) {


        for (map<string, vector<string>>::const_iterator itr{ data.begin() }; itr != data.end(); ++itr) {
            vector<string> tempVec = itr->second;

            for (auto& i : tempVec) {
                cout << key << " " << itr->first << " " << i << endl;
            }
            
        } // display all pairs
    }

    /*
    void printData(vector<string> data) {
        for (auto& i : data) {
            cout << i << endl;
        }
        cout << endl;
    }
    */
    //vector<string> sortVec(vector<string> partOSpeech) {

    //}

    void createMap(vector<string> partOfSpeech, vector<string> definition) {
        map <string, vector<string>> posDef;
        vector <string> definitionsCollection;
        vector <string> tempContainter;
        string temp;

        for (int i = 0; i < partOfSpeech.size(); i++) {

            if (posDef.empty()) {
                definitionsCollection.push_back(definition[i]);
                temp = partOfSpeech[i];
            }
            else
            {
                if (temp == partOfSpeech[i]) {
                    definitionsCollection.push_back(definition[i]);
                    temp = partOfSpeech[i];

                }
                else if (temp != partOfSpeech[i]) {
                    if (posDef.find(partOfSpeech[i]) == posDef.end()) {
                        tempContainter = definitionsCollection;
                        definitionsCollection.clear();
                        definitionsCollection.push_back(definition[i]);
                        temp = partOfSpeech[i];
                    }
                    else
                    {
                        definitionsCollection = tempContainter;
                        definitionsCollection.push_back(definition[i]);
                        temp = partOfSpeech[i];
                    }
                }
            }

            if (posDef.find(partOfSpeech[i]) == posDef.end()) {
                posDef.emplace(partOfSpeech[i], definitionsCollection);
            }
            else
            {
                posDef.erase(partOfSpeech[i]);
                posDef.emplace(partOfSpeech[i], definitionsCollection);
            }
        }
        setMapData(posDef);
    }

    void findAllDef(string line) {

        vector<string> definitions;
        vector<string> partOSpeech;
        string frontDelim = "> ";
        string rearDelim = "|";
        string endDelim = ".";
        string posRearDelim = " -";

        int startIndex;
        int endIndex;
        int speechStartIndex;
        int speechEndIndex;
        int executionCount = 0;

        while ((endIndex = line.find(endDelim) != string::npos)) {

            speechEndIndex = line.find(posRearDelim);
            if (executionCount > 0) {
                partOSpeech.push_back(line.substr(1, speechEndIndex - 1));
            }
            else {
                partOSpeech.push_back(line.substr(0, speechEndIndex));
            }
            startIndex = line.find(frontDelim);
            line.erase(0, startIndex + 1);

            endIndex = line.find(rearDelim);

            definitions.push_back(line.substr(0, endIndex));
            line.erase(0, endIndex);

            executionCount++;
        }

        createMap(partOSpeech, definitions);


    }

    string findKey(vector<string> data, string userIn) {
        string key;
        string delimiterKey = "|";

        int pos = 0;

        for (auto& i : data) {
            key = i;
            pos = i.find(delimiterKey);

            key = i.substr(0, pos);
            string removedKey = i.erase(0, pos + 1);

            if (key == userIn) {
                findAllDef(removedKey);
                return key;
            }
            
        }
    }

};

int main() {
    Dictionary dictionary;
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
        bool distinct = false;
        bool reverse = false;
        cout << "enter entry: ";
        cin >> userInput;
        if (userInput == "end") {
            end = true;
        }
        else {
            string keyword = dictionary.findKey(data, userInput);
            map<string, vector<string>> keywordData = dictionary.getMapData();
            dictionary.toString(keyword, distinct, reverse, keywordData);
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
