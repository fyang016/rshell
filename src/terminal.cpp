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
	this->input = "";
}

//For testing purposes
void Terminal::test(){
	cout << "Hello There" << endl;
}

//Convert given string to its equivalent char *
char * toChar(string  str){
	return const_cast<char*>((str).c_str());
}

//Throw aways comments by resizing the string
string Terminal::throwAwayComments(std::string input){
	// char_separator<char> sep("#");
	// tokenizer<char_separator<char> > tok(str, sep);
	
	for (unsigned int i = 0; i < input.size(); ++i){
		if (input.at(i) == '#'){
			// resize to cut off before the '#' sign
			input.resize(i);
		}
	}
 	return input;
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
	
	//Check for the exit command
	if(arguments[0] == "exit"){
		exit(0);
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
		perror("execvp failed");
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

// Concept: If there are '|' or '&' symbols that are not in pairs, call error
int Terminal::bugSearch(string str){
	int consecutiveAmpersand = 0;
	int consecutiveOr = 0;
	int most_consecutiveAmpersand = 0;
	int most_consecutiveOr = 0;
	
	for(unsigned int i = 0; i < str.size(); i++){
		
		//Too many ampersand's
		if(str[i] == '&'){
			consecutiveAmpersand++;
			if(consecutiveAmpersand > most_consecutiveAmpersand){
				most_consecutiveAmpersand = consecutiveAmpersand;
			}
		}
		else{
			if(consecutiveAmpersand > most_consecutiveAmpersand){
				most_consecutiveAmpersand = consecutiveAmpersand;
			}
			consecutiveAmpersand = 0;
		}
		
		//Too many OR's
		if(str[i] == '|'){
			consecutiveOr++;
			if(consecutiveOr > most_consecutiveOr){
				most_consecutiveOr = consecutiveOr;
			}
		}
		else{
			if(consecutiveOr > most_consecutiveOr){
				most_consecutiveOr = consecutiveOr;
			}
			consecutiveOr = 0;
		}
		
		if(most_consecutiveOr > 2 || most_consecutiveAmpersand > 2){
			return 1;
		}
	}
	
	return 0;
}

//Run the terminal application
void Terminal::run(){
	int exit = 0;
	
	// Extra credit part: store the login name and host name to output later
	char *loginName = getlogin();
	char hostName[128];
	gethostname(hostName, sizeof hostName);
	
	while (!exit){
		
		input = ""; //Erase the input4
		string noComments;
		while(input == ""){
			cout << loginName << '@' << hostName << this->prompt << " ";
			getline(cin, input);
			noComments =  this->throwAwayComments(input);
			input = noComments;
			if(bugSearch(input)){
				cout << "Bug found in input" << endl;
				input = "";
			}
		}
		
		
	    
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
						if(!result){
							cout << "Error executing: " << *beg3 << endl;
						}
					}
					else if(lastOperation == 1 && result == 1){
						result = (this->exe(*beg3) == 0);
						if(!result){
							cout << "Error executing: " << *beg3 << endl;
						}
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
