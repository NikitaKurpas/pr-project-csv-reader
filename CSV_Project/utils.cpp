#include "utils.h"

using namespace std;

struct FileInfo file_info;

/*
* Converts all given string charecters to lowercase
* @param str
*/
string toLowerCase(string str)
{
	const int length = str.length();
	for (int i = 0; i < length; ++i)
	{
		str[i] = tolower(str[i]);
	}
	return str;
}

/*
* Prints one help command. Only used in printHelp() method
* @param cmd
* @param desc
*/
void printCommand(string cmd, string desc)
{
	cout << setfill('.') << setw(20);
	cout << left << cmd;
	cout << setfill(' ') << setw(60);
	cout << left << desc;
}


/*
* Prints help
*/
void printHelp()
{
	cout << endl;
	printCommand("Command", "Description");
	cout << endl;
	printCommand("help", "Prints this help");
	printCommand("load <file>", "Loads a file by the given file name");
	printCommand("save_html <file>", "Saves the result into the given file");
	printCommand("clr", "Clears this console's screen");
	printCommand("mode_simple", "Changes mode to simple");
	cout << endl;
}

/*
* Reads a CSV file in fstream to the _table using specified line and element delimiters
* @param file
* @param _table
* @param _columns
* @param _LINE_DELIMITER
* @param _ELEMENT_DELIMITER
*/
void parseFile(ifstream& file, matrix& _table, str_vec& _columns, char _LINE_DELIMITER, char _ELEMENT_DELIMITER) {
	string *line = new string, *lineElement = new string;

	int row_count = 0, element_count = 0;
	int col_count = 0;
	while (getline(file, *line, _LINE_DELIMITER)) {
		if (line->find("c[") == 0) {
			line->erase(0, 2);

			stringstream st(*line);
			
			while (getline(st, *lineElement, _ELEMENT_DELIMITER)) {
				_columns.push_back(*lineElement);
				col_count++;
			}
			continue;
		}

		stringstream st(*line);
		row_count++;
		str_vec *v_line = new str_vec;

		while (getline(st, *lineElement, _ELEMENT_DELIMITER)) {
			v_line->push_back(*lineElement);
			element_count++;
		}
		_table.push_back(*v_line);
		delete v_line;
	}
	delete line, lineElement;
	file_info.defined_columns_count = col_count;
	file_info.columns_names = _columns;
	file_info.rows_count = row_count;
	file_info.elements_count = element_count;
}


/*
* Splits the given string into elements
* @param str
* @param delim
*/
str_vec split(string& str, char delim) {
	stringstream stream(str);
	string item;
	str_vec result;
	while (getline(stream, item, delim)) {
		result.push_back(item);
	}
	return result;
}

// Implementation of "select"
/*matrix select(str_vec& col_names, matrix& _table) {
	matrix result;
	short col_width = 15;

	// ATTENTION! CODE BELOW WORKS EXCLUSEVLY ON **MAGIC**
	if (col_names.size() >= 1) { // if the condition is not empty
		if (col_names.at(0) == "*") {
			for (int i = 0; i < _table.size(); i++) {
				for (int j = 0; j < _table.at(i).size(); j++) {
					if (i == 0) { // if the element is a column name then write it like this: [column_name]
						string name = "[" + _table.at(i).at(j) + "]";
						cout << setw(col_width) << left << name;
					}
					else // else - don't write the []
						cout << setw(col_width) << left << _table.at(i).at(j);
				}
				cout << endl;
			}
		}
		else {
			for (int i = 0; i < _table.size(); i++) { // selecting a line from table loop
				str_vec result_line;
				for (int j = 0; j < _table.at(i).size(); j++) { // selecting an item from a line loop
					for (int col_name = 0; col_name < col_names.size(); col_name++) { // selecting conditions
						if (_table.at(0).at(j) == col_names.at(col_name)) { // filtering conditions
							if (i == 0) { // if the element is a column name then write it like this: [column_name]
								string name = "[" + _table.at(i).at(j) + "]";
								cout << setw(col_width) << left << name;
							}
							else // else - don't write the []
								cout << setw(col_width) << left << _table.at(i).at(j);
							result_line.push_back(_table.at(i).at(j));
						} // end of condition if
					} // end of condition loop
				} // end of item loop
				cout << endl;
				result.push_back(result_line);
			} // end of line loop
		} // if (col_names.at(0) == "*") else
	} // if (col_names.size() >= 1)
	// **MAGIC** ENDS HERE
	return result;
}*/ // OLD

/*
* Prints the contents of the _table on the screen
* @param _table
*/
void print(matrix& _table, str_vec& _columns) {
	if (!_columns.empty()) {
		for (int i = 0; i < _columns.size(); i++) {
			string tmp = "[" + _columns.at(i) + "]";
			if (i == _columns.size() - 1)
				cout << tmp;
			else
				cout << tmp << ", ";
		}
	}
	cout << endl;
	for (int i = 0; i < _table.size(); i++) {
		for (int j = 0; j < _table.at(i).size(); j++) {
				if (j == _table.at(i).size() - 1) {
					cout << _table.at(i).at(j);
				}
				else {
					cout << _table.at(i).at(j) << ", ";
				}
		}
		cout << endl;
	}
}

/*
* Searches the _table for occurances of str 
* @param _table
* @param str
*/
matrix search(matrix& _table, string str) {
	matrix result;
	for (int i = 0; i < _table.size(); i++) {
		for (int j = 0; j < _table.at(i).size(); j++) {
			std::size_t found = toLowerCase(_table.at(i).at(j)).find(toLowerCase(str));
			if (found != std::string::npos) {
				result.push_back(_table.at(i));
				break;
			}
		}
	}
	return result;
}

/*
* Gives basic information about _table
* @param _table
*/
str_vec info() {
	str_vec result;
	result.push_back("INFORMATION: ");
	result.push_back("File path: " + file_info.file_path);
	result.push_back("File size: " + to_string(file_info.file_size) + " bytes");
	result.push_back("Rows count: " + to_string(file_info.rows_count));
	result.push_back("Elements count: " + to_string(file_info.elements_count));
	result.push_back("Defined columns count: " + to_string(file_info.defined_columns_count));
	if (!file_info.columns_names.empty()) {
		result.push_back("Columns:");
		for (int i = 0; i < file_info.columns_names.size(); i++)
			result.push_back("  [" + file_info.columns_names.at(i) + "]");
	}
	return result;
}