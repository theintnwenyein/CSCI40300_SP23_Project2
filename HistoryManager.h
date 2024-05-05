#ifndef H_HISTORYMANAGER
#define H_HISTORYMANAGER

// Imports
#include<iostream>
#include<string>
#include<fstream>
#include<list>
#include <vector>
#include <algorithm>
#include <unistd.h>

/*
Log 
Date: 2/6/24
@author Maria colon 
tired to add functionality to the Hisotry maneger, for some reason i am sturguling to write to the 
file. next i want to tackel the save method still working out how i will do that. note to self (you might need input form console). 
Date: 2/8/24
@author maria colon 
added fucntionality to save method, i want to note that i have yet to test both method i will do this next time and fix any bugs befor moving on. 
before that is done i will do adddirectory. 
*/
/**
 * @author Maria Colon
*/

std::string setBaseDir() {
    char cwd[1024];
    if(getcwd(cwd, sizeof(cwd)) != NULL) {
        return std::string(cwd);   // Return the current directory as a string
    } else {
        return "Error: Unable to get current directory";
    }
}

// Gets the default directory of the program. This is used for the Recording of the Logfile.
const std::string baseDir = setBaseDir();

class HistoryManager {
    private:
        std::string dir;
        std::vector<std::string> directory;
        int startPoint; 
        int value;
    protected:
    public:
    /**
     * @name HistoryManeger
     * @def  writes list of directories to the directory log file. 
    */
        HistoryManager();  

        ~HistoryManager();

        /**
         * @name getHistory
         * @def Gets the full list of directories this program has handled when
         * the user changed directories. This does not include the user changing
         * the directory outside of the use of this program.
        */
        std::list<std::string> getHistory();

        void debug();

        /**
         * @name getHistory
         * @def Gets a list of the directories the user has changed to, but limits
         * the display of the directories based on where to beginning display. (ie.
         * only show the directories start at and after the given value).
         * @param startPoint INT - Starting point in the history list
        */
        std::list<std::string> getHistory(int startPoint);


        /**
         * @name setDirectory
         * @def Sets the directory at the given line number. This will overwrite the
         * directory at the given line number.
         * @param lineNumber int - Line number to set the directory at
        */
        void setDirectory(int lineNumber);

        /**
         * @name clear
         * @def Clears the history log, removing all stored directories.
        */
        void clear();

        /**
         * @name removeDuplicates
         * @def Removes any duplicate directories found within the log. The NEWEST
         * found directory is kept while all older directories are removed.
        */
        void removeDuplicates();

        /**
         * @name addDirectory
         * @def Adds a directory to the log at the end (last). This does not care whether
         * the directory already exists within the log.
         * @param dir STRING - Directory to add to log
        */
        void addDirectory(std::string dir);

        /**
         * @name save
         * @def This method is called when the data needs to be saved to the log file.
        */
         void save();
};

#endif