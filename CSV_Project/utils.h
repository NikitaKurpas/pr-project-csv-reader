#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

typedef vector<vector<string>>	matrix;/*revolution*/		// <-- Neo is within
typedef vector<string>			str_vec;

extern struct FileInfo {
	string file_path;
	int file_size;
	int rows_count;
	int elements_count;
	int defined_columns_count;
	str_vec columns_names;
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