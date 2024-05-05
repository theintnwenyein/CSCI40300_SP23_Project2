#include "DisplayHandler.h"
#include "CommandCD.h"
#include "HistoryManager.h" 
#include<string>
#include<list>
#include<sstream>
#include <unistd.h>

// Added header for changing directory
#include <unistd.h>

CommandCD::CommandCD() {
    argType = NONE;
    rawInput = "";
}   

CommandCD::~CommandCD() { }  

void CommandCD::clearData() {
    rawInput.clear();
    args.clear();
    argType = NONE;
}

std::string CommandCD::getRawInput() {
    return rawInput;
}

CDArgType CommandCD::getArgType() {
    return argType;
}

std::string CommandCD::getArg(int index){
    if (index >= 0 && index < args.size()) {
            return args[index];
        }
        else{
            return NULL;
        }
}

bool CommandCD::isChangeDirectory() {
    return argType == i;
}   

void CommandCD::parseCommand(std::string rawInput){
    clearData();
    //rawInput = getRawInput();                         // NOTE (JM): This line causes a bug, Fixed below.
    CommandCD::rawInput = rawInput;         // The CommandCD::rawInput never has anything stored, the parameter 'rawInput' is set to "" and thus doesn't run anything.

    #include <sstream> // Include the necessary header file

    std::string modifiedInput = rawInput.substr(rawInput.find(' ') + 1);

    std::istringstream iss(modifiedInput);
    std::string arg;
    while(iss >> arg){ 
            
        if(arg == "-h"){
            argType = h;
            args.push_back(arg);
        }
        else if(arg == "-H"){
            argType = H;
            args.push_back(arg);
        }
        else if(arg == "-l"){
                argType = l;
                args.push_back(arg);
                // Check if there's an optional number after -l
                if (iss >> arg) {
                    try {
                        int n = std::stoi(arg);
                        argType = lN;
                        args.push_back(std::to_string(n));
                    } catch (const std::invalid_argument&) {
                        // Invalid argument after "-l"
                        argType = NONE;
                    }
                }
            }
        else if(arg == "-c"){
            argType = c;
            args.push_back(arg);
        }
        else if(arg == "-s"){
            argType = s;
            args.push_back(arg);
        }
        
        else if (arg.substr(0, 1) == "-") {
            // Handle -{n} where n is a positive integer
            try {
                int n = std::stoi(arg.substr(1));
                if (n >= 0) {
                    argType = i; // Change to directory from history at line number n
                    args.push_back(std::to_string(n));
                } else {
                    argType = NONE; // Invalid negative integer
                }
            } catch (const std::invalid_argument&) {
                // Invalid argument after "-"
                argType = NONE;
            }
        }
        else if(arg.substr(0,1) != "-"){
            argType = dir;
            args.push_back(arg);    
        }
        else{
            argType = NONE;
        }
    }
}

void CommandCD::implementCommand(){
    // Changed location of objects (JM)
    //DisplayHandler dh;
    //HistoryManager hm;
        if(getArgType() == h){
            std::cout << dh.getSimpleHelpMessage() << std::endl;
        }
        else if(getArgType() == H){
            std::cout << dh.getFullHelpMessage() << std::endl;
        }
        else if(getArgType() == l){
            std::cout << "List of Directories: " << std::endl;
            for (auto dir : hm.getHistory()) {
                std::cout << dir << " " << std::endl;
            }
            std::cout << std::endl;
        }
        else if(getArgType() == lN){
            std::cout << "List of Directories: " << std::endl;
            for (auto dir : hm.getHistory(std::stoi(args[1]))) {
                std::cout << dir << " " << std::endl;
            }
            std::cout << std::endl;
        }
        else if(getArgType() == c){
            hm.clear(); 
            std::cout << "Directory History Cleared" << std::endl;
        }
        else if(getArgType() == s){
            hm.removeDuplicates();  
            std::cout << "Directory History Suppressed" << std::endl;
        }
        else if(getArgType() == i){
            hm.setDirectory(std::stoi(args[0]));
            std::cout << "Change to directory from history at line number: " << args[0]<< std::endl;
        }
        else if(getArgType() == c){
            hm.clear(); 
            std::cout << "Directory History Cleared" << std::endl;
        }
        else if(getArgType() == s){
            hm.removeDuplicates();  
            std::cout << "Directory History Suppressed" << std::endl;
        }
        else if(getArgType() == dir){
            //hm.setDirectory(std::stoi(args[1]));
            if(args[0] == "cd")
                chdir(basedir.c_str());
            else
                chdir(args[0].c_str());                // Altered method to change directory based on user input of directory (JM)
            hm.addDirectory(dh.getCurrentDirectory());
            hm.save();
        }
        else{
            std::cout << "Invalid Argument" << std::endl;
        }
}
       
