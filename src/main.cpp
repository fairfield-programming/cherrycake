//
//  main.cpp
//  cherrycake
//
//  Created by William McGonagle on 11/30/22.
//

#include "tokenizer.h"
#include "console.h"
#include "lexer.h"
#include "ast/ast.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

bool run_command(int argc, const char * argv[]) {
    
    // Maybe check if ends with .chry
    
    std::string command = argv[1];
    
    if (command == "help") {
        
        if (argc >= 3) {
            
            console::help(argv[2]);
            
        } else {
            
            console::help();
            
        }
        
        return true;
        
    }
    
    return false;
    
}

int interpret_file(std::ifstream& file_stream) {
    
    // Read each token from the file
    std::vector<Token> tokens = tokens_from_file(file_stream);
    
    // Run each token through the lexer
    std::vector<ast::Statement*> body = lexer::ast_from_tokens(tokens);
    
    // Print the Tokens
    console::log(lexer::print_from_ast(body));
    
    return 1;
    
}

int main(int argc, const char * argv[]) {
    
    // Check that there are arguments
    if (argc == 1) { console::help(); return -1; }
    
    // Check if argv corresponds to a command
    if (run_command(argc, argv)) {
        // If so run the command (it does it in the conditional)
        
        return 0;
        
    } else {
        // Otherwise, run the file in interpretted mode
        
        std::ifstream currentFile (argv[1]);
        
        // If the file won't open, close program
        if (!currentFile.is_open())
        {
            
            // Log an Error and Escape
            console::log("Could not load file.");
            return -1;
            
        }
        
        // Interpret the file
        interpret_file(currentFile);
        
        // Program succeeded
        return 0;
        
    }
    
}
