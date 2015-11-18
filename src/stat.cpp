#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

// AS FAR AS I KNOW, you have to use a function in order for this to work.
// I don't know other ways to pass in the filePath

bool fileExists(const char* filePath)
{
	//The variable that holds the file information
	struct stat fileAtt; 
	// the type stat and function stat have exactly the same names, so to refer 
	// the type, we put struct before it to indicate it is an structure.

	//Use the stat function to get the information
	if (stat(filePath, &fileAtt) != 0) //start will be 0 when it succeeds
	{	
		cout << "Non-zero" << endl;
		
	}	
	
	// S_ISREG is a macro to check if the 
	// filepath referers to a file. If you 
	// don't know what a macro is, it's ok, 
	// you can use S_ISREG as any other 
	// function, it 'returns' a bool.
	return S_ISREG(fileAtt.st_mode);
}

bool directoryExists(const char* directoryPath)
{
	// The variable that holds the directory information
	struct stat directoryAtt; 
	// the type stat and function stat have exactly the same names, so to refer 
	// the type, we put struct before it to indicate it is an structure.

	// Use the stat function to get the information
	if (stat(directoryPath, &directoryAtt) != 0) 
	// start will be 0 when it succeeds
	{	
		cout << "Non-zero" << endl;
		
	}	
	return S_ISDIR(directoryAtt.st_mode);
}

int main()
{
    string text = "test/test2";
    
	if (fileExists(text.c_str()))
	{
		cout << "The file " <<  text << " exists!\n";
	}
	else
	{
	    cout << "The file " << text << " does not exist!\n";
	}
	
	if (directoryExists(text.c_str()))
	{
	    cout << "The directory " << text << " exists!\n";
	}
	else
	{
	    cout << "The directory " << text << " does not exist!\n";
	}
	
	return 0;
}