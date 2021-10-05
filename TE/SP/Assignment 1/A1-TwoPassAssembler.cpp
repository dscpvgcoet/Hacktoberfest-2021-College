/* Systems Programming Lab
 * Yatish Kelkar TE IT 8001
 * Assignment 1 : Pass 1 of Two Pass Assembler
 * 17/02/21
*/

#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
#include<vector>
#include<sstream>
#include<algorithm>

#define SIZE_SMALL 50
#define SIZE_LARGE 100

using namespace std;

class SymbolTable {

    public : 
        int index;
        int location;
        string symbol;

    // public :

        SymbolTable() {}

        SymbolTable(int indexFormal, int locationFormal, string symbolFormal) {
            index = indexFormal;
            location = locationFormal;
            symbol = symbolFormal;
        }
};

class LiteralTable {
    
    public : 
        int index;
        int location;
        string literal;

    // public :

        LiteralTable() {}

        LiteralTable(int indexFormal, int locationFormal, string literalFormal) {
            index = indexFormal;
            location = locationFormal;
            literal = literalFormal;
        }
};

class PoolTable {

    public : 
        int poolNumber;

        PoolTable(int poolNumberFormal) {
            poolNumber = poolNumberFormal;
        }
};

class Mnemonics {
    
    public : 
        string mnemonic;
        string opcode;  
        string type;
    

        Mnemonics() {}

        Mnemonics(string mnemonicFormal, string opcodeFormal, string typeFormal) {
            mnemonic = mnemonicFormal;
            opcode = opcodeFormal;
            type = typeFormal;
        }
};

class Assembler {
    
    private : 
        vector <SymbolTable> symbolTable;
        vector <LiteralTable> literalTable;
        vector <PoolTable> poolTable;
        vector <Mnemonics> mnemonicsTable;
        fstream sourceFile, intermediateCodeFile, symbolFile, literalFile, poolFile, mnemonicFile;
        int LC;
        vector <string> errorMessages;
        vector <string> IC;
        stringstream ss;
        string temp;
        bool startPresent, endPresent, invalidInstruction;
        int instructionNumber;
        char buffer[10];

    
    public : 
        Assembler();
        void convertToCode();
        void displaySymbolTable();
        void displayLiteralTable();
        void displayPoolTable();
        bool isMnemonic(string);
        string returnOpcode(string);
        string returnType(string);
        bool isLiteralAlreadyPresent(string);
        bool isLabelAreadyPresent(string);
        void detectErrors(string, string, string, string);
        void writeOutput();
};

Assembler :: Assembler () {

    string currentLine;
    cout << "\nOpening source file..." << endl;
            
    sourceFile.open("assembly-program.txt", ios::in);

    if(!sourceFile) {
        cout << "\nError opening source assembly file, please try again" << endl;
        exit(0);
    } else {
        cout << "\nSource assembly file opened successfully" << endl;
    }

    mnemonicFile.open("mnemonics.txt", ios::in);

    if(!mnemonicFile) {
        cout << "\nError opening mnemonic file, please try again" << endl;
        exit(0);
    } 

    while(!mnemonicFile.eof() && getline(mnemonicFile, currentLine, '\n')) {

        vector <string> mnemonics;
        string word;
        
        istringstream s(currentLine);
        while(getline(s, word, ' ')) {
            mnemonics.push_back(word);
        }

        mnemonicsTable.push_back(Mnemonics(mnemonics.at(0), mnemonics.at(1), mnemonics.at(2)));
    }

    startPresent = false;
    endPresent = false;
    invalidInstruction = false;
    instructionNumber = 0;

}


