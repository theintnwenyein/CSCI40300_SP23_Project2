/**
 * Date: 1 Febuary 2024
 * Assignment: Project 2
 * Description: Create a simple Bash program that handles and works similar
 * to that of a Bash Shell
 * LOG:
 *  1 Febuary 2024 (JM):
 *  - Added Generic files for Project use.
 *  - Edited Description for Project.
 *  4 Febuary 2024 (JM):
 *  - Added classes, methods and comments on what each method does.
 *  7 Febuary 2024 (JM):
 *  - Added methods for conversion of arguments and interactive mode checking.
 *  - Changed file types to header files rather than C++ files.
 *  - Changed Documention for 'run' method within ModeHandler.
 *  13 Febuary 2024 (JM):
 *  - Added instructions to README
 *  18 January 2024 (JM):
 *  - Added check for which mode user enters in.
*/

// Imports
#include <iostream>
#include <string>

#include <algorithm>
#include <cctype>

#include "ModeHandler.cpp"
#include "DisplayHandler.cpp"
#include "CommandCD.cpp"
#include "HistoryManager.cpp"

// Function Pre-cache
bool checkInteractive(std::string);
std::string convert(int, char**);

/**
 * @name main
 * @author Josh Moore
 * @authors Maria Colon, Leo Goldstein, Theint Nwe Nyein
 * @def Main Function of program.
 * @return 0
*/
int main(int argc, char** argv) {
    bool mode = true;
    DisplayHandler* dHandler = new DisplayHandler();

    std::string value(argc >= 2 ? argv[1] : "");
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c){return std::tolower(c); });

    if(argc < 2)
        std::cout << "Entering interactive mode..." << std::endl;
    else if(value.substr(0,2) != "cd") {
        std::cout << "Batch Mode" << std::endl;
        mode = false;
    }

    ModeHandler* mHandler = new ModeHandler(mode);

    if(mode) {
        std::string uInput = convert(argc, argv);

        if(uInput == "") {
            std::cout << dHandler->getCurrentDirectory() << " $ ";
            std::getline(std::cin, uInput);
        }

        while(true) {
            if(uInput == "exit")
                break;
            else if(uInput.substr(0,2) != "cd")
                std::cout << "Error, that command is not supported." << std::endl;
            else 
                mHandler->run(uInput);

            std::cout << dHandler->getCurrentDirectory() << " $ ";
            std::getline(std::cin, uInput);
        }
    } else {
        mHandler->run(convert(argc, argv));
    }
    
    return 0;
}

// Functions

/**
 * @name isInteractive
 * @def Determines if the given command is using the internal commands
 * Stored within this program. Returns TRUE if using an internal command.
 * @param input STRING - arguments of the program
 * @return TRUE - If input is an internal command.
*/
bool checkInteractive(std::string input) {
    return input.substr(0,2) == "cd";
}

std::string convert(int argc, char** argv) {
    std::string ret = "";

    for(int i = 1; i < argc; i++)
        ret += (std::string(argv[i]) + " ");


    return ret.substr(0, ret.length() - 1);
}
