#ifndef RSHELL_STAT
#define RSHELL_STAT

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;


bool fileExists(const char* filePath)
{
	//The variable that holds the file information
	struct stat fileAtt; 

	//Use the stat function to get the information
	if (stat(filePath, &fileAtt) != 0) //start will be 0 when it succeeds
	{	
		// cout << "Non-zero" << endl;
		
	}	
	
	// Does the file exist?
	return S_ISREG(fileAtt.st_mode);
}

bool directoryExists(const char* directoryPath)
{
	// The variable that holds the directory information
	struct stat directoryAtt; 

	// Use the stat function to get the information
	if (stat(directoryPath, &directoryAtt) != 0) 
	// start will be 0 when it succeeds
	{	
		// cout << "Non-zero" << endl;
		
	}	
	// Does the directory exist?
	return S_ISDIR(directoryAtt.st_mode);
}

// returns 0 (TRUE) if the test succeeds and 1 (FALSE) if the test fails
// MAKE SURE THIS IS USED ONLY WHEN THERE ARE BRACKETS
bool testBracketHelper(string input)
{
	int sBracketCount = 0;
	int fBracketCount = 0;
	
	int i = 0;
	
	// Debug
	// cout << input << endl;
	for (i = 0; i < input.size(); ++i)
	{
		if (input.at(i) == '[')
		{
			++sBracketCount;
		}
		if (input.at(i) == ']')
		{
			++fBracketCount;
		}
	}
	
	// Debug
	// cout << "sBracketCount " << sBracketCount << endl;
	// cout << "fBracketCount " << fBracketCount << endl;
	
	if (sBracketCount != fBracketCount)
	{
		cout << "ERROR: NOT ENOUGH BRACKETS" << endl;
		return 1;
	}
	
	while (input.at(0) == ' ')
	{
		input.erase(input.begin());
	}
	
	while (input.at(input.size() - 1) == ' ')
	{
		input.erase(input.begin() + (input.size() - 1));
	}
	
	if (input.at(0) != '[' || (input.at(0) == '[' && input.at(1) != ' '))
	{
		cout << "ERROR: COMMAND NOT FOUND" << endl;
		return 1;
	}
	
	if (input.at(input.size() - 1) != ']' || 
		(input.at(input.size() - 1) == ']' && 
		input.at(input.size() - 2) != ' '))
	{
		cout << "ERROR: MISSING ']'" << endl;
		return 1;
	}
	
	
	for (i = 0; i < input.size(); ++i)
	{
		if (input.at(i) == '[' || input.at(i) == ']')
		{
			input.erase(input.begin() + i);
			--i;
		}
	}
	
	
	
	while (input.size() > 0 && input.at(0) == ' ')
	{
		input.erase(input.begin());
		
	}
	
	while (input.size() > 0 && input.at(input.size() - 1) == ' ')
	{
		input.erase(input.size() - 1);
	}
	
	
	string name = "";
	
	vector<string> commandString;
    commandString.push_back("");
    int j = 0;
    
    for (int k = 0; k < input.size(); ++k)
    {
    	if (input.at(k) != ' ')
    	{
    		commandString.at(j).push_back(input.at(k));
    	}
    	else
    	{
    		commandString.push_back("");
    		++j;
    	}
    }
    
    // DEBUG
    // cout << commandString.at(0) << endl;
    // cout << commandString.at(1) << endl;
    
    // if there are only brackets (no spaces or anything else)
    if (commandString.at(0) == "")
    {
    	return 1;
    }
    
    if (commandString.at(0) == ";")
    {
    	cout << "ERROR: MISSING ']'" << endl;
    	cout << "ERROR: COMMAND NOT FOUND" << endl;
    	return 1;
    	
    }
    
    // Old code used for checking multiple flags
    // int countDash = 0;
    // int invalidDash = 0;
    
    // for (int g = 0; g < commandString.size(); ++g)
    // {
    // 	if (commandString.at(g).at(0) == '-')
    // 	{
    // 		++countDash;
    // 	}
    // 	if (g > 0 && commandString.at(g).at(0) == '-')
    // 	{
    // 		++invalidDash;
    // 	}
    // }
    
    
    
    // if (countDash > 1 || invalidDash > 0)
    // {
    // 	cout << "ERROR: INVALID FLAGS" << endl;
    // 	return 1;
    // }
    
    // if the second string counts as a flag (-e, -f, or -d)
    if (commandString.at(0).at(0) == '-')
    {
    	// if you don't have a flag and a file name
    	if (commandString.size() == 1)
    	{
    		cout << "ERROR: CANNOT HAVE ONLY FLAG" << endl;
    		return 1;
    	}
    	else if (commandString.size() == 2)
    	{
    		name = commandString.at(1);
    	}
    	else
    	{
    		cout << "ERROR: EXTRANEOUS PARAMETERS" << endl;
    		return 1;
    	}
    	
    	if (commandString.at(0).size() == 2 
    		&& commandString.at(0).at(1) == 'e')
    	{
    		if (fileExists(name.c_str()) || directoryExists(name.c_str()))
    		{
    			// debug
    			// cout << "The file/directory " << name << " exists!" << endl;
    			return 0;
    		}
    		else
    		{
    			// debug
    			// cout << "The file/directory " << name << " does not exist."
    			// 	<< endl;
    			return 1;
    		}
    	}
    	else if (commandString.at(0).size() == 2
    		&& commandString.at(0).at(1) == 'f')
    	{
    		if (fileExists(name.c_str()))
    		{
    			// debug
    			// cout << "The file " << name << " exists!" << endl;
    			return 0;
    		}
    		else
    		{
    			// debug
    			// cout << "The file " << name << " does not exist." << endl;
    			return 1;
    		}
    	}
    	else if (commandString.at(0).size() == 2
    		&& commandString.at(0).at(1) == 'd')
    	{
    		if (directoryExists(name.c_str()))
    		{
    			// debug
    			// cout << "The directory " << name << " exists!" << endl;
    			return 0;
    		}
    		else
    		{
    			// debug
    			// cout << "The directory " << name << " does not exist." << endl;
    			return 1;
    		}
    	}
    	else
    	{
    		cout << "ERROR: INVALID FLAG" << endl;
    		return 1;
    	}
    }
    else if (commandString.at(0).at(0) != '-' && commandString.size() == 1)
	{
		name = commandString.at(0);
		if (fileExists(name.c_str()) || directoryExists(name.c_str()))
		{
			// debug
			// cout << "The file/directory " << name << " exists!" << endl;
			return 0;
		}
		else
		{
			// debug
			// cout << "The file/directory " << name << " does not exist."
			// 	<< endl;
			return 1;
		}
	}
	else
	{
		cout << "ERROR: NOT CORRECT NUMBER OF PARAMETERS" << endl;
		return 1;
	}
	
	
	
	// debug
	// cout << input << endl;
	return 1;
}






