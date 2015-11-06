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

//Run individual commands returns int of results
int Terminal::exe(string command){
	
	// char * argss[splice.size() + 1];
	// argss[splice.size()] = NULL;
	// for(unsigned int i = 0; i < splice.size(); i++){
	// 	char * tmp = new char[(*splice[i]).length()+1];
	// 	strcpy(tmp, (*splice[i]).c_str());
	// 	argss[i] = tmp;
	// }
	
	pid_t c_pid, pid;
	int status;
	c_pid = fork();
	if(c_pid < 0){
		perror("ERROR: Fork Failed");
		exit(1);
	}
	else if(c_pid==0){
		//cout << "EXE Child" << endl;
	//	int result = execvp(argss[0], argss);
		//cout << "EXE Result: " << result << endl;
		//cout << "EXE Executed task" << endl;
		perror("execve failed");
		exit(1);
	}
	else if (c_pid > 0){
		//cout << "EXE parent" << endl;
		if((pid = wait(&status)) < 0){
			//cout << "EXE Error" << endl;
			perror("wait");
			exit(1);
		}
		//cout << "EXE pid: " << pid << endl;
		//cout << "EXE status: " << status << endl;
		return status;
	}
	// for(int i = 0; i < (splice.size() + 1); i++){
	// 	delete argss[i];
	// }
	return 1;

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

//Run the terminal application
void Terminal::run(){
	int exit = 0;
	while (!exit){
		cout << this->prompt << " ";
		
		getline(cin, input);
		
		string noComments = this->throwAwayComments(input);
		cout << noComments << endl;
	    //Separat string into its induvidual parts and compare boolean values
	    
	    //Separate string by ; first
		char_separator<char> separatorSemiColon(";");
		tokenizer<char_separator<char> > tok(noComments, separatorSemiColon);
		for(tokenizer<char_separator<char> >::iterator beg1=tok.begin(); beg1!=tok.end();++beg1){
			cout << "Semi Colon-------------------------------- " << endl;;
			//Separate strings by || first do to presidance
			char_separator<char> separatorAnd("||");
			tokenizer<char_separator<char> > tok(*beg1, separatorAnd);
			
			for(tokenizer<char_separator<char> >::iterator beg2=tok.begin(); beg2!=tok.end();++beg2){
				cout << "---------AND Operator---------------------" << endl;
				//Separate Strings by && and execute the commands
				char_separator<char> separatorAnd("&&");
				tokenizer<char_separator<char> > tok(*beg2, separatorAnd);
				
				for(tokenizer<char_separator<char> >::iterator beg3=tok.begin(); beg3!=tok.end();++beg3){
					cout << "OR Operator: " << *beg3 << endl;
					this->exe(*beg3);
				}
			}
	 	}
	}	
}

void Terminal::printValues(){
	for (unsigned int i = 0; i < values.size(); i++){
		cout << "Value " << i << ": " << *values[i] << endl;
	}
}
