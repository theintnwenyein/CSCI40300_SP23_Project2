#ifndef H_MODEHANDLER
#define H_MODEHANDLER

#include <iostream>
#include <string>
#include <vector>
#include <sstream> // Include for std::istringstream and std::ostringstream
#include <unistd.h> // For fork(), execvp(), getpid()
#include <sys/wait.h> // For waitpid()
#include "CommandCD.h" // Include the CommandCD header

class ModeHandler {
private:
    bool interactiveMode;

    void parseCommand(const std::string& commandLine, std::vector<std::string>& args) {
        std::istringstream iss(commandLine);
        std::string token;
        while (iss >> token) {
            args.push_back(token);
        }
    }

    void executeCommand(const std::vector<std::string>& args) {
        if (args.empty()) {
            return; // No command to execute
        }

        if (args[0] == "cd") {
            // Use CommandCD to handle cd command
            CommandCD cdCommand;
            std::string commandLine = join(args, " "); // Reconstruct command line, updated to use the vector directly
            cdCommand.parseCommand(commandLine);
            cdCommand.implementCommand();
        }
        else {
            // External command execution
            std::vector<char*> argv; // For execvp
            for (const auto& arg : args) {
                argv.push_back(const_cast<char*>(arg.c_str())); // Convert std::string to char*
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
                std::cerr << "Failed to execute command: " << args[0] << std::endl;
                _exit(1); // Exit child process
            }
        }
    }

public:
    ModeHandler(bool interactiveMode) : interactiveMode(interactiveMode) { }

    void run(const std::string& commandLine) {
        if (commandLine.empty()) {
            return; // If no command is provided, just return
        }

        std::vector<std::string> args;
        parseCommand(commandLine, args); // Parse the command line input into arguments

        // Execute parsed command
        executeCommand(args);
    }

    // Updated Utility function to directly accept a vector of strings
    std::string join(const std::vector<std::string>& parts, const std::string& separator) {
        std::ostringstream oss;
        for (size_t i = 0; i < parts.size(); ++i) {
            if (i > 0) {
                oss << separator;
            }
            oss << parts[i];
        }
        return oss.str();
    }
};

#endif
