#include "mode_simple.h"

string init[] = { "Load a file", "Change to expert mode", "Clear console screen", "Exit the application" };
string file_ops[] = { "Show information about the file", "Select column(s) and show it(them)", "Exit file menu" };

void initModeSimple() {
	cin.sync();
	command = "";
	cout << "MODE: SIMPLE\n";
	while (true) {
		for (int i = 0; i < sizeof(init) / sizeof(*init); i++) {
			cout << i + 1 << ": " << init[i] << "\n";
		} // Prints availible commands
		cout << "choise> ";
		cin >> command;

		if (command == "1") { // Load the file
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
					continue;
				} // file.is_open()
			} 
			catch (exception) {
				system("cls");
				cout << "Failed to open file \"" << path << "\"\n";
				continue;
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

				else if (command == "2") { // Show columns
					system("cls");
				}

				else if (command == "3") break; // Exit file menu
			} // File while loop
		} // command == "1"

		else if (command == "2") { // -> Expert mode
			system("cls");
			initModeExpert();
			break;
		} // command == "2"
		
		else if (command == "3") {
			system("cls");
		}

		else if (command == "4") {
			break;
		} // command == "4"
		system("cls");
	} // Main while loop
}