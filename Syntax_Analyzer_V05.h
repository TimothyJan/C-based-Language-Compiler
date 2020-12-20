#include <iterator>
#include <vector>
#include <stack>

using namespace std;

vector<string> lexemes;      //container of lexemes with same index as tokens
vector<string> tokens;     //container of lexemes with matching index as lexemes
vector<string> pt_Input;    //Predictive Table Input - container of lexemes with "i" instead of "IDENTIFIER"
string output_Syntax_Analyzer = "";
string input_ICG = "";

void output_Vector(vector<string> test)     //Outputs contents of Vector
{
    for(vector<string>::iterator i = test.begin(); i != test.end(); i++)
        cout<<*i<<"\t";
    cout<<'\n';
}

void token_Lexeme_Organizer(const string& input_Syntax_String)     //add lexemes and tokens to vectors respectively, creates pt_Input
{
    //Create Vector with input_Syntax_String;
    istringstream iss(input_Syntax_String);
    vector<string> input_Syntax_String_Vector{istream_iterator<string>{iss},
                      istream_iterator<string>{}};
    
    //adds lexemes to token vector and tokens to tokens vector
    for(int i = 1; i<input_Syntax_String_Vector.size()+1; i++)
    {
        if(i%3 == 1)    //add lexemes to token vector
            lexemes.push_back(input_Syntax_String_Vector[i-1]);
        else if(i%3 == 0)   //add tokens to tokens vector
            tokens.push_back(input_Syntax_String_Vector[i-1]);
    }

    //combining relational operators >=, <=, and == and change lexemes and tokens vectors accordingly
    for(int i = 0; i<lexemes.size();i++)
    {
        if( (lexemes.at(i) == ">" && lexemes.at(i+1) == "=") || (lexemes.at(i) == "<" && lexemes.at(i+1) == "=") || (lexemes.at(i) == "=" && lexemes.at(i+1) == "="))
        {
            lexemes[i] = lexemes[i] + lexemes[i+1];
            lexemes.erase(lexemes.begin()+i+1);
            tokens[i] = tokens[i] + tokens[i+1];
            tokens.erase(tokens.begin()+i+1);
        }
    }

    //creates pt_Input, lexemes except replaces IDENTIFIERS with 'i', bool values with 'b', keywords with 'k', and Real/Integers with 'n' for predictive table
    for(int i = 0; i<lexemes.size();i++)
    {
        if(tokens.at(i) == "IDENTIFIER")
            pt_Input.push_back("i");
        else if(tokens.at(i) == "KEYWORD")
        {
            if(lexemes.at(i) == "true" || lexemes.at(i) == "false")
                pt_Input.push_back("b");
            else if(lexemes.at(i) == "bool" || lexemes.at(i) == "float" || lexemes.at(i) == "int")
                pt_Input.push_back("k");
        }
        else if(tokens.at(i) == "REAL" || tokens.at(i) == "INTEGER")
            pt_Input.push_back("n");          
        else
            pt_Input.push_back(lexemes.at(i));
    }

    pt_Input.push_back("$");
}

void lexemes_tokens_Output(const int index) //outputs current token and lexeme
{
    if(index < lexemes.size())
    {
    // cout<<"Lexeme: "<<lexemes.at(index)<<"\t"<<"Token: "<<tokens.at(index)<<endl;
    output_Syntax_Analyzer += "Lexeme: " + lexemes.at(index) + "\t" + "Token: " + tokens.at(index) + "\n";
    }
    else
    {
    // cout<<"Lexeme: "<<lexemes.at(index-1)<<"\t"<<"Token: "<<tokens.at(index-1)<<endl;
    output_Syntax_Analyzer += "Lexeme: " + lexemes.at(index-1) + "\t" + "Token: " + tokens.at(index-1) + "\n";
    }
    
}

void print_Stack(stack<string> s)
{
    if (s.empty())
        return;
    string x = s.top();
    s.pop();
    print_Stack(s);
    cout<<x<<"\t";
    s.push(x);
}

vector<string> stack_Input_To_Vector(string stack_Input)
{
    istringstream iss(stack_Input);
    vector<string> stack_Input_Vector{istream_iterator<string>{iss},
                      istream_iterator<string>{}};
    return stack_Input_Vector;
}

