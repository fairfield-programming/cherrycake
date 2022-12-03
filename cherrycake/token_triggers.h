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

#pragma once

// Struct for defining each scope
struct Scope {
    
    std::string name;
    
    std::string start;
    std::string end;
    
    std::string initiator;
    std::string conditional;
    
    bool uses_start;
    
    Scope(std::string _name, std::string a, std::string b, bool _uses_start) {
        
        name = _name;
        uses_start = _uses_start;
        
        if (_uses_start) {
            
            start = a;
            end = b;
            
        } else {
            
            initiator = a;
            conditional = b;
            
        }
        
    }
    
};

// Struct for defining each symbol
struct Symbol {
    
    std::string name;
    std::string data;
    
    Symbol(std::string _name, std::string _data) {
        
        name = _name;
        data = _data;
        
    }
    
};

// Define all posible keywords that the language can support
const std::string keywords[] = {
    // Defining Functions
    "func",
    
    // Conditional Logic Package
    "if",
    "else",
    "true",
    "false",

    // Looping Package
    "for",

    // Logical Flow Package
    "break",
    "continue",
    "in",

    // Null Data
    "null",

    // HTTP Keywords
    "manifest",
    "funnel",
    "get",
    "post",
    "put",
    "delete",
    "cached",
    "mined",

    // Data Types
    "int",
    "float",
    "bool",
    "string"
};

// Define all posible symbols that the language can support
const Symbol symbols[] = {
    Symbol("INCREASE_SCOPE", "{"),
    Symbol("DECREASE_SCOPE", "}"),
    Symbol("EQUALS", "=="),
    Symbol("GREATER_THAN_OR_EQUALS", ">="),
    Symbol("LESS_THAN_OR_EQUALS", "<="),
    Symbol("GREATER_THAN", ">"),
    Symbol("LESS_THAN", "<"),
    Symbol("SET_KEYWORD", "="),
    Symbol("START_PAREN", "("),
    Symbol("END_PAREN", ")"),
    Symbol("CHAIN", "."),
    Symbol("PARAM_SEPARATOR", ","),
    Symbol("LOGICAL_AND", "&&"),
    Symbol("LOGICAL_OR", "||"),
    Symbol("LOGICAL_XOR", "^^"),
    Symbol("ADD_OPERATOR", "+"),
    Symbol("SUB_OPERATOR", "-"),
    Symbol("DIV_OPERATOR", "/"),
    Symbol("MUL_OPERATOR", "*"),
    Symbol("MOD_OPERATOR", "%")
};

// Define all of the possible scopes in the programming language
const Scope scopes[] = {
    Scope("STRING", "\"", "\"", true),
    Scope("LINE_COMMENT", "#", "\n", true),
    Scope("IDENTIFIER", "[_a-zA-Z]", "[_a-zA-Z0-9]", false),
    Scope("NUMERICAL", "[0-9]", "[0-9\\.]", false),
    Scope("URL", "[\\~]", "[\\/:_\\-0-9a-zA-Z]", false),
};
