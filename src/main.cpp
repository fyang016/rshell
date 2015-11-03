#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

// Abstract base class
class Connector
{
	
	
	public:
		virtual ~Connector() = 0;
		
		
};


// Virtual destructor that needs a function body.
Connector::~Connector() 
{
	
}

class Parameters
{
	// int orCount = 0;
	// int andCount = 0;
	// int nonConnectorCount = 0;
};

string findComments(string& input)
{
	/* This function finds the first '#' character, copies the string from that 
	point onward (onto a separate string), and returns the new string.
	The old string has the comments removed (but they will be added back 
	later).
	
	Resize the string if there are any # symbols
	Clarification: This removes the # and anything after it
	*/
	string comment;
	
	for (int i = 0; i < input.size(); ++i)
	{
		if (input.at(i) == '#')
		{
			
			comment.resize(input.size() - i);
			
			for (int j = 0; i + j < input.size(); ++j)
			{
				comment.push_back(input.at(i + j));
			}
			input.resize(i);
		}
	}
	
	return comment;
}

// Need to be able to split spaces from commands
void forkFunction()
{
	pid_t childPID;
	// int return_value;
	// int status;
	
	/*List of known compatible commands:
	-ls
	-echo
	-mkdir
	-git
	
	*/
	
	char* args[2];
	// string ls = "ls";
	
	vector<string> commandStuff;
	commandStuff.push_back("ls");
	
	args[0] = (char*)commandStuff.at(0).c_str();
	args[1] = NULL;
	
	childPID = fork();
	
	if (childPID < 0)
	{
		perror("fork");
		exit(0);
	}
	else if (childPID == 0)
	{
		cout << "This is the child process" << endl;
		cout << "Child process: ID #" << getpid() << endl;
		cout << "Parent process: ID #" << getppid() << endl;
		
		if (execvp (args[0], args) == -1)
		{
			perror("exec");
		}
		
		
		
	}
	else if (childPID > 0)
	{
		cout << "This is the parent process: waiting for %d to finish" << endl;
		
		waitpid(childPID, NULL, 0);
		
		if (wait(0) == -1)
		{
			perror ("wait");
		}
	}
	
}

void prompt()
{
	char command_prompt = '$';      // Used to prompt commands
	bool loop = true;               // If it should continue running, then true
	
	string input;                   // used to read the inputs, including spaces
	string storeComment;            // the last string to be in the string of
	                                // vectors (because a comment should be
	                                // way)
	
	string tempString;
	
	vector<string> result;
	
	cout << command_prompt << ' ';
	while (loop)
	{
		getline(cin, input);
		
		storeComment = findComments(input);
		
		
		result.clear();
		
		// This splits semicolons so each set of commands has its own line
		// Ex: ls; mkdir asdf; cd ..#asdfasdf will be sorted as
		// ls
		// mkdir asdf
		// cd ..#asdfasdf
		char_separator<char> separation(";");
		tokenizer< char_separator<char> > token_text(input, separation);
		BOOST_FOREACH (const string &t, token_text)
		{
			tempString = t;
			
			if (tempString.at(0) == ' ')
			{
				tempString.erase(tempString.begin());
			}
			
			if (tempString != "")
			{
				result.push_back(tempString);
			}
		}
		
		// if there were any comments in the given line
		if (storeComment != "")
		{
			result.push_back(storeComment);
		}
		
		
		// for (int i = 0; i < result.size(); ++i)   // for debugging tokenizer 
		// {                                         // vector
		// 	cout << result.at(i) << " " << i << endl;
		// }
		
		if (input == "exit")
		{
			loop = false;
		}
		
		forkFunction();
		
		if (loop == true)
		{
			cout << command_prompt << ' ';
		}
	}
}


// The main function has little code for the sake of clarity
int main(int argc, char *argv[]) 
{
	prompt();
	
	return 0;
}