void statement_List_Output(const int rule)
{
    switch(rule)
    {
        case 0:
            //cout<<"\t <Empty> -> Epsilon"<<endl;
            output_Syntax_Analyzer += "\t <Empty> -> Epsilon \n";
            break;
        case 1:
            // cout<<"\t <Statement> ->	<Assign> | <Declarative>"<<endl;
            //     cout<<"\t\t| if <Conditional> then <Statement> else <Statement> endif"<<endl;
            //     cout<<"\t\t| while <Conditional> do <Statement> whileend"<<endl;
            output_Syntax_Analyzer += "\t Statement -> <Assign> | <Declarative> \n\t\t | if <Conditional> then <Statement> else <Statement> endif \n\t\t | while <Conditional> do <Statement> whileend\n";
            break;
        case 2:
            // cout<<"\t <Assign> -> <Identifier> = <Expression>;"<<endl;
            output_Syntax_Analyzer += "\t <Assign> -> <Identifier> = <Expression> \n";
            break;
        case 3:
            // cout<<"\t <Expression> -> <Term> <ExpressionPrime> | <bool value>"<<endl;
            output_Syntax_Analyzer += "\t <Expression> -> <Term> <ExpressionPrime> | <bool value>\n";
            break;
        case 4:
            // cout<<"\t <ExpressionPrime> -> + <Term> <ExpressionPrime> | - <Term> <ExpressionPrime> | <Term> "<<endl;
            output_Syntax_Analyzer += "\t <ExpressionPrime> -> + <Term> <ExpressionPrime> | - <Term> <ExpressionPrime> | <Term> \n";
            break;
        case 5:
            // cout<<"\t <Term> -> <Factor> <TermPrime>"<<endl;
            output_Syntax_Analyzer += "\t <Term> -> <Factor> <TermPrime> \n";
            break;
        case 6:
            // cout<<"\t <TermPrime> -> * <Factor> <TermPrime> | / <Factor> <TermPrime> | <Empty>"<<endl;
            output_Syntax_Analyzer += "\t <TermPrime> -> * <Factor> <TermPrime> | / <Factor> <TermPrime> | <Empty> \n";
            break;
        case 7:
            // cout<<"\t <Factor> -> - ( <Expression> ) | <ID> | <num>"<<endl;
            output_Syntax_Analyzer += "\t <Factor> -> - ( <Expression> ) | <ID> | <num> \n";
            break;
        case 8:
            // cout<<"\t <Declarative> -> <Type> <ID> <MoreIds>"<<endl;
            output_Syntax_Analyzer += "\t <Declarative> -> <Type> <ID> <MoreIds>\n";
            break;
        case 9:
            // cout<<"\t <Type> -> bool | float | int"<<endl;
            output_Syntax_Analyzer += "\t <Type> -> bool | float | int \n";
            break;
        case 10:
            // cout<<"\t<MoreIds> -> , <Identifier> <MoreIds> | <empty>"<<endl;
            output_Syntax_Analyzer += "\t <MoreIds> -> , <Identifier> <MoreIds> | <empty> \n";
            break;        
    }
}

void error_Message(const int line_Number, const int token_Lexeme_Index)
{
    // cout<<"\t Error on line "<<line_Number<<endl;
    output_Syntax_Analyzer += "\t Error on line " + std::to_string(line_Number) + "\n";
}

