#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>
#include <vector>

using namespace std;

class Terminal{
	public:
		void test();	
		//void splitStringInto(const string &, char, vector<string *> &);
		void run();
		char * toChar(string *);
		string throwAwayComments(std::string);
		int exe(std::string);
		int bugSearch(string);
		void printValues();
		Terminal();

	private:
		//Global variables
		char prompt;

		//Main loop code section
		string input;
		vector<string *> values;

};


#endif
