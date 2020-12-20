#include <iostream>
#include <string>
#include <fstream> // Stream class to both read and write from/to files
#include <sstream>

#include "Lexical_Analyzer_V03.h"
#include "Syntax_Analyzer_V05.h"
//#include "Syntax_Analyzer_V06.h"
#include "ICG_V01.h"

using namespace std;

void Syntaxical_Analyzer_Test()
{
    string line, pathway;
    int line_Number = 1;

    cout<<"Enter the pathway to the text file you wish to use: ";
    getline(cin,pathway);

    ifstream input_File(pathway);       //Open file
    if(!input_File.is_open())           //Ensures file is open
    {           
        cout<<"Error opening file"<<endl;
        exit(0);
    }

    //Parses through each line of the file until end of file
    while (!input_File.eof())
    {
        while(getline(input_File,line))
        {
            // cout<<"------------------------------"<<endl;//DELETE
            //cout<<line<<endl;//DELETE
            // cout<<"Line Number: "<<line_Number<<endl;//DELETE
            //1: LEXER: generate the string needed for Lexical Analyzer Output file and generates input_Syntax_String
            lexer(line); 
            //2: generate the string needed for the Syntaxical Analyzer File and generates input_ICG for ICG
            if(input_Syntax_String != "")
            {
                syntax_Analyzer(input_Syntax_String, line_Number);\
                input_Syntax_String = ""; //reset the input for the Syntaxical Analyzer every new line
            }
            //tracking which line
            line_Number++;

            //3: Symbol Table, uses input_ICG generated from Syntaxical Analyzer
            // cout<<input_ICG<<endl;
            // ICG(input_ICG);
            // input_ICG = "";//reset the input for the ICG
        }
    }
    input_File.close();

    // creating Lexical file output with results
    ofstream output_Lexical_Analyzer_File;
    output_Lexical_Analyzer_File.open("1 - Output_Lexical_Analyzer.txt");
    output_Lexical_Analyzer_File << output_Lexical_String; //outputstring declared in Lexical_Analyzer-V02.h
    output_Lexical_Analyzer_File.close();

    // creating Syntaxical file output
    ofstream output_Syntax_Analyzer_File;
    output_Syntax_Analyzer_File.open("2 - Output_Syntax_Analyzer.txt");
    output_Syntax_Analyzer_File << output_Syntax_Analyzer; //outputstring declared in Lexical_Analyzer-V02.h
    output_Syntax_Analyzer_File.close();

    // //creating ICG file output
    // ofstream output_ICG_File;
    // output_ICG_File.open("Output_ICG.txt");
    // output_ICG_File << output_ICG;
    // output_ICG_File.close();
}

int main()
{
    Syntaxical_Analyzer_Test();

    string exit;
    cout<<"Enter any character to exit: ";
    cin>> exit;
    
    return 0;
}