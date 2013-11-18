#include "mode_simple.h"

#include <sys/types.h>
#include <sys/stat.h>

string init[] = { "Load a file", "Change delimiter", "Current delimiter", "About author", "Exit the application" };

/**
 * Main method-menu. Beginning of the application.
 */
void initModeSimple() {
	cin.sync();
	command = "";
	while (true) {
		printCommands(init, sizeof(init) / sizeof(*init));
		cout << "choise> ";
		cin.sync(); cin >> command;

		if (command == "1") { // Load the file
			if (fileMenu() == -1) continue;
		} // Load the file
		
		else if (command == "2") { // Change delimiter
			cout << "Current delimiter > \'" << _ELEMENT_DELIMITER << "\'" << endl;
			cout << "    New delimiter > ";
			char prev_delim = _ELEMENT_DELIMITER;
			cin.sync(); cin >> _ELEMENT_DELIMITER;
			if (!cin.good()) {
				system("cls");
				cout << "Bad delimiter symbol. Old one restored";
				continue;
			}
			system("cls");
			cout << "Delimiter changed > \'" << _ELEMENT_DELIMITER << "\'" << endl;
			continue;
		} // Change delimiter

		else if (command == "3") { // Current delimiter
			system("cls");
			cout << "Current delimiter > \'" << _ELEMENT_DELIMITER << "\'" << endl;
			continue;
		} // Current delimiter

		else if (command == "4") { // About author
			system("cls");
			cout << "Author:" << endl;
			cout << "  Name:     Nikita" << endl;
			cout << "  Surname:  Kurpas" << endl;
			cout << "  Login:    KUR0089" << endl;
			cout << "  Group:    Unknown" << endl;
			cout << "  Time:     16:00" << endl;
			cout << "Author end;" << endl << endl;
			continue;
		} // About author

		else if (command == "5") { // Exit
			break;
		} // Exit
		system("cls");
	} // Main while loop
	return;
}

string file_ops[] = { "Show information about the file", "Print contents", "Search file", "Edit row", "Delete row", "Insert row", "Save file", "Save file as...", "Export to HTML", "Exit file menu (close file)" };

/**
 * Method-menu to work with a file
 */
int fileMenu() {
	cout << "Enter file path and name (C:\\some_dir\\some_file.txt): ";
	string path;

// -------------------------------------------------------
	/* LOADING THE FILE */
	try {
		cin.sync(); cin >> path;
		file.close();
		file.open(path);
		if (file.is_open()) { // file loaded
			_table.clear(); _columns.clear(); _current_display.clear();
			parseFile(file, _table, _columns, _LINE_DELIMITER, _ELEMENT_DELIMITER);
			file.close();
			system("cls");
			cout << "File \"" << path << "\" loaded\n";
			_FILE_LOADED = true;

			struct stat filestatus;
			stat(path.c_str(), &filestatus);
			file_info.file_size = filestatus.st_size;
			file_info.file_path = path;
		}
		else { // file not loaded
			system("cls");
			cout << "Failed to open file \"" << path << "\"\n";
			return -1;
		} // file.is_open()
	}
	catch (exception) {
		system("cls");
		cout << "Failed to open file \"" << path << "\"\n";
		return -1;
	} // try-catch end
// -------------------------------------------------------

	/* MAIN UI PART */
	bool b_printCommands = true;
	bool b_printContents = true;
	_current_display = _table;
	while (isJavaTheBest) { // File while loop
		if (b_printContents) {
			print(_current_display, _columns);
			cout << endl;
		}
		if (b_printCommands) {
			printCommands(file_ops, sizeof(file_ops) / sizeof(*file_ops));
		}
		cout << "choise> ";
		cin.sync(); cin >> command;
		if (command == "1") {								// Show info
			system("cls"); b_printCommands = true; b_printContents = false;
			str_vec _info = info();
			for (int i = 0; i < _info.size(); i++) {
				cout << _info.at(i) << endl;
			}
			cout << endl;
		} // Info

		else if (command == "2") {							// Print contents
			system("cls"); b_printCommands = true; b_printContents = true;
			_current_display = _table;
			continue;
		}

		else if (command == "3") {							// Search file
			cout << "search> ";
			string search_str; cin.sync(); cin >> search_str;
			matrix search_result = search(_table, search_str);
			system("cls"); b_printCommands = true; b_printContents = true;
			_current_display = search_result;
		}

		else if (command == "4") {							// Edit row
			if (!_current_display.empty()) {
				cout << "Select row (1 - " << _current_display.size() << "): ";
				int row_num; cin.sync(); cin >> row_num;
				if (!cin.good() || row_num < 1 || row_num > _current_display.size()) {
					cout << "Bad row number!\n";
					b_printCommands = false; b_printContents = false;
					continue;
				}
				row_num--;
				str_vec row = _current_display.at(row_num);
				edit_row(row, row_num);
				system("cls"); b_printCommands = true; b_printContents = true;
				continue;
			}
		}

		else if (command == "5") {							// Delete row
			cout << "Select row (1 - " << _current_display.size() << "): ";
			int row_num; cin.sync(); cin >> row_num;
			if (!cin.good() || row_num < 1 || row_num > _current_display.size()) {
				cout << "Bad row number!\n";
				b_printCommands = false; b_printContents = false;
				continue;
			}
			str_vec row = _current_display.at(row_num);
			int orig_row_index = StrToInt(row.at(row.size() - 1)) - 1;
			_table.erase(_table.begin() + orig_row_index - 1);
			_current_display.erase(_current_display.begin() + row_num - 1);
			system("cls"); b_printCommands = true; b_printContents = true;
		}

		else if (command == "6") {							// Insert row
			str_vec row;
			cout << "Input values:" << endl;
			for (int i = 0; i < _columns.size(); i++) {
				cout << "[" + _columns.at(i) + "] > ";
				cin.sync(); getline(cin, command);
				row.push_back(command);
			}
			row.push_back(to_string(_table.size()));
			edit_row(row, _current_display.size());
			system("cls"); b_printCommands = true; b_printContents = true;
			continue;
		}

		else if (command == "7") {							// Save file
			ofstream file; file.open(file_info.file_path);
			if (file.is_open())
				saveFile(file, _table, _columns, _LINE_DELIMITER, _ELEMENT_DELIMITER);
			file.close();
			cout << "File saved!" << endl; b_printCommands = false; b_printContents = false;
			continue;
		}

		else if (command == "8") {							// Save file as
			cout << "Enter file path: ";
			cin.sync(); cin >> command;
			ofstream file; file.open(command);
			if (file.is_open()) {
				saveFile(file, _table, _columns, _LINE_DELIMITER, _ELEMENT_DELIMITER);
				file.close();
				cout << "File saved!" << endl; b_printCommands = false; b_printContents = false;
				continue;
			}
			else
				cout << "Failed to open file for writing!" << endl; b_printCommands = false; b_printContents = false;
			file.close();
			continue;
		}

		else if (command == "9") {							// Export to HTML
			cout << "Enter file path (it should end with .html): ";
			cin.sync(); cin >> command;
			ofstream file; file.open(command);
			if (file.is_open()) {
				HTMLexport(file, _current_display, _columns);
				file.close();
				cout << "File saved!" << endl; b_printCommands = false; b_printContents = false;
				continue;
			}
			else
				cout << "Failed to open file for writing!" << endl; b_printCommands = false; b_printContents = false;
			file.close();
			continue;
		}

		else if (command == "10") break;						// Exit file menu

		else {												// Wrong command
			system("cls"); b_printCommands = true; b_printContents = true;
			cout << "Wrong command \"" << command << "\"\n\n";
		}
	} // File while loop
}

