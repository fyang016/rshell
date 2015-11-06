COMPILE_DEFAULT = g++ -Wall -Werror -ansi -pedantic
TWO_CPP = rshell.cpp terminal.cpp

all:
    rm -rf bin
    mkdir -p bin
    $(COMPILE_DEFAULT) $(TWO_CPP)

rshell:
    rm -rf bin
    mkdir -p bin
    $(COMPILE_DEFAULT) $(TWO_CPP)