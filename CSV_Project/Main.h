#pragma once
#include <iostream>
#include <iomanip>
#include <windows.h>
#include "utils.h"
#include "mode_simple.h"

using namespace std;

extern const bool                 isJavaTheBest;		///< Java > C++.		 
extern bool                      _FILE_LOADED;			///< File loaded or not.
extern char                      _ELEMENT_DELIMITER;	///< Element delimiter char.
extern char                      _LINE_DELIMITER;		///< Line delimiter char.
extern matrix                    _table;				///< This is a 2D vector - a table of string elements.     
extern str_vec					 _columns;				///< A vector containing column names.	 
extern matrix					 _current_display;		///< A matrix containing current visible items (it can be the whole matrix or the search result).		 
extern string                    command;				///< User input (command) will be stored here.         
extern ifstream                  file;					///< The file will be loaded here.           