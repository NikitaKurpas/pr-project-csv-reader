#include "mode_simple.h"

string init[] = { "Load a file", "Clear console screen", "Exit the application" };
string file_ops[] = { "Show information about the file", "Print contents", "Exit file menu" };

void initModeSimple() {
	cin.sync();
	command = "";
	cout << "MODE: SIMPLE\n";
	while (true) {
		printCommands(init, sizeof(init) / sizeof(*init));
		cout << "choise> ";
		cin >> command;

		if (command == "1") { // Load the file
			if (fileMenu() == -1) continue;
		} // command == "1"
		
		else if (command == "2") { // Clear console
			system("cls");
		}

		else if (command == "3") { // Exit
			break;
		} // command == "4"
		system("cls");
	} // Main while loop
}

int fileMenu() {
	cout << "Enter file path and name (C:\\some_dir\\some_file.txt): ";
	string path;
	try {
		cin >> path;
		file.open(path);
		if (file.is_open()) { // file loaded
			parseFile(file, _table, _LINE_DELIMITER, _ELEMENT_DELIMITER);
			system("cls");
			cout << "File \"" << path << "\" loaded\n";
			_FILE_LOADED = true;
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
	while (true) { // File while loop
		for (int i = 0; i < sizeof(file_ops) / sizeof(*file_ops); i++) {
			cout << i + 1 << ": " << file_ops[i] << "\n";
		} // Prints availible file commands
		cout << "choise> ";
		cin >> command;
		if (command == "1") { // Show info
			system("cls");
			str_vec _info = info(_table);
			for (int i = 0; i < _info.size(); i++) {
				cout << _info.at(i) << endl;
			}
			cout << endl;
		} // Info

		else if (command == "2") { // print contents
			system("cls");
			print(_table);
		}

		else if (command == "3") break; // Exit file menu
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