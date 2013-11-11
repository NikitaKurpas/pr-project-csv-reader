#pragma once
#include <iostream>
#include <iomanip>
#include <windows.h>
#include "utils.h"
#include "mode_simple.h"

using namespace std;

extern const bool                 isJavaTheBest;			 /** \brief Java > C++ */
extern bool                      _FILE_LOADED;
extern char                      _ELEMENT_DELIMITER;
extern char                      _LINE_DELIMITER;
extern matrix                    _table;                     /** \brief This is a 2D vector - a table of string elements */
extern str_vec					 _columns;					 /** \brief A vector containing column names */
extern matrix					 _current_display;			 /** \brief A matrix containing current visible items (it can be the whole matrix or the search result); */
extern string                    command;                    /** \brief User input (command) will be stored here */
extern ifstream                  file;                       /** \brief The file will be loaded here */