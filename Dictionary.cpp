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
    //setters and getters
    void setValidKeyword(bool input) {
        validKeyword = input;
    }
    void setUserParse(string const& input) {

        vector<string> userParsed;
        stringstream in(input);
        string data;
        size_t position = 0;
        while (getline(in, data, ' ')) {
            userParsed.push_back(data);
        }


        userParse = userParsed;
    }
    void setMapData(map<string, vector<string>> data) {
        keywordData = data;
    }
    bool getValidKeyword() {
        return validKeyword;
    }
    map<string, vector<string>> getMapData() {
        return keywordData;
    }
    vector<string> getUserParse() {
        return userParse;
    }

    void validateInput(vector<string> line) {
        vector<string> validOptions = { "noun", "pronoun", "adjective", "determiner", "verb", "adverb", "preposition", "conjunction", "interjection", "distinct", "reverse"};
        bool second = false, third = false, fourth = false;

        if (line.size() > 1 && line.size() < 5) {
            for (int i = 1; i < line.size(); i++) {
                for (int j = 0; j < validOptions.size(); j++) {
                    if (line[i] == validOptions[j]) {

                        if (i == 1) {

                            second = false;
                        }
                        else if (i == 2) {

                            third = false;

                        }
                        else if (i == 3) {

                            fourth = false;
                        }
                        break;
                    }
                    else {

                        if (i == 1) {

                            second = true;
                        }
                        else if (i == 2) {

                            third = true;

                        }
                        else if (i == 3) {

                            fourth = true;
                        }
                    }
                }
            }

        
            if (second == true) {
                cout << "     <The entered 2nd parameter '" << line[1] << "' is NOT a part of speech." << endl;
                cout << "     <The entered 2nd parameter '" << line[1] << "' is NOT 'distinct'." << endl;
                cout << "     <The entered 2nd parameter '" << line[1] << "' is NOT 'reverse'." << endl;
                cout << "     <The entered 2nd parameter '" << line[1] << "' was disregarded." << endl;
                cout << "     <The 2nd parameter should be a part of speech or 'distinct' or 'reverse'.>" << endl;
                cout << "    |" << endl;
            }

            if (third == true) {
                cout << "     <The entered 3rd parameter '" << line[2] << "' is NOT 'distinct'." << endl;
                cout << "     <The entered 3rd parameter '" << line[2] << "' is NOT 'reverse'." << endl;
                cout << "     <The entered 3rd parameter '" << line[2] << "' was disregarded." << endl;
                cout << "     <The 3rd parameter should be 'distinct' or 'reverse'.>" << endl;
                cout << "    |" << endl;
            }

            if (fourth == true) {
                cout << "     <The entered 4th parameter '" << line[3] << "' is NOT 'reverse'." << endl;
                cout << "     <The entered 4th parameter '" << line[3] << "' was disregarded." << endl;
                cout << "     <The 4th parameter should be 'reverse'.>" << endl;
                cout << "    |" << endl;
            }
            
        }
        else {
            cout << "     PARAMETER HOW-TO, please enter:" << endl;
            cout << "     1. A search key - then 2. An optional part of speech - then" << endl
                << "     3. An optional 'distinct' -then 4. An optional 'reverse'" << endl;
        }

    }

    //print + userValidation function
    void toString(string in, map<string, vector<string>> data) {
        
        vector<string> userData = getUserParse();
        validateInput(userData);
        
        string keyword, partOfSpeech;
        bool distinct, reverse, ifValid, validPos, flagNotPOSDistinct, rFoundInPos, invalidPOS;

        vector<string> partOfSpeechVec = { "noun", "pronoun", "adjective", "determiner", "verb", "adverb", "preposition", "conjunction", "interjection" };

        ifValid = getValidKeyword();

        validPos = false;
        distinct = false;
        reverse = false;
        flagNotPOSDistinct = false;
        rFoundInPos = false;

        // if our input is less than 5 slots and the keyword is valid
        if (userData.size() < 5 && ifValid == true) {
            
            //if the user data is greater than 0 get the keyword if only valid keyword, then print map
            if (userData.size() > 0) {
                keyword = userData[0];
                
                if (userData.size() == 1) {
                    for (map<string, vector<string>>::const_iterator itr{ data.begin() }; itr != data.end(); ++itr) {
                        vector<string> temp = itr->second;
                        for (auto& i : temp) {
                            cout << "     " << keyword << " [" << itr->first << "]  : " << i << endl;
                        }
                    } 
                }
                
            }

            //if greater than 2 we know keyword is always in 1st position, second postion can contain distinct, however we can have that as a valid POS
            if (userData.size() >= 2) {
                partOfSpeech = userData[1];

                if (userData.size() > 2 && userData.size() < 5) {
                    if (userData.size() == 3) {
                        if (userData[2] == "reverse") {
                            reverse = true;
                        }
                        else reverse = false;
                        
                        if (userData[2] == "distinct") {
                            distinct = true;
                            flagNotPOSDistinct = true;
                        }
                        else distinct = false;
                    }
                    else if (userData.size() == 4) {

                        if (userData[2] == "distinct") {
                            distinct = true;
                            flagNotPOSDistinct = true;
                        }
                        else distinct = false;

                        if (userData[2] == "reverse") {
                            reverse = true;
                        }else if (userData[3] == "reverse"){
                            reverse = true;
                        }
                    }
                }

                //check the valid inputs for pos and distinct, set flag for distinct if found in 2nd position.
                for (int i = 0; i < partOfSpeechVec.size(); i++) {
                    if (partOfSpeechVec[i] == partOfSpeech || partOfSpeech == "distinct" || partOfSpeech == "reverse") {
                        validPos = true;
                        if (userData.size() == 2) {

                            if (partOfSpeech == "reverse") {
                                reverse = true;
                                rFoundInPos = true;
                            }
                            else
                                reverse = false;


                            if (partOfSpeech == "distinct") {
                                distinct = true;
                            }
                            else
                                distinct = false;
                        }
                    }
                    else
                        invalidPOS = true;
                }


                if (invalidPOS) {
                    for (map<string, vector<string>>::const_iterator itr{ data.begin() }; itr != data.end(); ++itr) {
                        vector<string> temp = itr->second;
                        for (auto& i : temp) {
                            cout << "     " << keyword << " [" << itr->first << "]  : " << i << endl;
                        }
                    }
                }


                ///handling POS + keyword for 2 + reverse
                if (validPos == true && distinct == false){
                    if (reverse == false) {
                        for (auto itr = data.find(userData[1]); itr != data.end(); itr++) {

                            if (itr->first == userData[1]) {
                                vector<string> temp = itr->second;

                                for (auto& i : temp) {
                                    cout << "     " << keyword << " [" << itr->first << "]  : " << i << endl;
                                }
                            }
                        }
                    }
                    else {
                        if (rFoundInPos) {
                            for (map<string, vector<string>>::reverse_iterator itr{ data.rbegin() }; itr != data.rend(); ++itr) {
                                vector<string> temp = itr->second;
                                for (auto& i : temp) {
                                    cout << "     " << keyword << " [" << itr->first << "]  : " << i << endl;
                                }
                            }
                        }
                        else {
                            for (auto itr = data.find(userData[1]); itr != data.end(); itr++) {

                                if (itr->first == userData[1]) {
                                    vector<string> temp = itr->second;

                                    for (auto i = temp.rbegin(); i != temp.rend(); i++) {
                                        cout << "     " << keyword << " [" << itr->first << "]  : " << *i << endl;
                                    }
                                }
                            }
                        }
                    }
                        
                }
                
                ///handling distinct + keyword via a map + reversed
                else if (validPos == true && distinct) {

                    for (map<string, vector<string>>::const_iterator itr{ data.begin() }; itr != data.end(); ++itr) {
                        map<string, string> keepTrack;
                        
                        vector<string> temp = itr->second;
                        for (int i = 0; i < temp.size(); i++) {
                            string tempString = temp[i];
                            //to lower in order to make sure an capitalization conflicts on the definition are parsed out
                            
                            for_each (tempString.begin(), tempString.end(), [](char& c) {
                                c = tolower(c);
                            });

                            keepTrack.emplace(tempString, itr->first);
                        }
                       
                        if (reverse == false) {
                            
                            if (flagNotPOSDistinct) {
                                for (map<string, string>::const_iterator itr2{ keepTrack.begin() }; itr2 != keepTrack.end(); ++itr2) {
                                    if (itr2->second == partOfSpeech) {
                                        cout << "     " << keyword << " [" << itr2->second << "]  :" << itr2->first << endl;
                                    }
                                }
                               
                            }
                            else {
                                for (map<string, string>::const_iterator itr2{ keepTrack.begin() }; itr2 != keepTrack.end(); ++itr2) {
                                    cout << "     " << keyword << " [" << itr2->second << "]  :" << itr2->first << endl;
                                }
                            }
                        }
                        if (reverse == true) {
                            if (flagNotPOSDistinct) {
                                for (map<string, string>::reverse_iterator itr3{ keepTrack.rbegin() }; itr3 != keepTrack.rend(); ++itr3) {
                                    if (itr3->second == partOfSpeech) {
                                        cout << "     " << keyword << " [" << itr3->second << "]  :" << itr3->first << endl;
                                    }
                                }

                            }
                            else {
                                for (map<string, string>::reverse_iterator itr3{ keepTrack.rbegin() }; itr3 != keepTrack.rend(); ++itr3) {
                                    cout << "     " << keyword << " [" << itr3->second << "]  :" << itr3->first << endl;
                                }
                            }
                            
                        }
                        
                    }
                }
            }
        }
        if (!getValidKeyword() == false) {
            cout << "    |" << endl;
        }
        
    }
    
    //create a map of Part of speech to a vector of definitions
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

    //parse out all data after key
    void findAllDef(string line) {
        vector<string> definitions;
        vector<string> partOSpeech;
        string frontDelim = "> ";
        string rearDelim = "|";
        string endDelim = ".";
        string posRearDelim = " -";

        int startIndex;
        int endIndex;
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

    //get the key
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
            cout << "     <NOT FOUND> To be considered for the next release. Thank you" << endl << "    |" << endl;
            cout << "    |" << endl;
            cout << "     PARAMETER HOW-TO, please enter:" << endl;
            cout << "     1. A search key - then 2. An optional part of speech - then" << endl
                << "     3. An optional 'distinct' -then 4. An optional 'reverse'" << endl << "    |" << endl;
            setValidKeyword(false);
        }
    }
};

