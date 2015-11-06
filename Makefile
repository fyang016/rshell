all:
    rm -rf bin
    mkdir -p bin
    g++ -Wall -Werror -ansi -pedantic ./src/rshell.cpp ./src/terminal.cpp -o ./bin/rshell

rshell:
    rm -rf bin
    mkdir -p bin
    g++ -Wall -Werror -ansi -pedantic ./src/rshell.cpp ./src/terminal.cpp -o ./bin/rshell