// converts the assembly program to intermeidate code
void Assembler :: convertToCode() {

    string currentLine, word;
    bool shouldUpdateLC = false;
    
    cout << "\nStarting reading source file..." << endl;

    while(!sourceFile.eof() && getline(sourceFile, currentLine, '\n')) {
        
        if(shouldUpdateLC) LC++;
        
        vector <string> inputWords;
        string label, instruction, operand1, operand2;
        
        istringstream s(currentLine);
        while(getline(s, word, ' ')) {
            inputWords.push_back(word);
        }

        label = inputWords.at(0);
        instruction = inputWords.at(1);
        operand1 = inputWords.at(2);
        operand2 = inputWords.at(3);

        // cout << "\n\n-------------------------------------\n";
        // cout << "l:" << label << "\ti:" << instruction << "\to1:" << operand1 << "\to2:" << operand2<< "\t" << LC ;
        if(instructionNumber == 0 && instruction != "START") {
            startPresent = false;
            break;
        }
        detectErrors(label, instruction, operand1, operand2);
        // cout << " \n\ninstr no" << instructionNumber;
        // conditions for insruction
        
        if(instruction == "START") {
            LC = atoi(operand1.c_str());
            poolTable.push_back(PoolTable((int)literalTable.size()));
            cout << "\n(" << returnType("START") << "," << returnOpcode("START") << ")  (C," << LC << ")" ;
            //ss << LC + 1; ss >> temp;
            IC.push_back("\n(" + returnType("START") + "," + returnOpcode("START") + ")\t(C," + string(itoa(LC, buffer, 10)) + ")");
            startPresent = true;
            instructionNumber++;
            continue;
        }
        else if(instruction == "LTORG") {
            
            poolTable.push_back(PoolTable((int)literalTable.size()));
            
            int numberOfLiterals = poolTable.at(poolTable.size() -1 ).poolNumber - poolTable.at(poolTable.size() -2 ).poolNumber;
            
            for(int i = 0; i < numberOfLiterals; i++) {
                literalTable.at((int)literalTable.size() - numberOfLiterals + i).location = LC ;
                LC++;
            }
            shouldUpdateLC = false;
            cout << "\n(" << returnType("LTORG") << "," << returnOpcode("LTORG") << ")" ;
            
            IC.push_back("\n(" + returnType("LTORG") + "," + returnOpcode("LTORG") + ")") ;
            instructionNumber++;
            continue;
        }
        else if(instruction == "ORIGIN") {
            
            if(int pos = operand1.find("+") != string::npos) {
                string symb = operand1.substr(0, pos);
                for(int i = 0; i < symbolTable.size(); i++) {
                    if(symbolTable.at(i).symbol == symb) {
                        LC = symbolTable.at(i).location + atoi(operand1.substr(pos, operand1.size() - pos).c_str());
                    }
                }
            } else {
                LC = atoi(operand1.c_str());
            }
            shouldUpdateLC = false;
            cout << "\n(" << returnType("ORIGIN") << "," << returnOpcode("ORIGIN") << ") (C," << LC << ")" ;
            ss << LC ; ss >> temp;
            IC.push_back("\n(" + returnType("ORIGIN") + "," + returnOpcode("ORIGIN") + ") (C," + string(itoa(LC, buffer, 10)) + ")" );
            instructionNumber++;
            continue;
        }
        else if(instruction == "DS") {
            LC = LC + atoi(operand1.c_str());
            cout << "\n(" << returnType("DS") << "," << returnOpcode("DS") << ") (C," << operand1 << ")" ;
            IC.push_back("\n(" + returnType("DS") + "," + returnOpcode("DS") + ") (C," + operand1 + ")" );
            instructionNumber++;
            continue;
        }
        else if(instruction == "END") {
            shouldUpdateLC = false;
            cout << "\n(" << returnType("END") << "," << returnOpcode("END") << ")" << endl ;
            IC.push_back("\n(" + returnType("END") + "," + returnOpcode("END") + ")" + "\n" );
            endPresent = true;
            instructionNumber++;
            continue;
        }
        else if(instruction == "EQU") {
            
            cout << "\n(" << returnType("EQU") << "," << returnOpcode("EQU") << ")" ;
            IC.push_back("\n(" + returnType("EQU") + "," + returnOpcode("EQU") + ")") ;
            
            
            string symbolForEQU, operandForEQU;
            int i = 0, operandForEQUInt;

            while(operand1.at(i) != '+') {
                symbolForEQU.push_back(operand1.at(i));
                i++;
            }
            i++;
            while(i < operand1.size()) {
                operandForEQU.push_back(operand1.at(i));
                i++;
            }

            int locSymb;
            for(int j = 0; j < symbolTable.size(); j++) {
                if(symbolTable.at(j).symbol == symbolForEQU) {
                    cout << " (S," << j  << ") + " << operandForEQU;
                    ss << j ; ss >> temp;
                    locSymb = symbolTable.at(j).location;
                    IC.push_back(" (S," + string(itoa(j, buffer, 10))  + ") + " + operandForEQU);
                }
            }  
            symbolTable.push_back(SymbolTable((int)symbolTable.size(), locSymb+atoi(operandForEQU.c_str()), label)); 
            instructionNumber++;
            shouldUpdateLC = false;
            continue;
        } else if(returnType(instruction) == "NA") {
            errorMessages.push_back("Invalid instruction");
            endPresent = true;
            invalidInstruction = true;
            break;
        }

        cout << "\n(" << returnType(instruction) << "," << returnOpcode(instruction) << ")" ;
        IC.push_back("\n(" + returnType(instruction) + "," + returnOpcode(instruction) + ")") ;

        
        // conditions for operand1
        if(operand1 != "-") {
            if(operand1.at(operand1.size()-1) == ',') {
                operand1.resize(operand1.size() - 1);
                cout << " (" << returnType(operand1) << "," << returnOpcode(operand1) << ")" ;
                IC.push_back(" (" + returnType(operand1) + "," + returnOpcode(operand1) + ")") ;
            }
            if(!isMnemonic(operand1)) {
                if(!isLabelAreadyPresent(operand1)) {
                    symbolTable.push_back(SymbolTable((int)symbolTable.size(), -1, operand1));
                    cout << " (S," << symbolTable.size()-1 << ")" ;
                    ss << (static_cast<int>(symbolTable.size()) - 1) ; ss >> temp;
                    
                    IC.push_back(" (S," + string(itoa(symbolTable.size()-1, buffer, 10)) + ")");
                }
            }
        }


        // conditions for operand2
        if (operand2 != "-") {
            if (operand2.at(0) == '=') {
                if(!isLiteralAlreadyPresent(operand2)) {
                    literalTable.push_back(LiteralTable((int)literalTable.size(), LC, operand2));
                    cout << "(L," << literalTable.size()-1 << ")" ;
                    ss << literalTable.size() - 1 ; ss >> temp;
                    IC.push_back(" (L," + string(itoa(literalTable.size()-1, buffer, 10)) + ")");
                }
            } else {
                if(!isLabelAreadyPresent(operand2)) {
                    symbolTable.push_back(SymbolTable((int)symbolTable.size(), LC, operand2));
                    cout << " (S," << symbolTable.size()-1 << ")" ;
                    ss << symbolTable.size() - 1 ; ss >> temp;
                    IC.push_back(" (S," + string(itoa(symbolTable.size()-1, buffer, 10)) + ")");
                }
            }
        }

        // conditions for label
        if (label != "-") {
            if(isLabelAreadyPresent(label)) {
                for(int i = 0; i < symbolTable.size(); i++) {
                    if(symbolTable.at(i).symbol == label) {
                        if(symbolTable.at(i).location == -1) {
                            symbolTable.at(i).location = LC;
                        }
                        else {
                            errorMessages.push_back("ERROR: Redeclaration of symbol");
                        }
                        break;                        
                    }
                }
            }
            else {
                symbolTable.push_back(SymbolTable((int)symbolTable.size(), LC, label));
                cout << "(S," << symbolTable.size()-1 << ")" ;
                ss << symbolTable.size() - 1 ; ss >> temp;
                IC.push_back(" (S," + string(itoa(symbolTable.size()-1, buffer, 10)) + ")");
            }
        } 

        shouldUpdateLC = true;
        instructionNumber++;

    }

    if(!startPresent) errorMessages.push_back("Start instruction missing");
    if(!endPresent && startPresent) errorMessages.push_back("End instruction missing");

    for(int i = 0; i < symbolTable.size(); i++) {
        if(symbolTable[i].location == -1) {
            errorMessages.push_back("Symbol not defined");
        }
    }
    cout << endl;
    for(int i = 0; i < errorMessages.size(); i++) {
        cout << "\nERROR : " << errorMessages.at(i);
    }

    if(startPresent && endPresent && !invalidInstruction) {
        displayPoolTable();
        displayLiteralTable();
        displaySymbolTable();
    }
    
    writeOutput();
    
}


