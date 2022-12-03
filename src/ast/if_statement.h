//
//  if_statement.h
//  cherrycake
//
//  Created by William McGonagle on 12/3/22.
//

#pragma once

#include "statement.h"
#include "boolean_expression.h"

namespace ast {

    struct IfStatement: Statement {
        
        BooleanExpression conditional;
        
        IfStatement() {
            
            type = "IfStatement";
            
        }
        
        IfStatement(int _start, int _end) {
            
            type = "IfStatement";
            start = _start;
            end = _end;
            
        }
        
        std::string print() {
            
            std::string str_start = std::to_string(start);
            std::string str_end = std::to_string(end);
            
            std::string str_conditional = conditional.print();
            
            return "{ \"type\": \"" + type + "\", \"conditional\": " + str_conditional + ", \"start\": " + str_start + ", \"end\": " + str_end + " }";
            
        }
        
    };

}
