#include<string>
#include<iostream>
#include<unistd.h>
#include "DisplayHandler.h" 

DisplayHandler::DisplayHandler(){
    simpleHelpMessage = R"(Usage: cd [-h] [-H] [-l [{n}]] [-{n}] [-c] [-s] (DIR)
Change the current directory to DIR.
                  
Options:
-h          Display simple help message.
-H          Display full help message.
-l [{n}]    Display the history list of the current directories with serial numbers. With the optional N, it displays only the last N entries.
-{n}        Change the current directory to the n-th entry in the history list.
-c          Clean the directory history.
-s          Suppress the directory history by eliminating duplicated directories.  The order of the history must be maintained. The latest entry must be kept for same directories.)";

            fullHelpMessage = R"(Description: The cd command is used to change the current working directory in a shell environment. It allows for flexible navigation within the file system and includes additional features 
 beyond the typical cd commands found in Windows Command Prompt or Linux shells.
                    

Usage: cd [-h] [-H] [-l [{n}]] [-{n}] [-c] [-s] (DIR)
Change the current directory to DIR. The default DIR is the current directory so that it is identical to the pwd command in typical Linux shells.
                   
 Options:
-h, --help:
Display a simple help message describing the basic usage of the cd command.

-H, --full-help
Display a detailed help message explaining all available options and usage scenarios for the cd command.              
                            
-l [{n}], --list [{n}]
Display the history list of the current directories with serial numbers. 
If the optional N is provided, it displays only the last N entries from the history list.
For example: Display the last 5 entries from the directory history: cd -l 5
            
- {n} -- Go to nth directory
Change the current directory to the n-th entry in the history list.
For example: Change to the directory listed as the 3rd entry in the history: cd -3                            
                      
                      
-c, --clean-history
Clean the directory history, removing all entries from the history list.
                      
-s, --suppress-duplicates
Suppress the directory history by eliminating duplicated directories. 
The order of the history must be maintained, and only the latest entry must be kept for the same directories.)";
         
}

DisplayHandler::~DisplayHandler() { }   

std::string DisplayHandler::getSimpleHelpMessage(){
    return simpleHelpMessage;
}

std::string DisplayHandler::getFullHelpMessage(){
    return fullHelpMessage;
}

std::string DisplayHandler::getCurrentDirectory(){
    char cwd[1024];
    if(getcwd(cwd, sizeof(cwd)) != NULL) {
        return std::string(cwd);   // Return the current directory as a string
    } else {
        return "Error: Unable to get current directory";
    }
}   