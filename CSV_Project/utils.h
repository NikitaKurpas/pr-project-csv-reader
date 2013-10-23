#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef vector<vector<string>> matrix;
typedef vector<string> str_vec;

string toLowerCase(string& str);
void printCommand(string cmd, string desc);
void printHelp();
void parseFile(ifstream& file, matrix& _table, char _LINE_DELIMITER, char _ELEMENT_DELIMITER);
str_vec split(string& str, char delim);
//matrix select(str_vec& col_names, matrix& _table); Deprecated
void print(matrix& _table);
str_vec info(matrix& _table);