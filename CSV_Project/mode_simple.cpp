#include "mode_simple.h"

#include <sys/types.h>
#include <sys/stat.h>

string init[] = { "Load a file", "Clear console screen", "Exit the application" };

// Initializes simple mode
void initModeSimple() {
	cin.sync();
	command = "";
	while (true) {
		printCommands(init, sizeof(init) / sizeof(*init));
		cout << "choise> ";
		cin >> command;

		if (command == "1") { // Load the file
			if (fileMenu() == -1) continue;
		} // Load the file
		
		else if (command == "2") { // Clear console
			system("cls");
		} // Clear console

		else if (command == "5") { // Exit
			break;
		} // Exit
		system("cls");
	} // Main while loop
}

string file_ops[] = { "Show information about the file", "Print contents", "Search file", "Edit row", "Insert row", "Save file", "Save file as...", "Export to HTML", "Exit file menu (close file)" };

// Opens the file menu
int fileMenu() {
	cout << "Enter file path and name (C:\\some_dir\\some_file.txt): ";
	string path;

// -------------------------------------------------------
	/* LOADING THE FILE */
	try {
		cin >> path;
		file.open(path);
		if (file.is_open()) { // file loaded
			parseFile(file, _table, _columns, _LINE_DELIMITER, _ELEMENT_DELIMITER);
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

	/* Main UI part */
	while (true) { // File while loop
		printCommands(file_ops, sizeof(file_ops) / sizeof(*file_ops));
		cout << "choise> ";
		cin >> command;
		if (command == "1") {								// Show info
			system("cls");
			str_vec _info = info();
			for (int i = 0; i < _info.size(); i++) {
				cout << _info.at(i) << endl;
			}
			cout << endl;
		} // Info

		else if (command == "2") {							// Print contents
			system("cls");
			print(_table, _columns);
			cout << endl;
		}

		else if (command == "3") {							// Search file
			cout << "search> ";
			string search_str; cin >> search_str;
			matrix search_result = search(_table, search_str);
			system("cls");
			print(search_result, _columns);
			cout << endl;
		}

		else if (command == "4") {							// Edit row

		}

		else if (command == "5") {							// Insert row

		}

		else if (command == "6") {							// Save file

		}

		else if (command == "7") {							// Save file as

		}

		else if (command == "8") {							// Export to HTML

		}

		else if (command == "9") break;						// Exit file menu

		else {												// Wrong command
			system("cls");
			cout << "Wrong command \"" << command << "\"\n\n";
		}
	} // File while loop
}


/*
 * Prints all strings from an array like this: index: element
 * @param arr
 */
void printCommands(string arr[], int size) {
	for (int i = 0; i < size; i++) {
		cout << i + 1 << ": " << arr[i] << "\n";
	} // Prints availible commands
}