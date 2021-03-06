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
#include "stat.cpp"


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
		if(args[0][0] == 't' && args[0][1] == 'e' && args[0][2] == 's' && args[0][3] == 't' ){
			exit(testWordHelper(command));
		}
		else if(args[0][0] == '['){
			exit(testBracketHelper(command));
		}
		
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

vector<string> Terminal::vectorizeParentheses(string str){
	//tested for : (echo A || echo B && echo C) && echo D && echo e
	int check_for_operation_behind = 0;
	vector<string> list;
	char_separator<char> separatorSemiColon("()","()",boost::keep_empty_tokens);
	tokenizer<char_separator<char> > tok(str, separatorSemiColon);
	for(tokenizer<char_separator<char> >::iterator beg=tok.begin(); beg!=tok.end();++beg){
			//If we find a parenthesis set up check_for_operation to one
			//so that the next loop around we check to see if we have an 
			//operation
			if((*beg == "(" || *beg == ")") && check_for_operation_behind == 0){
				check_for_operation_behind = 1;
				list.push_back(*beg);
			}
			else if(check_for_operation_behind){
				check_for_operation_behind = 0;
				char_separator<char> separatorAmps("","&&",boost::keep_empty_tokens);
				tokenizer<char_separator<char> > tok2(*beg, separatorAmps);
				tokenizer<char_separator<char> >::iterator amps=tok2.begin();
				int count = 0;
				int stop = 0;
				string result;
				for(tokenizer<char_separator<char> >::iterator amps=tok2.begin(); amps!=tok2.end();++amps){
					
					// debug
					// cout << "Parendation : " << *amps << endl;
					if((*amps == " " || *amps == "\0" || *amps == "") && count == 0){
						amps++;
						amps++;
						amps++;
						// debug
						// cout << "Parendation Comparison found &&" << endl;
						list.push_back("&&");
					}
					else if(count != 0 && stop == 0){
						result.append(*amps);
					}
					else if(stop == 0){
						result.append(*beg);
						stop = 1;
					}
					count++;
				}
				
				check_for_operation_behind = 0;
				char_separator<char> separatorOr("","||",boost::keep_empty_tokens);
				tokenizer<char_separator<char> > tok3(*beg, separatorAmps);
				tokenizer<char_separator<char> >::iterator ors=tok3.begin();
				count = 0;
				stop = 0;
				result = "";
				for(tokenizer<char_separator<char> >::iterator ors=tok3.begin(); ors!=tok3.end();++ors){
					
					// debug	
					// cout << "Parendation : " << *ors << endl;
					if((*ors == " " || *ors == "\0" || *ors == "") && count == 0){
						ors++;
						ors++;
						ors++;
						// debug
						// cout << "Parendation Comparison found ||" << endl;
						list.push_back("||");
					}
					else if(count != 0 && stop == 0){
						result.append(*ors);
					}
					else if(stop == 0){
						result.append(*beg);
						stop = 1;
					}
					count++;
				}
				
				list.push_back(result);
			
			}
			else{
				check_for_operation_behind = 0;
				list.push_back(*beg);
			}
	}
	
	return list;
}

void Terminal::removeEmpty(vector<string> & v){
	int len = v.size();
	for(int i = 0; i < len; i++){
		if(v[i] == "\0" || v[i] == " " || v[i] == ""){
			// debug
			// cout << "removed Blanks: " << i  << ":" << v[i]  << ":" << endl;
			v.erase(v.begin() + i);
		}
	}
}

void Terminal::splicer(string  str){
		int lastOperation = 0; //zero for OR one for AND
		int result = 0;
		int global_result = 0;
		int parentheses = 0;
			
		char_separator<char> separatorSemiColon(";");
		tokenizer<char_separator<char> > tok(str, separatorSemiColon);
		for(tokenizer<char_separator<char> >::iterator beg1=tok.begin(); beg1!=tok.end();++beg1){
			if(*beg1 == "("){
				// debug
	    		// cout << "Open Parenthesis Found" << endl;
	    		parentheses++;
	    		continue;
	    	}
	    	else if (*beg1 == ")"){
	    		// debug
	    		// cout << "Close Parenthesis Found" << endl;
	    		parentheses--;
	    		global_result = result;
	    		// debug
	    		// cout << "Comarisons: " << global_result << endl;
	    		continue;
	    	}
    	
			//Separate strings by || first do to presidance
			char_separator<char> separatorAnd("&&");
			tokenizer<char_separator<char> > tok(*beg1, separatorAnd);
			for(tokenizer<char_separator<char> >::iterator beg2=tok.begin(); beg2!=tok.end();++beg2){
				//cout << "Executing: " << *beg2 << endl;
				//cout << "Results:" << endl;
				
				//Separate Strings by && and execute the commands
				char_separator<char> separatorOr("||");
				tokenizer<char_separator<char> > tok(*beg2, separatorOr);
				for(tokenizer<char_separator<char> >::iterator beg3=tok.begin(); beg3!=tok.end();++beg3){
					//cout << "lastOperation: " << lastOperation << endl;
					//cout << "result: " << result << endl;
					
					if(*beg3 == " " || *beg3 == "\0"){
						result = global_result;
						continue;
					}
				
					//If the result of the exe function is zero it means
					//that the function executed correctly 0 errors
					if(lastOperation == 0 && result == 0){
						result = (this->exe(*beg3) == 0);
						if(!result){
							//cout << "Error executing: " << *beg3 << endl;
						}
					}
					else if(lastOperation == 1 && result == 1){
						result = (this->exe(*beg3) == 0);
						if(!result){
							//cout << "Error executing: " << *beg3 << endl;
						}
					}
					lastOperation = 0; // OR operation ||
				}
				lastOperation = 1; // AND operation &&
			}
	 	}
		
}

//Run the terminal application
void Terminal::run(){
	int exit = 0;
	
	// Extra credit part: store the login name and host name to output later
	//char *loginName = getlogin();
	//char hostName[128];
	//gethostname(hostName, sizeof hostName);
	
	while (!exit){
		
		input = ""; //Erase the input4
		string noComments;
		while(input == ""){
			//cout << loginName << '@' << hostName << this->prompt << " ";
			cout << this->prompt << " ";
			getline(cin, input);
			noComments =  this->throwAwayComments(input);
			input = noComments;
			// if(bugSearch(input)){
			// 	cout << "Bug found in input" << endl;
			// 	input = "";
			// }
		}
		
		
	    
	    //Separat string into its induvidual parts and compare boolean values
		vector<string> list;
		list = vectorizeParentheses(noComments);
		for(unsigned int i = 0; i < list.size(); i++){
			// debug
			// cout << "Values: " << list[i] << endl;
		}
		removeEmpty(list);
		for(unsigned int i = 0; i < list.size(); i++){
			// debug
			// cout << "Values: " << list[i] << endl;
		}
	
	    //Separate string by ; first
	    int len = list.size();
	    for(int i = 0; i < len; i++){
	    	if(list[i] != "(" && list[i] != ")"){
	    		// debug
	    		// cout << "Execute: " << list[i] << endl;
    			splicer(list[i]);
	    	}
	    }
	}	
}

void Terminal::printValues(){
	for (unsigned int i = 0; i < values.size(); i++){
		// debug
		// cout << "Value " << i << ": " << *values[i] << endl;
	}
}
