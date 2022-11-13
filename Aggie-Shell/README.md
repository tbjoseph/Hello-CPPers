# Aggie Shell

This project was an exercise in implementing a Linux shell through C++. The main file is shell.cpp.

Features:
- Run Linux commands as child processes
- Inter-process communication
- Navigate through the file system
- File input/out redirection

The shell has the ability to function almost as well as BASH. It runs Linux commands that sit as executables in the system through a a call to execvp().

To run the shell: after compiling with make, run the program with ./shell. Then a prompt will be printed, and you may enter commands as you would with a normal BASH shell.
