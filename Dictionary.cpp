#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

class Dictionary {

private:
    bool validKeyword = true;
    map<string, vector<string>> keywordData;
    vector<string> userParse;

public:

    void setValidKeyword(bool input) {
        validKeyword = input;
    }
    bool getValidKeyword() {
        return validKeyword;
    }
    void setMapData(map<string, vector<string>> data) {
        keywordData = data;
    }
    map<string, vector<string>> getMapData() {
        return keywordData;
    }
    
    void setUserParse(string const &input) {
        
        vector<string> userParsed;
        stringstream in(input);
        string data;
        size_t position = 0;
        while (getline(in, data, ' ')) {
            userParsed.push_back(data);
        }
      

        userParse = userParsed;
    }
    
    vector<string> getUserParse() {
        return userParse;
    }



    //print + userValidation function
    void toString(string in, map<string, vector<string>> data) {
        
        vector<string> userData = getUserParse();

        string keyword, partOfSpeech;
        bool distinct, reverse, ifValid, validPos;

        vector<string> partOfSpeechVec = { "noun", "pronoun", "adjective", "determiner", "verb", "adverb", "preposition", "conjunction", "interjection" };

        ifValid = getValidKeyword();

        validPos = false;
        distinct = false;
        reverse = false;

        // if our input is less than 5 slots and the keyword is valid
        if (userData.size() < 5 && ifValid == true) {
            
            //if the user data is greater than 0 get the keyword if only valid keyword, then print map
            if (userData.size() > 0) {
                keyword = userData[0];
                
                if (userData.size() == 1) {
                    for (map<string, vector<string>>::const_iterator itrer{ data.begin() }; itrer != data.end(); ++itrer) {
                        vector<string> temp = itrer->second;
                        for (auto& i : temp) {
                            cout << keyword << " [" << itrer->first << "]  : " << i << endl;
                        }
                    } // display all pairs
                }
            }

            //if greater than 2 we know keyword is always in 1st position, second postion can contain distinct, however we can have that as a valid POS
            if (userData.size() >= 2) {
                partOfSpeech = userData[1];

                //check the valid inputs for pos and distinct, set flag for distinct if found in 2nd position.
                for (int i = 0; i < partOfSpeechVec.size(); i++) {
                    if (partOfSpeechVec[i] == partOfSpeech || partOfSpeech == "distinct") {
                        validPos = true;
                        if (partOfSpeech == "distinct") {
                            distinct = true;
                        }
                        else {
                            distinct = false;
                        }
                    }
                }

                if (validPos == true && distinct == false && reverse == false){
                    
                    for (auto itr = data.find(userData[1]); itr != data.end(); itr++) {
                        if (itr->first == userData[1]) {
                            vector<string> temp = itr->second;
                            cout << "FOUND INFO: Key | POS |" << endl;
                            for (auto& i : temp) {
                                    
                                cout << keyword << " [" << itr->first << "]  : " << i << endl;

                            }
                        }
                    }
                    cout << "status of distinct : " << distinct << endl;
                }
                
                else if (validPos == true && distinct) {

                    for (map<string, vector<string>>::const_iterator itrerer{ data.begin() }; itrerer != data.end(); ++itrerer) {
                        map<string, string> keepTrack;
                        
                        vector<string> temp = itrerer->second;
                        for (int i = 0; i < temp.size(); i++) {
                            string tempString = temp[i];
                            //to lower in order to make sure an capitalization conflicts on the definition are parsed out
                            
                            for_each (tempString.begin(), tempString.end(), [](char& c) {
                                c = tolower(c);
                            });

                            keepTrack.emplace(tempString, itrerer->first);
                        }
                       
                        for (map<string, string>::const_iterator itrererer{ keepTrack.begin() }; itrererer != keepTrack.end(); ++itrererer) {
                            cout << keyword << " [" << itrererer->second << "]  :" << itrererer->first << endl;
                        }
                    }
                }
                cout << endl;
            }
        }

    }

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

    void findKey(vector<string> data, string userIn) {
        vector<string> parsed;
        setValidKeyword(true);
        string key;
        string delimiterKey = "|";
        bool keyFound = false;
        int pos = 0;
      
        setUserParse(userIn);
        parsed = getUserParse();
        
        for (auto& i : data) {
            key = i;
            pos = i.find(delimiterKey);

            key = i.substr(0, pos);
            string removedKey = i.erase(0, pos + 1);

            if (key == parsed[0]) {
                keyFound = true;
                findAllDef(removedKey);
                break;
            }

        }
        if (!keyFound) {
            cout << "Sorry there is no valid keyword entered, to be considered" << endl;
            setValidKeyword(false);
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
        
        
        cout << "enter entry: ";
        getline(cin, userInput);

        //convert user input to lower
        for_each(userInput.begin(), userInput.end(), [](char& c) {
            c = tolower(c);
        });


        if (userInput == "end") {
            end = true;
        }
        else {

            dictionary.findKey(data, userInput);
            map<string, vector<string>> keywordData = dictionary.getMapData();
            dictionary.toString(userInput, keywordData);
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
