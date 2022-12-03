//
//  lexer.h
//  cherrycake
//
//  Created by William McGonagle on 12/2/22.
//

#pragma once

#include "ast/ast.h"
#include <vector>
#include "tokenizer.h"

namespace lexer
{

    inline std::vector<ast::Statement *> ast_from_tokens(std::vector<Token> tokens)
    {

        std::vector<ast::Statement *> output;

        output.push_back(new ast::IfStatement());
        output.push_back(new ast::Statement());

        return output;
    }

    inline std::string print_from_ast(std::vector<ast::Statement *> input)
    {

        std::string output = "[";

        for (auto i : input)
        {

            output += i->print() + ", ";
        }

        // remove trailing comma
        output.pop_back();
        output.pop_back();
        output += "]";

        return output;
    }

    inline std::string beautify_from_ast(std::vector<ast::Statement> input)
    {

        std::string output;

        for (auto i : input)
        {

            output += i.beautify();
        }

        return output;
    }

}
