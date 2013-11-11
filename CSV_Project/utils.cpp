#include "utils.h"

using namespace std;

struct FileInfo file_info;

/**
 * Converts all given string charecters to lowercase
 * \param str String
 * \return Converted string
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

/**
 * Converts given string to integer
 * \param[in] str String
 * \return Converted int
 */
int StrToInt(string str) {
	int result;
	istringstream(str) >> result;
	return result;

}

/**
 * Prints one help command. Only used in printHelp() method. Helper method
 * \param[in] cmd	Comand
 * \param desc	Description
 */
void printCommand(string cmd, string desc)
{
	cout << setfill('.') << setw(20);
	cout << left << cmd;
	cout << setfill(' ') << setw(60);
	cout << left << desc;
}


/**
 * Prints help.
 * \deprecated Not useful anymore
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

/**
 * Reads a CSV file in fstream to the _table using specified line and element delimiters
 * \param file					A file to parse
 * \param _table				Matrix that will contain file contents
 * \param _columns				Vector that will contain columns
 * \param _LINE_DELIMITER		Line delimiter
 * \param _ELEMENT_DELIMITER	Element delimiter
 */
void parseFile(ifstream& file, matrix& _table, str_vec& _columns, char _LINE_DELIMITER, char _ELEMENT_DELIMITER) {
	string *line = new string, *lineElement = new string;

	int row_count = 0, element_count = 0;
	int col_count = 0;
	bool columnsRead = false;
	while (getline(file, *line, _LINE_DELIMITER)) {
		if (!columnsRead) {
			stringstream st(*line);
			
			while (getline(st, *lineElement, _ELEMENT_DELIMITER)) {
				_columns.push_back(*lineElement);
				col_count++;
			}
			columnsRead = true;
			continue;
		}

		stringstream st(*line);
		row_count++;
		str_vec *v_line = new str_vec;

		while (getline(st, *lineElement, _ELEMENT_DELIMITER)) {
			v_line->push_back(*lineElement);
			element_count++;
		}
		v_line->push_back(to_string(row_count));
		_table.push_back(*v_line);
		delete v_line;
	}
	delete line, lineElement;
	file_info.defined_columns_count = col_count;
	file_info.columns_names = _columns;
	file_info.rows_count = row_count;
	file_info.elements_count = element_count;
}

/**
* Saves a CSV file in fstream to the _table using specified line and element delimiters
* \param file					A file to save to
* \param _table					Matrix that contains elements
* \param _columns				Vector that contains columns
* \param _LINE_DELIMITER		Line delimiter
* \param _ELEMENT_DELIMITER		Element delimiter
*/
void saveFile(ofstream& file, matrix& _table, str_vec& _columns, char _LINE_DELIMITER, char _ELEMENT_DELIMITER) {
	for (int i = 0; i < _columns.size(); i++)
		file << _columns.at(i) << _ELEMENT_DELIMITER;
	file << _LINE_DELIMITER;
	for (int i = 0; i < _table.size(); i++) {
		for (int j = 0; j < _table.at(i).size() - 1; j++)
			file << _table.at(i).at(j) << _ELEMENT_DELIMITER;
		file << _LINE_DELIMITER;
	}
}

/**
* Exports content to HTML
* \param file					A file to save to
* \param _table					Matrix that contains elements
* \param _columns				Vector that contains columns
*/
void HTMLexport(ofstream& file, matrix& _table, str_vec& _columns) {
	file << "<!DOCTYPE html>\n"
		<< "<head>\n"
		<< "<title>" << "Export of " << file_info.file_path << " to HTML" << "</title>\n"
		<< "<style>\n th, td { padding: 5px 7px; font-family: Arial, Helvetica, sans-serif; }\n"
		<< "th { background-color: #DCDCDC; }\n</style>\n"
		<< "</head>\n<body>\n<div style=\"height: 100%; width: 100%;\">\n"
		<< "<table style=\"margin: 0 auto;\" border=\"1\" cellspacing=\"0\">\n<tr>\n";
	for (int i = 0; i < _columns.size(); i++) {
		file << "<th>" << _columns.at(i) << "</th>\n";
	}
	file << "</tr>\n";
	for (int i = 0; i < _table.size(); i++) {
		file << "<tr>\n";
		for (int j = 0; j < _table.at(i).size() - 1; j++) {
			file << "<td>" << _table.at(i).at(j) << "</td>\n";
		}
		file << "</tr>\n";
	}
	file << "</table>\n</div>\n</body>\n</html>";

}


/*
 * Splits the given string into elements
 * \param str		String to split
 * \param delim		Delimiter
 * \return An array, containing splitted string
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
}*/

/*
* Prints the contents of the _table on the screen.
* \param _table		Elements matrix
* \param _columns	Columns vector
*/
void print(matrix& _table, str_vec& _columns) {
	cout << "[Row number], ";
	for (int i = 0; i < _columns.size(); i++) {
		string tmp = "[" + _columns.at(i) + "]";
		if (i == _columns.size() - 1)
			cout << tmp;
		else
			cout << tmp << ", ";
	}
	cout << endl;
	for (int i = 0; i < _table.size(); i++) {
		cout << setw(6) << left << "[" + to_string(i + 1) + "]";
		for (int j = 0; j < _table.at(i).size() - 1; j++) {
				if (j == _table.at(i).size() - 2) {
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
 * \param  _table
 * \param  str
 * \return	   matrix
 */
matrix search(matrix& _table, string str) {
	matrix result;
	for (int i = 0; i < _table.size(); i++) {
		for (int j = 0; j < _table.at(i).size(); j++) {
			std::size_t found = toLowerCase(_table.at(i).at(j)).find(toLowerCase(str));
			if (found != std::string::npos) {
				str_vec tmp = _table.at(i);
				tmp.pop_back();
				tmp.push_back(to_string(i));
				result.push_back(tmp);
				break;
			}
		}
	}
	return result;
}

/*
* Gives basic information about _table
* \return Vector containing the info
*/
str_vec info() {
	str_vec result;
	result.push_back("INFORMATION: ");
	result.push_back(" File path: " + file_info.file_path);
	result.push_back(" File size: " + to_string(file_info.file_size) + " bytes");
	result.push_back(" Rows count: " + to_string(file_info.rows_count));
	result.push_back(" Elements count: " + to_string(file_info.elements_count));
	result.push_back(" Defined columns count: " + to_string(file_info.defined_columns_count));
	result.push_back(" Columns:");
	for (int i = 0; i < file_info.columns_names.size(); i++)
		result.push_back("   [" + file_info.columns_names.at(i) + "]");
	return result;
}