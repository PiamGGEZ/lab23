#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(const string &filename, vector<string> &names, vector<int> &scores, vector<char> &grades) {
    ifstream file(filename);
    if (!file) {
        cerr << "Unable to open file " << filename << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        char name[100];
        int score1, score2, score3;

       
        sscanf(line.c_str(), "%[^:]: %d %d %d", name, &score1, &score2, &score3);

        int total_score = score1 + score2 + score3; 
        names.push_back(name);
        scores.push_back(total_score);
        grades.push_back(score2grade(total_score));
    }

    file.close();
}


void getCommand(string &command, string &key){
    cout << "Please input your command: \n";
    string input;
    getline(cin, input);


    size_t spacePos = input.find(' ');
    if (spacePos != string::npos) {
        command = input.substr(0, spacePos); 
        key = input.substr(spacePos + 1);   
    } else {
        command = input;
        key = "";
    }

    command = toUpperStr(command); 
}


void searchName(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, string key){
    bool found = false;
    cout << "---------------------------------" << endl;

    for (size_t i = 0; i < names.size(); i++) {
        if (toUpperStr(names[i]) == toUpperStr(key)) { 
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            found = true;
            break; 
        }
    }

    if (!found) {
        cout << "Cannot found." << endl;
    }

    cout << "---------------------------------" << endl;
}

void searchGrade(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, string key){
    bool found = false;
    cout << "---------------------------------" << endl;

    for (size_t i = 0; i < grades.size(); i++) {
        if (grades[i] == key[0]) {
            cout << names[i] << " (" << scores[i] << ")" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Cannot found." << endl;
    }

    cout << "---------------------------------" << endl;
}



int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}