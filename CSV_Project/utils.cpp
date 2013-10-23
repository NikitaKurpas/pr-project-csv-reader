#include "utils.h"

using namespace std;

// Convert all given string charecter to lowercase
string toLowerCase(string& str)
{
	const int length = str.length();
	for (int i = 0; i < length; ++i)
	{
		str[i] = tolower(str[i]);
	}
	return str;
}

// Prints one help command. Only used in printHelp() method
void printCommand(string cmd, string desc)
{
	cout << setfill('.') << setw(20);
	cout << left << cmd;
	cout << setfill(' ') << setw(60);
	cout << left << desc;
}

// Prints basic help
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

// Reads a CSV file in fstream to the _table using specified line and element delimiters
void parseFile(ifstream& file, matrix& _table, char _LINE_DELIMITER, char _ELEMENT_DELIMITER) {
	string *line = new string, *lineElement = new string;
	while (getline(file, *line, _LINE_DELIMITER)) {
		stringstream st(*line);
		str_vec *v_line = new str_vec;
		while (getline(st, *lineElement, _ELEMENT_DELIMITER)) {
			v_line->push_back(*lineElement);
		}
		_table.push_back(*v_line);
		delete v_line;
	}
	delete line, lineElement;
}

// Splits the given string into elements
str_vec split(string& str, char delim) {
	stringstream stream(str);
	string item;
	str_vec result;
	while (getline(stream, item, delim)) {
		result.push_back(item);
	}
	return result;
}

matrix select() {
	matrix result;
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

// Implementation of "select"
void print(matrix& _table) {
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

str_vec info(matrix& _table) {
	str_vec result;
	result.push_back("INFORMATION: ");
	int size = _table.size() == 0 ? 0 : _table.at(0).size();
	string tmp = "Number of columns: " + to_string(size);
	result.push_back(tmp);
	int entries = _table.size() == 0 ? 0 : _table.size();
	tmp = "Number of entries: " + to_string(entries);
	result.push_back(tmp);
	if (size != 0) {
		result.push_back("Columns:");
		for (int i = 0; i < size; i++) {
			result.push_back("\t" + _table.at(0).at(i));
		}
	}
	return result;
}