#ifndef H_COMMANDCD_H_EXISTS
#define H_COMMANDCD_H_EXISTS
#include "DisplayHandler.h"
#include "HistoryManager.h"
#include <vector>

// Imports
#include<string>
#include<list>

std::string getBaseDir() {
    char cwd[1024];
    if(getcwd(cwd, sizeof(cwd)) != NULL) {
        return std::string(cwd);   // Return the current directory as a string
    } else {
        return "Error: Unable to get current directory";
    }
}

// Gets the default directory of the program. This is used for the Recording of the Logfile.
const std::string basedir = getBaseDir();

// Enum
enum CDArgType {
    h, // Simple Help
    H, // Full Help
    l, // List directory history {included COULD be a numerical value}
    lN, // List the N last directories
    c, // clear directory history
    s, // remove duplicate paths in history
    i, // change to directory from history from line number {i}
    dir, // Change to directory
    NONE // NONE of the above, argument is a directory input
};

// Theint
class CommandCD {

    private:
        std::string rawInput;
        CDArgType argType;
        int index;
        DisplayHandler dh;  // Moved Objects here to prevent continuous calling (JM)
        HistoryManager hm;

        /**
         * @name clearData
         * @def Clears the data stored within this class object. This should be used
         * after the @ref{parseCommand(std::string)} method to ensure that the data
         * within memory has been removed.
        */
        void clearData();

    public:
    std::vector<std::string> args;

        /**
         * @constructor
         * @def Used for handling the CD command.
        */
        CommandCD();

        /**
         * @deconstructor
         * @def Removes data from memory
        */
        ~CommandCD();

        /**
         * @name getRawInput
         * @def gets the Raw input data that was put into the @ref{parseCommand(std::string)}
         * method.
        */
        std::string getRawInput();

        /**
         * @name getArg
         * @def Gets an argument from the input. Returns NULL if OutOfBounds.
         * @param value INT - argument to get.
        */
        std::string getArg(int index);

        /**
         * @name getArgType
         * @def Gets the type of argument that was used.
        */
        CDArgType getArgType();

        /**
         * @name isChangeDirectory
         * @def Returns whether the input is a directory and is changing
         * the directory.
        */
        bool isChangeDirectory();

        /**
         * @name parseCommand
         * @def Intakes a String of arguments that that the program will handle.
         * The arguments are parsed and the data is stored to be grabbed based on
         * what action to perform. The action is NOT performed within this method,
         * only determining what data the command is is done here.
         * @param input STRING - String of arguments for the CD command.
        */
        void parseCommand(std::string input);

            
        /**
         * @name implementCommand
         * @def This method is called after the @ref{parseCommand(std::string)} method to implement each argument.
        */
        void implementCommand();
        
}; 
#endif