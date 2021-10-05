/* Systems Programming Lab
 * Yatish Kelkar TE IT 8001
 * Assignment 2 : Pass 2 of Two Pass Assembler
 * 11/03/21
*/

#include<iostream>
#include<string.h>
#include<fstream>
#include<stdlib.h>
#include<vector>
#include<sstream>
#include<algorithm>


using namespace std;

class Literal {

    public:
        string index;
        string address;

        Literal(string indexF, string addressF) {
            index = indexF;
            address = addressF;
        }
};

class Symbol {

    public:
        string index;
        string address;

        Symbol(string indexF, string addressF) {
            index = indexF;
            address = addressF;
        }
};

string getTokenText(string);

string getTokenText(string token, vector<Literal> littab, vector<Symbol> symbtab) {

    string text = "";
    if(!(token.at(0) == '(')) return "";

    if(token.at(1) == 'A' || token.at(1) == 'D' ) return " ";

    if(token.at(1) == 'I' && token.at(2) == 'S') {
        text.push_back(token.at(4));
        text.push_back(token.at(5));
    }

    if(token.at(1) == 'R' && token.at(2) == 'E' && token.at(3) == 'G') {
        text.push_back(token.at(5));
        text.push_back(token.at(6));
    }

    if(token.at(1) == 'L') {
        for (int i = 0; i < littab.size(); i++)
        {   
            if(string(1,token.at(3)) == littab.at(i).index){
                text.append(littab.at(i).address);
                break;
            }
        }
    }

    if(token.at(1) == 'S') {
        for (int i = 0; i < symbtab.size(); i++)
        {
            if(string(1,token.at(3)) == symbtab.at(i).index){
                text.append(symbtab.at(i).address);
                break;
            }
        }
    }
    return text;
}

int main () {

    fstream ICfile, litFile, symbFile, machineCodeFile;
    vector<Literal> literalTable;
    vector<Symbol> symbolTable;
    vector<string> output;

    ICfile.open("ic.txt", ios::in);
    litFile.open("literal_tab.txt", ios::in);
    symbFile.open("sym_table.txt", ios::in);

    string line;
    int startAdd = 200;

    if(!ICfile || !litFile || !symbFile) {
        cout << "\nError opening source file, please try again" << endl;
        exit(0);
    }

    // read literal file
    while (!litFile.eof() && getline(litFile, line, '\n'))
    {
        vector<string> tokens;
        istringstream s(line);
        string token;
        while(getline(s, token, ' ')) {
            tokens.push_back(token);
        }
        literalTable.push_back(Literal(tokens.at(0), tokens.at(1)));
    }

    // read symbol file
    while (!symbFile.eof() && getline(symbFile, line, '\n'))
    {
        vector<string> tokens;
        istringstream s(line);
        string token;
        while(getline(s, token, ' ')) {
            tokens.push_back(token);
        }
        symbolTable.push_back(Symbol(tokens.at(0), tokens.at(1)));
    }

    while(!ICfile.eof() && getline(ICfile, line, '\n')) {
        
        vector<string> tokens;
        istringstream s(line);
        string token, temp;

        
        while(getline(s, token, ' ')) {
            tokens.push_back(token);
        }
        cout << startAdd << ")";

        stringstream ss;
        ss << startAdd; ss >> temp;
        output.push_back(temp);
        output.push_back(")");

        if(tokens.at(0).at(1) == 'I') {
            cout << " + ";
            output.push_back(" + ");
        }
        for (int i = 0; i < tokens.size(); i++) {
            string tokenText = getTokenText(tokens.at(i), literalTable, symbolTable);
            cout << tokenText << " ";
            output.push_back(tokenText);
            output.push_back(" ");
        }
        cout << endl;
        output.push_back("\n");
        startAdd++;
    }

    machineCodeFile.open("machine-code.txt", ios::out);
    for (int i = 0; i < output.size(); i++)
    {
        machineCodeFile.write(output.at(i).c_str(), output.at(i).size());
    }
    return 0;  
}