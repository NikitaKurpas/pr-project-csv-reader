#include "Main.h"

/**
 * \mainpage CSV Reader by Nikita Kurpas. KUR0089. Group time: 16:00.
 * A simple CSV Reader project for Programming 1
 */

const bool                 isJavaTheBest = true;      
bool                      _FILE_LOADED = false;		  
char                      _ELEMENT_DELIMITER = ';';	  
char                      _LINE_DELIMITER = '\n';	  
matrix                    _table;                     
str_vec					  _columns;					  
matrix					  _current_display;			  
string                    command;                    
ifstream                  file;     ///< The file will be loaded here.                   

/**
 * Simple main() method to init the application
 */
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