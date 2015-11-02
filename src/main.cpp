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
	
};

string findComments(string& input)
{
	// This function finds the first '#' character, copies the string from that 
	// point onward (onto a separate string), and returns the new string.
	// The old string has the comments removed (but they will be added back 
	// later).
	
	// Resize the string if there are any # symbols
	// Clarification: This removes the # and anything after it
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



void prompt()
{
	char command_prompt = '$';		// Used to prompt commands
	bool loop = true;               // If it should continue running, then true
	
	string input;                   // used to read the inputs, including spaces
	string storeComment;            // the last string to be in the string of
	                                // vectors (because a comment should be
	                                // way)
	
	vector<string> result;
	
	cout << command_prompt << ' ';
	while (loop)
	{
		getline(cin, input);
		
		storeComment = findComments(input);
		
		
		result.clear();
		
		char_separator<char> separation("; ");
		tokenizer< char_separator<char> > token_text(input, separation);
		BOOST_FOREACH (const string &t, token_text)
		{
			result.push_back(t);
		}
		
		// if there were any comments in the given line
		if (storeComment != "")
		{
			result.push_back(storeComment);
		}
		
		
		// for (int i = 0; i < result.size(); ++i)   // for debugging tokenizer 
		// {                                         // vector
		// 	cout << result.at(i) << i << endl;
		// }
		
		if (input == "exit")
		{
			loop = false;
		}
		
		
		
		if (loop == true)
		{
			cout << command_prompt << ' ';
		}
	}
}


int main(int argc, char *argv[]) 
{
	prompt();
	
	return 0;
}
