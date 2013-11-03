#include "Main.h"

const bool                 isJavaTheBest = true;      // Java > C++
bool                      _FILE_LOADED = false;
char                      _ELEMENT_DELIMITER = ';';
char                      _LINE_DELIMITER = '\n';
matrix                    _table;                     // This is a 2D vector - a table of string elements
str_vec					  _columns;
string                    command;                    // User input (command) will be stored here
ifstream                  file;                       // The file will be loaded here

int main(int _argc, char* argv)
{
	cin.sync();
	command = "";
	system("cls");
	cout << setw(60) << "CSV Reader. Project by Nikita Kurpas\n\n";
	initModeSimple();
}