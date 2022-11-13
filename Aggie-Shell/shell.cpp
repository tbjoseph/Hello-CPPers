#include <iostream>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctime>

#include <vector>
#include <string>
#include <cstring>
#include <fcntl.h>

#include "Tokenizer.h"

// all the basic colours for a shell prompt
#define RED     "\033[1;31m"
#define GREEN	"\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE	"\033[1;34m"
#define WHITE	"\033[1;37m"
#define NC      "\033[0m"

using namespace std;

int main () {
    char oldPwd[255];
    getcwd(oldPwd, 255); //old directory
    vector<int> bg; //vector of background process IDs
    int stdin2 = dup(0); //save stdin contents

    for (;;) {
        
        // need date/time, username, and absolute path to current dir
        time_t now = time(0);
        char* dt = ctime(&now);
        char time[16];
        memcpy(time, &dt[4], 15); //date/time
        string login = getenv("USER"); //username
        char pwd[255];
        getcwd(pwd, 255); //absolute path to current dir

        cout << YELLOW << time << " " << login << ":" << pwd << "$" << NC << " ";
        
        // get command from user
        string input;
        getline(cin, input);

        for (size_t i = 0; i < bg.size(); i++) waitpid(bg.at(i), NULL, WNOHANG); //Ensure no zombie processes

        if (input == "exit") {  // print exit message and break out of infinite loop
            cout << RED << "Now exiting shell..." << endl << "Goodbye" << NC << endl;
            break;
        }

        // get tokenized commands from user input
        Tokenizer tknr(input);
        if (tknr.hasError()) {  // continue to next prompt if input had an error
            continue;
        }

        auto cd = tknr.commands.at(0)->args;
        if (cd.at(0) == "cd") {
            if (cd.at(1) == "-")
            {
                char temp[255];
                getcwd(temp, 255);
                chdir(oldPwd);
                memcpy(oldPwd, temp, 254); //old dir is now the dir in temp
            }
            else {
                char temp[255];
                memcpy(temp, oldPwd, 254); //temp is now the dir in old dir
                getcwd(oldPwd, 255); //put current into old directory
                if (chdir(cd.at(1).c_str()) == -1) memcpy(oldPwd, temp, 254); //old dir is now the dir in temp (upon failure of chdir)
            }
            continue;
        }
        

        // // print out every command token-by-token on individual lines
        // // prints to cerr to avoid influencing autograder
        // for (auto cmd : tknr.commands) {
        //     for (auto str : cmd->args) {
        //         cerr << "|" << str << "| ";
        //     }
        //     if (cmd->hasInput()) {
        //         cerr << "in< " << cmd->in_file << " ";
        //     }
        //     if (cmd->hasOutput()) {
        //         cerr << "out> " << cmd->out_file << " ";
        //     }
        //     cerr << endl;
        // }

        for (size_t i = 0; i < tknr.commands.size(); i++) {

            auto currCommand = tknr.commands.at(i);

            // Create pipe
            int fd[2];
            pipe(fd);

            // fork to create child
            pid_t pid = fork();
            if (pid < 0) {  // error check
                perror("fork");
                exit(2);
            }

            if (pid == 0) {  // if child, exec to run command
                //redirect output to write end of pipe
                if (i < tknr.commands.size() - 1)
                {
                    dup2(fd[1], STDOUT_FILENO);
                    close(fd[0]);
                }
                
                char** args = new char*[currCommand->args.size()];
                    
                for (size_t j = 0; j < currCommand->args.size(); j++) {
                    args[j] = (char*)(currCommand->args.at(j).c_str());
                }

                if (currCommand->hasInput())
                {
                    int fd = open(currCommand->in_file.c_str(), O_RDONLY);
                    if (fd == -1) {
                        fd = open(currCommand->in_file.c_str(), O_RDONLY, S_IRWXU);
                    }

                    dup2(fd, STDIN_FILENO);
                }
                
                if (currCommand->hasOutput())
                {
                    int fd = open(currCommand->out_file.c_str(), O_WRONLY);
                    if (fd == -1) {
                        fd = open(currCommand->out_file.c_str(), O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU);
                        if (fd == -1) cout << "L" << endl;
                    }
                    
                    dup2(fd, STDOUT_FILENO);
                }

                if (execvp(args[0], args) < 0) {  // error check
                    perror("execvp");
                    exit(2);
                }

                delete[] args;
                //return 0;
            }
            else {  // if parent, wait for child to finish
                dup2(fd[0], STDIN_FILENO);
                // Close the write end of the pipe on the child side.
                close(fd[1]);
                
                if (currCommand->isBackground()) bg.push_back(pid);

                else {
                    int status = 0;
                    waitpid(pid, &status, 0);
                    if (status > 1) {  // exit if child didn't exec properly
                        exit(status);
                    }
                }
            }

        }
        dup2(stdin2, STDIN_FILENO); //restore stdin
    }
}
