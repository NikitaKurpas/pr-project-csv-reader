#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

typedef vector<vector<string>>	matrix;///< revolution =) For internal use
typedef vector<string>			str_vec;///< For internal use

/**
 * A structure to hold file info
 */
extern struct FileInfo {
	string file_path; ///< File path
	int file_size; ///< File size
	int rows_count; ///< Count of rows in the file
	int elements_count; ///< Count of elements in the file
	int defined_columns_count; ///< Number of defined columns in the file
	str_vec columns_names; ///< Vector containing column names
} file_info; 

string toLowerCase(string str);

int StrToInt(string str);

void printCommand(string cmd, string desc);

void printHelp();

void parseFile(ifstream& file, matrix& _table, str_vec& _columns, char _LINE_DELIMITER, char _ELEMENT_DELIMITER);

void saveFile(ofstream& file, matrix& _table, str_vec& _columns, char _LINE_DELIMITER, char _ELEMENT_DELIMITER);

void HTMLexport(ofstream& file, matrix& _table, str_vec& _columns);

str_vec split(string& str, char delim);

void print(matrix& _table, str_vec& _columns);

matrix search(matrix& _table, string str);

str_vec info();