//
//  expression.h
//  cherrycake
//
//  Created by William McGonagle on 12/3/22.
//

#pragma once

#include <string>

#include "expression.h"

namespace ast
{

    struct BooleanExpression : Expression
    {

        std::string type;
        int start;
        int end;

        BooleanExpression()
        {

            type = "BooleanExpression";
            start = 0;
            end = 0;
        }

        BooleanExpression(int _start, int _end)
        {

            type = "BooleanExpression";
            start = _start;
            end = _end;
        }

        std::string print()
        {

            std::string str_start = std::to_string(start);
            std::string str_end = std::to_string(end);

            return "{ \"type\": \"" + type + "\", \"start\": " + str_start + ", \"end\": " + str_end + " }";
        }

        std::string beautify()
        {

            return "";
        }
    };

}
