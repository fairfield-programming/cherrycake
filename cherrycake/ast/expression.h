//
//  expression.h
//  cherrycake
//
//  Created by William McGonagle on 12/3/22.
//

#pragma once

#include <string>
#include <format>

namespace ast {

    struct Expression {
        
        std::string type;
        int start;
        int end;
        
        Expression() {
            
            type = "Expression";
            start = 0;
            end = 0;
            
        }
        
        Expression(int _start, int _end) {
            
            type = "Expression";
            start = _start;
            end = _end;
            
        }
        
        virtual std::string print() {
            
            std::string str_start = std::to_string(start);
            std::string str_end = std::to_string(end);
            
            return "{ \"type\": \"" + type + "\", \"start\": " + str_start + ", \"end\": " + str_end + " }";
            
        }
        
        virtual std::string beautify() {
            
            return "";
            
        }
    
    };

}
