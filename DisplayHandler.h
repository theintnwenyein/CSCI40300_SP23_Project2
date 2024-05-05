#ifndef H_DISPLAYHANDLER_H_EXISTS
#define H_DISPLAYHANDLER_H_EXISTS

// Imports
#include<string>
#include<iostream>


/**
 * @class
 * @name DisplayHandler
 * @author Josh Moore
 * @authors Theint Nwe Nyein
 * @def Contains methods that pertain to display information onto the terminal.
*/
class DisplayHandler {
    private:
        std::string simpleHelpMessage;
        std::string fullHelpMessage;
        
    protected:
    public:

        /**
         * @constructor
         * @def Handler for displaying text information
         * 
        */
        DisplayHandler();

        /**
         * @deconstructor
         * @def Removes and Deletes any data necessary after being killed by the program.
        */
        ~DisplayHandler();

        /**
         * @name getSimpleHelpMessage
         * @def Gets the simple help message for the CD command.
         * @return STRING - Simple Help Message
        */
        std::string getSimpleHelpMessage();

        /**
         * @name getFullHelpMessage
         * @def Gets the Full lengthy help message for the CD command.
         * @return STRING - Full Help Message
        */
        std::string getFullHelpMessage();

        /**
         * @name getCurrentDirectory
         * @def Gets the current working directory. This is used when the program is running
         * in interactive mode.
        */

        std::string getCurrentDirectory();
   
};

#endif


/*
Name - Theint Nwe Nyein
Date - 10/10/2021
Log: Deleted displaySimpleHelp() and displalyFullHelp() methods. The getters can be used instead.
*/