// display the symbol table
void Assembler :: displaySymbolTable() {
    
    // cout << "\n==============================";
    cout << "\n\nSymbol table is :\n"; 
    cout << "INDEX\tSYMBOL\tADDRESS" << endl;  
    for(int i = 0; i < symbolTable.size(); i++) {
        cout << i << "\t" << symbolTable.at(i).symbol << "\t" << symbolTable.at(i).location << endl;
    }
    
}


// display literal table
void Assembler :: displayLiteralTable() {
    
    // cout << "\n==============================";
    cout << "\n\nLiteral table is :\n"; 
    cout << "INDEX\tLITERAL\tADDRESS" << endl;  
    for(int i = 0; i < literalTable.size(); i++) {
        cout << i << "\t" << literalTable.at(i).literal << "\t" << literalTable.at(i).location << endl;
    }
    
}


// display pool table 
void Assembler :: displayPoolTable() {
    
    // cout << "\n==============================";
    cout << "\n\nPool table is :\n";
    cout << "POOL\tLIT NUMBER" << endl;  
    for(int i = 0; i < poolTable.size()-1; i++) {
        cout << i+1 << "\t" << poolTable.at(i).poolNumber << endl;
    }
    
}


// returns true or false based on whether input is present in mnemonic table
bool Assembler :: isMnemonic(string search) {

    for(int i = 0; i < mnemonicsTable.size(); i++) {
        if(mnemonicsTable.at(i).mnemonic == search) return true;
    } 
    return false;
}


