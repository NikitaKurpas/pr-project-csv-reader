#pragma once
#include <iostream>
#include <iomanip>
#include <windows.h>
#include "utils.h"
#include "mode_simple.h"

using namespace std;

extern const bool                 isJavaTheBest;			// Java > C++
extern bool                      _FILE_LOADED;
extern char                      _ELEMENT_DELIMITER;
extern char                      _LINE_DELIMITER;
extern matrix                    _table;                     // This is a 2D vector - a table of string elements
extern str_vec					 _columns;
extern string                    command;                    // User input (command) will be stored here
extern ifstream                  file;                       // The file will be loaded here