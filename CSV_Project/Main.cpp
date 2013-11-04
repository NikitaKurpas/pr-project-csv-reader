#include "Main.h"

const bool                 isJavaTheBest = true;      // Java > C++
bool                      _FILE_LOADED = false;
char                      _ELEMENT_DELIMITER = ';';
char                      _LINE_DELIMITER = '\n';
matrix                    _table;                     // This is a 2D vector - a table of string elements
str_vec					  _columns;					  // A vector containing column names
matrix					  _current_display;			  // A matrix containing current visible items (it can be the whole matrix or the search result);
string                    command;                    // User input (command) will be stored here
ifstream                  file;                       // The file will be loaded here

int main(int _argc, char* argv)
{
	cin.sync();
	command = "";
	system("cls");
	cout << "================================================================================";
	cout << "           SUPER CSV Reader 2013. Project by Nikita Kurpas | KUR0089\n";
	cout << "================================================================================";
	cout << endl;
	initModeSimple();
	return 0;
}