// returns the opcode of the instruction
string Assembler :: returnOpcode(string instruction) {

    for(int i = 0; i < mnemonicsTable.size(); i++) {
        if(mnemonicsTable.at(i).mnemonic == instruction) {
            return mnemonicsTable.at(i).opcode;
        }
    }
    return "NA";
}


// returns the type of instruction
string Assembler :: returnType(string instruction) {

    for(int i = 0; i < mnemonicsTable.size(); i++) {
        if(mnemonicsTable.at(i).mnemonic == instruction) {
            return mnemonicsTable.at(i).type;
        }
    }
    return "NA";
}


// is literal already there in literal pool
bool Assembler :: isLiteralAlreadyPresent (string literal) {
    
    for(int i = poolTable.at((int)poolTable.size() - 1).poolNumber; i < literalTable.size(); i++) {
        if(literalTable.at(i).literal == literal) {
            return true;
        }
    }
    return false;
}

// is label already there in literal pool
bool Assembler :: isLabelAreadyPresent (string label) {
    
    for(int i = 0; i < symbolTable.size(); i++) {
        if(symbolTable.at(i).symbol == label) {
            return true;
        }
    }
    return false;
}

// detect errors in program
void Assembler :: detectErrors(string label, string instruction, string operand1, string operand2) {
    
    if(instruction == "MOVEM" || instruction == "MOVER" || instruction == "ADD" || instruction == "SUB" || instruction == "MULT")
        if(operand1 != "AREG," && operand1 != "BREG," && operand1 != "CREG," && operand1 != "DREG,")
            errorMessages.push_back("Invalid operand declared");

    if(instruction == "LTORG" || instruction == "END" || instruction == "STOP")
        if(operand1 != "-" || operand2 != "-")
            errorMessages.push_back("Unnecessary operand found");

    if(instruction == "START" || instruction == "ORIGIN")
        if(operand1 == "-")
            errorMessages.push_back("No operand found");

    if(instruction == "START" || instruction == "ORIGIN")
        if(operand2 != "-")
            errorMessages.push_back("Unnecessary second operand detected");

}

void Assembler :: writeOutput () {

    literalFile.open("literal_output.txt", ios::out);
    poolFile.open("pool_output.txt", ios::out);
    symbolFile.open("symbol_output.txt", ios::out);
    intermediateCodeFile.open("ic.txt", ios::out);

    literalFile << "  SRNO  LITERAL   LOCATION\n\n"; 
    for(int i = 0; i < literalTable.size(); i++) {
        literalFile << "   " << literalTable[i].index << "     " << literalTable[i].literal << "\t\t" << literalTable[i].location << endl;
    }

    poolFile << "  POOL  LITERAL NUMBER\n\n"; 
    for(int i = 0; i < poolTable.size()-1; i++) {
        poolFile << "   " << i+1 << "     " << poolTable[i].poolNumber << endl;
    }

    symbolFile << "  SRNO  SYMBOL   LOCATION\n\n"; 
    for(int i = 0; i < symbolTable.size(); i++) {
        symbolFile << "   " << symbolTable[i].index << "\t\t\t" << symbolTable[i].symbol << "\t\t\t\t" << symbolTable[i].location << endl;
    }

    for(int i = 0; i < IC.size(); i++) {
        intermediateCodeFile << "   " << IC[i] ;
    }

    cout << "\nOutput written to 4 files." << endl;
}


int main () {

    Assembler analyzer;
    analyzer.convertToCode();

    return 0;
}
