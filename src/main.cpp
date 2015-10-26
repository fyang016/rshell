#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

vector<string> split(string input)       // split strings because of spaces
{                                        // and semicolons
	vector<string> result;               // Other applicable symbols are 
	                                     // also accounted for.
	int j = 0;
	int countSpaces = 0;
	int countSemicolons = 0;
	int countComments = 0;
	
	result.push_back("");
	
	for (int i = 0; i < input.size(); ++i)
	{
		if (input.at(i) != ' ' && input.at(i) != ';' && input.at(i) != '#')
		{
			countSpaces = 0;
			countSemicolons = 0;
			result.at(j) = result.at(j) + input.at(i);
		}
		else if (input.at(i) == ' ')    // make sure duplicate spaces do not 
		{                               // count
			++countSpaces;
			if (countSpaces == 1)
			{
				++j;
				result.push_back("");
			}
		}
		
		else if (input.at(i) == ';')
		{
			++countSemicolons;
			
			if (countSemicolons > 1)
			{
				cout << "Error: Multiple semicolons." << endl;
				exit(0);
			}
			else
			{
				++j;
				result.push_back(";");
			}
		}
		
		else if (input.at(i) == '#')
		{
			++countComments;
			
			if (countComments >= 1)
			{
				
			}
		}
	}
	
	
	return result;
}

int main(int argc, char *argv[]) 
{
	char command_prompt = '$';		// Used to prompt commands
	bool loop = true;               // If it should continue running, then true
	
	string input;                   // used to read the inputs, including spaces
	vector<string> result;
	
	cout << command_prompt << ' ';
	while (loop)
	{
		
		getline(cin, input);
		result = split(input);
		
		// for (int i = 0; i < result.size(); ++i)   // for debugging split 
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
	
	return 0;
}
