#ifndef H_MODEHANDLER
#define H_MODEHANDLER

// Imports
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h> // For fork(), execvp(), getpid()
#include <sys/wait.h> // For waitpid()
#include <fstream> // For file operations


class ModeHandler {
private:
    bool interactiveMode;
    /**
     * @name isFirstLinePath
     * @def Checks if the given string starts with the symbols '#!'. If this
     * does, then the given file data is a script file and needs to use the
     * engine of the path.
     * @param line STRING - First line of file
    */
    bool isFirstLinePath(std::string line) {
        return !line.empty() && line.substr(0, 2) == "#!";
    }

    /**
     * @name isPathBeta
     * @def Determines if the given line (from the above method) points to
     * the Beta program engine. If so, then this returns TRUE that this
     * program will handle the execution of the commands found within
     * the script file.
     * @param line STRING - Line to check if the engine is beta
    */
    bool isPathBeta(std::string line) {
        // beta is the path to the beta engine
        return line.find("beta") != std::string::npos;
    }

    /**
     * @name isInInteractiveMode
     * @def Returns whether the program is running in an interactive mode or not. This
     * is used to determine whether the program will shutdown after execution, or continue
     * after command(s) are completed.
    */
    bool isInInterativeMode() {
        return interactiveMode;
    }

    void parseCommand(const std::string& command, std::vector<std::string>& args) {
        std::istringstream iss(command);
        std::string token;
        while (iss >> token) {
            args.push_back(token);
        }
    }

    void executeScript(const std::string& filePath) {
        std::ifstream file(filePath);
        std::string line;
        if (file.is_open()) {
            while (getline(file, line)) {
                if (!line.empty() && line[0] != '#') { // Skip comments
                    run(line);
                }
            }
            file.close();
        }
        else {
            std::cerr << "Unable to open file: " << filePath << std::endl;
        }
    }
 protected:
     void executeCommand(const std::string& command) {
         std::vector<std::string> args;
         parseCommand(command, args);

         if (args.empty()) {
             return; // No command to execute
         }
         std::vector<char*> argv; // For execvp
         for (auto& arg : args) {
             argv.push_back(&arg.front()); // Convert std::string to char*
         }
         argv.push_back(nullptr); // NULL-terminate the argument list

         pid_t pid = fork();
         if (pid == -1) {
             std::cerr << "Failed to fork" << std::endl;
         }
         else if (pid > 0) {
             // Parent process
             int status;
             waitpid(pid, &status, 0); // Wait for the child process to finish
         }
         else {
             // Child process
             execvp(argv[0], argv.data());
             // If execvp returns, it means it failed
             std::cerr << "Failed to execute command: " << command << std::endl;
             _exit(1); // Exit child process
         }
     }
public:

    ModeHandler(bool interativeMode) : interactiveMode(interactiveMode) { }

    /**
     * @name run
     * @def Takes the arguments of the input and runs the command after converting the given
     * argument(s) into a runnable termimal command. The input only contains the arguments, meaning
     * translating the input into the correct action is needed. Whether the program is using
     * interactive mode or Batch Mode is determined in the main and passed as a Boolean value within the Constructor.
     * NOTE: This method should use the fork() and exec() methods when performing the action(s).
     * @param input STRING - User input from keyboard
     * 
     * NOTE: Interactive mode arguments
     * @example cd -l 5
     * @example cd -10
     * @example cd -H
     * 
     * NOTE: Batch Mode Arguments
     * @example < scriptFile.psh
     * @example scriptfile.psh
    */

   // NOTE: Since converting to string is unnecessary (my fault), suggest to changing parameters
   // to: (int argc, char** argv) - argument count, char double-array
    void run(std::string input) {
        if (isFirstLinePath(input)) {
            executeScript(input);
        }
        else {
            executeCommand(input);
        }
    }
};

#endif

