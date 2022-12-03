//
//  console.h
//  cherrycake
//
//  Created by William McGonagle on 11/30/22.
//

#include <iostream>
#include <string>
#include <fstream>

#pragma once

namespace console {

    struct CommandArg {
      
        std::string arg_name;
        std::string arg_desc;
        std::string example;
        bool optional;
        
        CommandArg(std::string _arg_name, std::string _arg_desc, std::string _example, bool _optional) {
            
            arg_name = _arg_name;
            arg_desc = _arg_desc;
            example = _example;
            optional = _optional;
            
        }
        
        CommandArg(std::string _arg_name, std::string _arg_desc, std::string _example) {
            
            arg_name = _arg_name;
            arg_desc = _arg_desc;
            example = _example;
            optional = true;
            
        }
        
    };

    struct Command {
        
        std::string name;
        std::string title;
        std::string description;
        std::vector<CommandArg> args;
        
        Command(std::string _name, std::string _title, std::string _description, std::vector<CommandArg> _args) {
            
            name = _name;
            title = _title;
            description = _description;
            args = _args;
            
        }
        
        Command(std::string _name, std::string _description, std::vector<CommandArg> _args) {
            
            name = _name;
            title = _name;
            description = _description;
            args = _args;
            
        }
        
        Command(std::string _name, std::vector<CommandArg> _args) {
            
            name = _name;
            title = _name;
            description = "This is the default description for the " + _name + " command.";
            args = _args;
            
        }
        
    };

    const Command commands[] = {
        Command("help", "The help command stores information about how the cherrycake cli works.", {
            CommandArg("command", "Including this argument displays the documentation for the command with a name matching the argument.", "build")
        }),
        Command("run", "The run command executes the code, in interpretted mode, of the file specified as the first argument.", {
            CommandArg("file", "This argument is required and used so that the cherrycake cli can know where your code is stored.", "example.chry", false)
        })
    };

    inline int log(std::string message) {
        
        // Print the message
        std::cout << message << std::endl;
        
        // Shouldn't fail
        return 0;
        
    }

    inline int error(std::string message) {
        
        // Print the message
        std::cout << "Error: " << message << std::endl;
        
        // Shouldn't fail
        return 0;
        
    }

    inline int help(std::string command) {
        
        for (auto i: commands) {
            
            if (i.name == command) {
                
                log(i.title);
                log(i.description);
                return 0;
                
            }
            
        }
        
        return 0;
        
    }

    inline int help() {
        
        log("Commands:");
        
        for (auto i: commands) {
            
            // Check if name is the same as the title
            if (i.name == i.title) {
                
                // If so, don't include title in parenthesis
                log("   " + i.name);
                
            } else {
                
                // If different title and name, include title in parenthesis
                log("   " + i.name + "(" + i.title + ")");
                
            }
            
            log("     " + i.description);
            log("");
            
        }
        
        return 0;
        
    }

    inline int token(std::string message, Token token, std::ifstream& target_file, std::string file_path) {
        
        const long long int file_start = target_file.tellg();
        
        int start_line = 0;
        int start_column = 0;
        
        target_file.clear();
        target_file.seekg(0, std::ios::beg);
    
        int i = 0;
        while (i < token.start) {
            
            if (target_file.get() == '\n') {
            
                start_line++;
                start_column = 0;
                
            } else {
                
                start_column++;
                
            }
            
            i++;
            
        }
        
        int end_line = start_line;
        int end_column = start_column;
        
        while (i < token.end) {
        
            if (target_file.get() == '\n') {
            
                end_line++;
                end_column = 0;
                
            } else {
                
                end_column++;
                
            }
            
            i++;
            
        }
        
        std::cout << file_path << ":" << start_line << "." << start_column << "-" << end_line << "." << end_column << ": " << message << std::endl;
        
        target_file.seekg(file_start, std::ios::beg);
        
        return 0;
        
    }

}
