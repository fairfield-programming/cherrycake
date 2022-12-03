//
//  tokenizer.h
//  cherrycake
//
//  Created by William McGonagle on 11/30/22.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

#pragma once

#include "token_triggers.h"

struct Token {
    
    std::string name;
    std::string data;
    long long int start;
    long long int end;
    
    Token(std::string _name, std::string _data, long long int _start, long long int _end) {
        
        name = _name;
        data = _data;
        start = _start;
        end = _end;
        
    }
    
};

inline std::string keyword_to_tokenname(std::string input) {

    std::string output = input;
    
    std::for_each(output.begin(), output.end(), [](char & c){ c = ::toupper(c); });
    
    return output + "_KEYWORD";
    
}

inline std::string get_token_names() {
    
    std::string output;
    
    for (auto i: keywords)
    {
        
        output.append(keyword_to_tokenname(i) + '\n');
        
    }
    
    for (auto i: symbols) {
        
        output.append(i.name + '\n');
        
    }
    
    return output;
    
}

inline std::string print_current_tokens(std::vector<Token> tokens) {
    
    std::string output;
    
    for (auto i: tokens) {
        
        output = output + i.name + ": " + i.data + "\n";
        
    }
    
    return output;
    
}

inline std::vector<Token> tokens_from_file(std::ifstream& input) {
    
    // Declare high-scoped variables to be used later
    std::vector<Token> output;
    std::string buffer;
    bool insideScope = false;
    Scope curScope = Scope("", "", "", false);
    
    // Check if the file is open
    if (input.is_open()) {
        
        // Loop through each part of the file
        while (input) {
            
            // Loop through all of the scopes and check if any match
            if (insideScope) {
                
                if (curScope.uses_start) {
                    
                    bool matching = true;
                    int j = 0;
                    
                    while (matching && j < curScope.end.length()) {
                        
                        char currentChar = input.get();
                        if (curScope.end[j] != currentChar) { matching = false; break; }
                        j++;
                        
                    }
                    
                    if (matching) {
                        
                        // Calculate where the token is in the file
                        long long int end_pos = input.tellg();
                        long long int start_pos = end_pos - j;
                        
                        // Add the current token
                        output.push_back(Token(curScope.name, buffer, start_pos, end_pos));
                        
                        buffer = "";
                        insideScope = false;
                        
                    } else {
                        
                        // Move the current 'cursor' back
                        input.seekg(-1 - j, input.cur);
                        char temp = input.get();
                        buffer = buffer + temp;
                        
                    }
                    
                } else {
                    // Uses initiator and conditional instead
                    char currentChar = input.get();
                    
                    // Convert current character to string
                    std::string curCharString = {currentChar};
                    std::smatch base_match;
                    
                    // Check if the current character should fit in the scope
                    if (std::regex_match(curCharString, base_match, std::regex(curScope.conditional))) {
                        // Matches
                        
                        buffer = buffer + curCharString;
                        
                    } else {
                        // Doesn't Match
                        
                        // TODO: Figure out how to calculate start position...
                        long long int end_pos = input.tellg();
                        long long int start_pos = end_pos;
                        
                        // Add it in there
                        output.push_back(Token(curScope.name, buffer, start_pos, end_pos));
                        buffer = "";
                        insideScope = false;
                        
                        // We looked at too many chars I guess so we go back–– TO THE FUTURE
                        input.seekg(-1, input.cur);
                        
                    }
                  
                }
                
                continue;
                
            }
            
            // Loop through all of the scopes
            for (auto i: scopes) {
                
                if (i.uses_start) {
                    
                    bool matching = true;
                    int j = 0;
                    
                    while (matching && j < i.start.length()) {
                        
                        char currentChar = input.get();
                        if (i.start[j] != currentChar) { matching = false; break; }
                        buffer = buffer + currentChar;
                        j++;
                        
                    }
                    
                    if (matching) {
                        
                        // Set the current scope
                        insideScope = true;
                        curScope = i;
                        
                        // Clear buffer
                        buffer = "";
                        
                        // We looked at too many chars I guess so we go back–– TO THE FUTURE
                        input.seekg(-1, input.cur);
                        
                        break;
                        
                    } else {
                        
                        // Move the current 'cursor' back
                        input.seekg(-1 - j, input.cur);
                        buffer = "";
                        
                    }
                    
                } else {
                    // Uses initiator and conditional
                    
                    char currentChar = input.get();
                    
                    // Convert current character to string
                    std::string curCharString = {currentChar};
                    std::smatch base_match;
                    
                    if (std::regex_match(curCharString, base_match, std::regex(i.initiator))) {

                        insideScope = true;
                        curScope = i;
                        buffer = {currentChar}; // Set the buffer to currentCharacter string
                        input.seekg(-1, input.cur);
                        break;

                    } else {
                        
                        // Move the current 'cursor' back
                        input.seekg(-1, input.cur);
                        
                    }

                }
                
            }
            
            // Make sure that there's no trespassing
            if (insideScope) {
                
                input.get();
                continue;
                
            }
            
            // Loop through all of the symbols and check if any match
            for (auto i: symbols) {
                
                bool matching = true;
                int j = 0;
                
                while (matching && j < i.data.length()) {
                    
                    char currentChar = input.get();
                    if (i.data[j] != currentChar) { matching = false; break; }
                    buffer = buffer + currentChar;
                    j++;
                    
                }
                
                if (matching) {
                    
                    long long int end_pos = input.tellg();
                    long long int start_pos = end_pos - j;
                    
                    output.push_back(Token(i.name, buffer, start_pos, end_pos));
                    buffer = "";
                    
                    // We looked at too many chars I guess so we go back–– TO THE FUTURE
                    input.seekg(-1, input.cur);
                    break;
                    
                } else {
                    
                    // Move the current 'cursor' back
                    input.seekg(-1 - j, input.cur);
                    buffer = "";
                    
                }
                
            }
            
            // Loop through all of the keywords and check if any match
            for (auto i: keywords) {
                
                bool matching = true;
                int j = 0;
                
                while (matching && j < i.length()) {
                    
                    char currentChar = input.get();
                    if (i[j] != currentChar) { matching = false; break; }
                    buffer = buffer + currentChar;
                    j++;
                    
                }
                
                if (matching) {
                    
                    // Calculate the start and end positions
                    long long int end_pos = input.tellg();
                    long long int start_pos = end_pos - j;
                    
                    // Add the current token to the tokens array
                    output.push_back(Token(keyword_to_tokenname(i), buffer, start_pos, end_pos));
                    buffer = "";
                    
                    // We looked at too many chars I guess so we go back–– TO THE FUTURE
                    input.seekg(-1, input.cur);
                    
                    break;
                    
                } else {
                    
                    // Move the current 'cursor' back
                    input.seekg(-1 - j, input.cur);
                    buffer = "";
                    
                }
                
            }
            
            // If the character cant be matched, skip it!
            input.get();
            
        }
        
    }
    
    // Loop through all of the identifiers because keyword detection doesnt work right now
    // TODO: reorder the above tokenizers parts so that identifier scope and keywords don't interfere
    
    for (auto &out_token: output) {
        
        if (out_token.name != "IDENTIFIER") continue;
        
        for (auto keyword: keywords) {
            
            if (keyword == out_token.data) {
                
                out_token.name = keyword_to_tokenname(keyword);
                
            }
            
        }
        
    }
    
    
    return output;
    
}