string edit_row_ops[] = { "Edit element", "Delete element", "Save", "Cancel" };

/**
 * Method-menu for editing a row.
 * \param row		Row for editing
 * \param row_num	Row number
 */
int edit_row(str_vec& row, int row_num) {
	while (isJavaTheBest) {
		system("cls");
		print_row(row);
		printCommands(edit_row_ops, sizeof(edit_row_ops) / sizeof(*edit_row_ops));
		cout << "choise> ";
		string command;
		cin.clear(); cin.sync();
		getline(cin, command); //cin >> command;
		if (command == "1") { // Edit Element
			cout << "Element number: ";
			int elem; cin >> elem;
			if (!cin.good() || elem < 1 || elem > row.size() - 1) {
			//	cout << "Bad element number" << endl << endl;
			//	system("cls");
				continue;
			}
			elem--;
			cout << "  Old > " << row.at(elem) << endl;
			cout << "  New > "; cin.sync(); getline(cin, command); // cin.sync(); getline(cin, command, '\n');
			row.at(elem).replace(row.at(elem).begin(), row.at(elem).end(), command);
			continue;
		}

		else if (command == "2") { // Delete element
			cout << "Element number: ";
			int elem; cin.sync(); cin >> elem;
			if (!cin.good() || elem < 1 || elem > row.size() - 1) {
			//	cout << "Bad element number" << endl << endl;
			//	system("cls"); 
				continue;
			}
			elem--;
			row.at(elem).replace(row.at(elem).begin(), row.at(elem).end(), "");
		}

		else if (command == "3") { // Save
			int orig_row_index = StrToInt(row.at(row.size() - 1)) - 1;
			if (orig_row_index == _table.size())
				_table.push_back(row);
			else
				_table.at(orig_row_index) = row;
			if (row_num == _current_display.size())
				_current_display.push_back(row);
			else
				_current_display.at(row_num) = row;
			break;
		}

		else if (command == "4") { // Cancel
			break;
		}
	}
	return -1;
}

/**
 * Method to print a row for editing
 * \param row	A vector containing a row to print
 */
void print_row(str_vec& row) {
	cout << "Row elements:" << endl;
	for (int i = 0; i < _columns.size(); i++) {
		string tmp;
		try {
			cout << setw(4) << to_string(i + 1) + "" << setw(20) << "> [" + _columns.at(i) + "]" << row.at(i) << endl;
		}
		catch(exception) {
			cout << setw(4) << to_string(i + 1) + "" << setw(20) << "> [" + _columns.at(i) + "]" << endl;
		}
			
	}
}

/**
 * Prints all strings from an array in this order: "index: element"
 * \param arr	Array with commands
 * \param size	Array size
 */
void printCommands(string arr[], int size) {
	for (int i = 0; i < size; i++) {
		cout << i + 1 << ": " << arr[i] << "\n";
	} // Prints availible commands
}