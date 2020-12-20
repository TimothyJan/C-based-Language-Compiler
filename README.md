# FakeLanguageCompiler
Components of a compiler for a made-up C-based language. 

When prompted, provide the pathway to the text file you wish to generate text files for. The first text file generated is the “1 - Output_Lexical_Analyzer.txt” and contains the tokens and lexemes. The second file generated is the “2 - Output_Syntax_Analyzer.txt” and contains the tokens and lexemes with the production rules used for analyzing each token.

Lexical Analyzer parses through the source code and outputs each lexeme and its appropriate token. It strips extraneous characters from source code, breaks up the source code into meaningful units called tokens and implements the Deterministic Finite State Machine to classify each of the lexemes with appropriate tokens.

Syntax Analyzer parses through source code to determine if it is syntactically correct. With the grammar given, I rewrote the grammar to remove any left recursion and ambiguity. I created a predictive table with the First and Follow sets of the rewritten grammar. The Top-Down Syntax Analyzer parses through the source code, uses a stack and prints out the tokens/lexemes and all the production rules used for analyzing the tokens. 