void syntax_Analyzer(const string& input_Syntax_String, const int line_Number)
{
    string predictive_Table[11][14] ={{"",   "i",        "+",     "-",      "*",        "/",      "(",     ")",  "$",  ";", "n",      "k",        ",",    "b"},
                                      {"S",  "A",         "",      "",       "",         "",       "",      "",   "",   "",  "",      "D",        "",     ""},
                                      {"A",  "i = E ;",   "",      "",       "",         "",       "",      "",   "",   "",  "",      "",         "",     ""},
                                      {"E",  "T Q",       "",      "",       "",         "",       "T Q",   "",   "",   "ɛ", "T Q",   "",         "",     "b"},
                                      {"Q",  "T",         "+ T Q", "- T Q",  "",         "",       "T",     "ɛ",  "ɛ",  "ɛ", "T",     "",         "",     ""},
                                      {"T",  "F R",       "",      "",       "",         "",       "F R",   "",   "",   "ɛ", "F R",   "",         "",     ""},
                                      {"R",  "",          "ɛ",     "ɛ",      "* F R",    "/ F R",  "",      "ɛ",  "ɛ",  "ɛ", "ɛ",     "",         "",     ""},    
                                      {"F",  "i",         "",      "",       "",         "",       "( E )", "",   "",   "ɛ", "n",     "",         "",     ""},
                                      {"D",  "",          "",      "",       "",         "",       "",      "",   "",   "ɛ", "",      "Z i M ;",  "",     ""},
                                      {"Z",  "",          "",      "",       "",         "",       "",      "",   "",   "ɛ", "",      "k",        "",     ""},
                                      {"M",  "",          "",      "",       "",         "",       "",      "",   "",   "ɛ", "",      "",         ", i M",""}};
    stack<string> mystack;
    vector<string> stack_Input_Vector;
    vector<int> rulesUsed;
    string table_Row = "", table_Column = "", stack_Input="";
    int table_Row_Int = 0, table_Column_Int = 0, token_Lexeme_Index = 0;
    bool error = false;

    // //reset vector for tokens, lexemes and pt_Input
    tokens.clear();
    lexemes.clear();
    pt_Input.clear();
    
    //organizes lexemes, tokens and pt_Input into respective vectors
    token_Lexeme_Organizer(input_Syntax_String);
    // cout<<"lexemes: "<<endl;output_Vector(lexemes);   //DELETE
    // cout<<"tokens: "<<endl;output_Vector(tokens);  //DELETE
    // cout<<"pt_Input: "<<endl;output_Vector(pt_Input); //DELETE

    //Initialize stack with end marker and start symbol
    mystack.push("$");  //using '$' as end marker symbol
    mystack.push("S");  //start symbol

    //Expression 
    while(!mystack.empty())
    {
        // cout<<"Top of stack: ";print_Stack(mystack);cout<<'\n';//DELETE
        // cout<<"pt_Input:";output_Vector(pt_Input);//DELETE
        if(error)
        {
            // cout<<"Error 1"<<endl;    //DELETE
            error_Message(line_Number, token_Lexeme_Index);
            break;
        }
        if(mystack.top() == "$" && pt_Input.at(0) == "$")
        {
            break;
        }
        if(mystack.top() == "ɛ")
        {
            rulesUsed.push_back(0);
            mystack.pop();
            continue;
        }
        else if(mystack.top() == pt_Input.at(0))    //if beginning of input string and top of stack match
        {
            mystack.pop();
            pt_Input.erase(pt_Input.begin());
            lexemes_tokens_Output(token_Lexeme_Index);
            token_Lexeme_Index++;
            for(int i = 0; i<rulesUsed.size();i++)
            {
                statement_List_Output(rulesUsed.at(i));
                //****ICG: for Symbol Table Declarative Statement used
                // if(rulesUsed.at(i) == 8)
                // {
                //     input_ICG = input_Syntax_String;
                // }
            }
            rulesUsed.clear();
            // cout<<"\n";
            output_Syntax_Analyzer += '\n';
            continue;
        }
        else if(mystack.top() != pt_Input[0])    //If they don't match, access predictive table
        {
            table_Row = mystack.top();
            table_Column = pt_Input.at(0);

            // cout<<"table_Row: "<<table_Row<<endl;//DELETE
            // cout<<"table_Column: "<<table_Column<<endl;//DELETE

            //search for which row of predictive table to use
            for(int i = 1;i<=11;i++)
            {
                if(table_Row == predictive_Table[i][0])
                    table_Row_Int = i;
            }
            //Search for which column of predictive table to use
            for(int j = 1;j<=13;j++)
            {
                if(table_Column == predictive_Table[0][j])
                    table_Column_Int = j;
            }

            // cout<<"table_Row_Int: "<<table_Row_Int<<endl;//DELETE
            // cout<<"table_Column_Int: "<<table_Column_Int<<endl;//DELETE
            // // cout<<"2Enter for next: ";cin>>exit;//DELETE

            //checks if "" in table meaning error
            if(predictive_Table[table_Row_Int][table_Column_Int] == "" || table_Column_Int == 0)
            {
                // cout<<"Error 2"<<endl; //DELETE
                error = true;
                error_Message(line_Number, token_Lexeme_Index);
                break;
            }

            //push new element to top of stack, converts stack input string in predictive table to vector and pushes to mystack in reverse order
            mystack.pop();
            stack_Input = predictive_Table[table_Row_Int][table_Column_Int];
            stack_Input_Vector = stack_Input_To_Vector(stack_Input);    //input for stack is made into vector

            //Rule used is added
            rulesUsed.push_back(table_Row_Int);

            //input for stack is pushed to stack
            for(int k = stack_Input_Vector.size()-1; k>=0;k--)
            {
                mystack.push(stack_Input_Vector.at(k));
            }
            stack_Input_Vector.clear();
            // cout<<"End stack: ";print_Stack(mystack);cout<<'\n';//DELETE
            // output_Vector(pt_Input);//DELETE
        }
    }
}