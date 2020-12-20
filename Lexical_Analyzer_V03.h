#include <iostream>
#include <string>
#include <fstream> // Stream class to both read and write from/to files
#include <sstream>

using namespace std;

bool isComment = false;
string output_Lexical_String = "TOKENS \t\t LEXEMES \n";
string input_Syntax_String = "";//delete

bool checkIfSeparator(const string& str)
{
    string separators[] = {"'","(",")","{","}","[","]",",",".",":",";"," "};
    for(int i=0; i<=12;i++)
    {
        if(str == separators[i])
            return true;
    }
    return false;
}

bool checkIfOperator(const string& str)
{
    string operators[] = {"*","+","-","=","/",">","<","%"};
    for(int i=0; i<=8;i++)
    {
        if(str == operators[i])
            return true;
    }
    return false;
}

bool checkIfNumber(const string& str)
{
    bool result = false;
    char numbers[] = {'0','1','2','3','4','5','6','7','8','9', '.'};
    for(int i=0;i<11;i++)
    {
        if(str[0] == numbers[i])
            result = true;
    }
    return result;
}

bool checkReal(const string& str)
{
    bool result = false;
    for(int i=0;i<str.length();i++)
    {
        if(str[i] == '.')
            result = true;
    }
    return result;
}

bool checkIfKeyword(const string& str)
{
    string keywords[] = {"int","float","bool","true","false","if","else","then","endif","while","whileend","do","doend","for","forend","input","output","and","or","not"};
    for(int i=0;i<20;i++)
    {
        if(str == keywords[i])
            return true;
    }
    return false;
}

bool checkIfIdentifier(const string& str)
{
    char alphabet[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    char index1 = toupper(str[0]);
    for(int i=0; i<26; i++)
    {
        if(index1 == alphabet[i])
            return true;
    }
    return false;
}

int checkInput(const string& str)
{
    if(checkIfSeparator(str))
        return 1;
    else if(checkIfOperator(str))
        return 2;
    else if(checkIfNumber(str))
        return 3;
    else
        return 4;
}

void checkFinalState(const int& state, const string& lexeme)
{
    if (state == 0){
        output_Lexical_String +=  lexeme + "\t = \t ERROR \n";
        input_Syntax_String +=  lexeme + "\t = \t ERROR \n";
    }
    else if(state == 1){
        output_Lexical_String += lexeme +  "\t = \t SEPARATOR \n";
        input_Syntax_String +=  lexeme + "\t = \t SEPARATOR \n";
    }
    else if(state == 2){
        output_Lexical_String += lexeme + "\t = \t OPERATOR \n";
        input_Syntax_String +=  lexeme + "\t = \t OPERATOR \n";
    }
    else if(state == 3)
    {
        if(checkReal(lexeme)){
            output_Lexical_String += lexeme + "\t = \t REAL \n";
            input_Syntax_String +=  lexeme + "\t = \t REAL \n";
        }
        else{
            output_Lexical_String += lexeme + "\t = \t INTEGER \n";
            input_Syntax_String +=  lexeme + "\t = \t INTEGER \n";
        }     
    }
    else    //state=4
    {
        if(checkIfKeyword(lexeme)){
            output_Lexical_String += lexeme +  "\t = \t KEYWORD \n";
            input_Syntax_String +=  lexeme + "\t = \t KEYWORD \n";
        }
        else if(checkIfIdentifier(lexeme)){
            output_Lexical_String += lexeme +  "\t = \t IDENTIFIER \n";
            input_Syntax_String +=  lexeme + "\t = \t IDENTIFIER \n";
        }         
        else{
            output_Lexical_String += lexeme +  "\t = \t ERROR \n";
            input_Syntax_String +=  lexeme + "\t = \t ERROR \n";
        }
    }
}

void lexer(const string& line)
{
    int inputSymbol = 0, state = 0;
    int fsm_table[5][5] ={  {0, 1,  2,  3,  4},
                            {1, 0,  0,  0,  0},
                            {2, 0,  0,  0,  0},
                            {3, 3,  0,  3,  0},
                            {4, 0,  0,  4,  4}  };
    string lexeme="", character="";
    bool skip = false;

    //Parses through each char in line
    for(int index=0; index<line.length();index++)
    {
        //Check if space
        if(line[index] == ' ')
        {
            if(lexeme != "")
            {
                checkFinalState(state,lexeme);
                state = 0;
                lexeme = "";
            }
            skip=true;
        }
        //skips iteration due to character being a space
        if(skip)
        {
            skip=false;
            continue;
        }

        //convert character to string type
        stringstream str;
        str<<line[index]; 
        str>>character;
        //cout<<"Character: "<<character<<endl;

        //Check if comment
        if(character == "!")
        {
            isComment = !isComment;
            continue;
        }

        //If not comment
        if(!isComment)
        {
            inputSymbol = checkInput(character);

            if(inputSymbol == 1 || inputSymbol == 2)
            {
                //If '.' and state is number
                if(state == 3 && character == ".")
                {
                    lexeme += character;
                    continue;
                }
                //Checks previous lexeme
                if(lexeme != "")
                {
                    checkFinalState(state,lexeme);
                    state=0;
                }

                //New state with operator/separator
                state = fsm_table[state][inputSymbol];             
                checkFinalState(state,character);
                state=0;
                lexeme = "";          
            }
            else if(inputSymbol == 3 || inputSymbol ==4)
            {
                state = fsm_table[state][inputSymbol];
                lexeme += character;

                //if end of line with no separator
                if(index == (line.length()-1))
                {
                    checkFinalState(state,lexeme);
                    state=0;
                    lexeme = "";
                }
            }
            else
                cout<<"Something went wrong"<<endl;
        }
    }
}