int main() {
    Dictionary dictionary;
    vector<string> data;
    int count = 1;
    int keyCount = 0;
    string userInput = "";
    fstream ioFile;
    bool end = false;

    ioFile.open("Data.CS.SFSU.txt", ios::in);

    if (ioFile.is_open()) {
        string temp;
        while (getline(ioFile, temp)) {
            keyCount++;
            data.push_back(temp);
        }
    }
    ioFile.close();

    cout << "! Loading Complete...\n" << endl << "===== DICTIONARY 340 JAVA =====" <<
       endl << "----- Keywords: " << keyCount << endl << "----- Definitions: " << endl;

    while (!end) {
        
        
        cout << "Search["<< count << "]: ";
        getline(cin, userInput);
        
        
        count++;
        //convert user input to lower
        for_each(userInput.begin(), userInput.end(), [](char& c) {
            c = tolower(c);
        });


        if (userInput == "!q") {
            end = true;
            cout << endl << "-----THANK YOU-----";
        }
        else if (userInput == " " || userInput == "!help" || userInput == "") {
            cout << "    |" << endl;
            cout << "     PARAMETER HOW-TO, please enter:" << endl;
            cout << "     1. A search key - then 2. An optional part of speech - then" << endl 
                << "     3. An optional 'distinct' -then 4. An optional 'reverse'" << endl << "    |" << endl;
        }
        else {
            cout << "    |" << endl;
            dictionary.findKey(data, userInput);
            map<string, vector<string>> keywordData = dictionary.getMapData();
            dictionary.toString(userInput, keywordData);
        }
     }

     return 0;
}