// returns 0 (TRUE) if the test succeeds and 1 (FALSE) if the test fails
// MAKE SURE THIS IS USED ONLY WHEN THE FIRST PHRASE IS "test"
bool testWordHelper(string input)
{
		
	
	while (input.at(0) == ' ')
	{
		input.erase(input.begin());
	}
	
	while (input.at(input.size() - 1) == ' ')
	{
		input.erase(input.begin() + (input.size() - 1));
	}
	
	string name = "";
	
	vector<string> commandString;
    commandString.push_back("");
    int j = 0;
    
    for (int i = 0; i < input.size(); ++i)
    {
    	if (input.at(i) != ' ')
    	{
    		commandString.at(j).push_back(input.at(i));
    	}
    	else
    	{
    		commandString.push_back("");
    		++j;
    	}
    }
    
    
    // DEBUG
    // cout << commandString.at(0) << endl;
    // cout << commandString.at(1) << endl;
    
    if (commandString.size() <= 1 || commandString.size() > 3)
    {
    	cout << "ERROR: NOT CORRECT NUMBER OF PARAMETERS" << endl;
    	return 1;
    }
    
    // if the second string counts as a flag (-e, -f, or -d)
    if (commandString.at(1).at(0) == '-' && commandString.size() == 3)
    {
    	name = commandString.at(2);
    	if (commandString.at(1).at(1) == 'e'
    		&& commandString.at(1).size() == 2)
    	{
    		if (fileExists(name.c_str()) || directoryExists(name.c_str()))
    		{
    			//cout << "The file/directory " << name << " exists!" << endl;
    			return 0;
    		}
    		else
    		{
    			//cout << "The file/directory " << name << " does not exist." << endl;
    			return 1;
    		}
    	}
    	else if (commandString.at(1).at(1) == 'f'
    		&& commandString.at(1).size() == 2)
    	{
    		if (fileExists(name.c_str()))
    		{
    			//cout << "The file " << name << " exists!" << endl;
    			return 0;
    		}
    		else
    		{
    			//cout << "The file " << name << " does not exist." << endl;
    			return 1;
    		}
    	}
    	else if (commandString.at(1).at(1) == 'd'
    		&& commandString.at(1).size() == 2)
    	{
    		if (directoryExists(name.c_str()))
    		{
    			// debug
    			// cout << "The directory " << name << " exists!" << endl;
    			return 0;
    		}
    		else
    		{
    			// debug
    			// cout << "The directory " << name << " does not exist." << endl;
    			return 1;
    		}
    	}
    	else
    	{
    		cout << "ERROR: FLAG AT SLOT 1" << endl;
    		return 1;
    	}
    }
    else if (commandString.at(1).at(0) != '-' && commandString.size() == 2)
	{
		name = commandString.at(1);
		if (fileExists(name.c_str()) || directoryExists(name.c_str()))
		{
			// debug
			// cout << "The file/directory " << name << " exists!" << endl;
			return 0;
		}
		else
		{
			// debug
			// cout << "The file/directory " << name << " does not exist."
			// 	<< endl;
			return 1;
		}
	}
	else
	{
		cout << "ERROR" << endl;
		return 1;
	}
	
}

// int main()
// {
//     // string text = "test/test2";
    
    
//     string input = "";
    
//     cout << "Please input \"test\" and then commands: ";
//     // cout << "Please input brackets: ";
//     getline(cin, input);
    
//     cout << testWordHelper(input) << endl;
    
	
// 	return 0;
// }

#endif