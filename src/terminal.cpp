#include "terminal.h"
#include <iostream>
#include <boost/tokenizer.hpp>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <typeinfo>


using namespace std;
using namespace boost;

Terminal::Terminal(){
	this->prompt = '$';
}

//For testing purposes
void Terminal::test(){
	cout << "Hello There" << endl;
}

//Convert given string to its equivalent char *
char * toChar(string  str){
	return const_cast<char*>((str).c_str());
}

//Throw aways comments
string Terminal::throwAwayComments(std::string str){
	char_separator<char> sep("#");
	tokenizer<char_separator<char> > tok(str, sep);
 	return *(tok.begin());
	
}

//Run individual commands returns int of results
int Terminal::exe(string command){
	
	//Separate command by spaces and save to a vector
	char_separator<char> space(" ");
	tokenizer<char_separator<char> > tok(command, space);
	int size = 0;
	vector<string> arguments;
	
	for(tokenizer<char_separator<char> >::iterator beg=tok.begin(); beg!=tok.end();++beg){
		size++;
		arguments.push_back(*beg);
		//cout << "Argument " << size << ": " << *beg << endl;
	}
	
	//Convert vector to char * for the execvp function
	char ** args;
	args = new char*[size + 1]; //+1 to make space for null termination
	args[size] = NULL; //Last item must be empty to indicate end of list
	
	for(int i = 0; i < size; i++){
		args[i] = const_cast<char*>((arguments[i]).c_str()); //Converting string to Char
	    //args[i] = toChar(arguments[i]);
	}
	
	pid_t c_pid, pid;
	int status;
	c_pid = fork();
	if(c_pid < 0){
		perror("ERROR: Fork Failed");
		exit(1);
		return -1;
	}
	else if(c_pid==0){
		execvp(args[0], args);
		perror("execve failed");
		delete args;
		exit(1);
	}
	else if (c_pid > 0){
		if((pid = wait(&status)) < 0){
			perror("wait");
			exit(1);
		}
		//cout << "EXE status: " << status << endl;
		delete args;
		return status;
	}
	
	return 1;
}

//Run the terminal application
void Terminal::run(){
	int exit = 0;
	while (!exit){
		char *loginName = getlogin();
		char hostName[128];
		gethostname(hostName, sizeof hostName);
		
		cout << loginName << '@' << hostName << this->prompt << " ";
		
		getline(cin, input);
		
		string noComments = this->throwAwayComments(input);
		cout << noComments << endl;
	    //Separat string into its induvidual parts and compare boolean values
	    
	    //Separate string by ; first
		char_separator<char> separatorSemiColon(";");
		tokenizer<char_separator<char> > tok(noComments, separatorSemiColon);
		for(tokenizer<char_separator<char> >::iterator beg1=tok.begin(); beg1!=tok.end();++beg1){
			
			//Separate strings by || first do to presidance
			char_separator<char> separatorAnd("&&");
			tokenizer<char_separator<char> > tok(*beg1, separatorAnd);
			
			int lastOperation = 0; //zero for OR one for AND
			int result = 0;
			for(tokenizer<char_separator<char> >::iterator beg2=tok.begin(); beg2!=tok.end();++beg2){
				
				//Separate Strings by && and execute the commands
				char_separator<char> separatorAnd("||");
				tokenizer<char_separator<char> > tok(*beg2, separatorAnd);
				
				for(tokenizer<char_separator<char> >::iterator beg3=tok.begin(); beg3!=tok.end();++beg3){
					
					//If the result of the exe function is zero it means
					//that the function executed correctly 0 errors
					if(lastOperation == 0 && result == 0){
						result = (this->exe(*beg3) == 0);
					}
					else if(lastOperation == 1 && result == 1){
						result = (this->exe(*beg3) == 0);
					}
					lastOperation = 0;
				}
				lastOperation = 1;
			}
	 	}
	}	
}

void Terminal::printValues(){
	for (unsigned int i = 0; i < values.size(); i++){
		cout << "Value " << i << ": " << *values[i] << endl;
	}
}
