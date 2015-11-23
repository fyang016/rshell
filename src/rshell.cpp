
//#include <uninstd.h>
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include "terminal.h"

using namespace std;

int main(int argc, char *argv[]){
	Terminal terminal;
	terminal.run();
	// debug
	// cout << "Done" << endl;

	return 0;
}
