#include "mode_expert.h"
/*
void initModeExpert() {
	cin.sync();
	command = "";
	cout << "MODE: EXPERT\n";
	cout << "For help type \"help\"\n";
	cout << "To clear the console type \"clr\"\n";
	cout << "To change to simple mode type \"mode_simple\"\n";
	cout << endl;
	while (isJavaTheBest) { // An infinite loop
		cout << "input> ";
		getline(cin, command);
		toLowerCase(command);
		if (command == "help") { // Print out the help
			command.clear();
			printHelp();
		} // command == "help"
		else if (command == "exit" || command == "quit") { // Exit the app
			break;
		} // command == "exit"
		else if (command.find("load") != string::npos) { // Load the given file
			try {
				file.open((split(command, ' ')).at(1));
				if (file.is_open()) {
					parseFile(file, _table, _LINE_DELIMITER, _ELEMENT_DELIMITER);
					cout << "File loaded\n";
					_FILE_LOADED = true;
				}
			}
			catch (exception) {
				cout << "Failed to open file\n";
			}
		} // command == "load"
		else if (command == "query") { // Enter the query mode. In query mode you can add, remove and modify data.
			cout << "To exit query mode type \"end\" or \"exit\" or \"quit\"" << endl;
			while (isJavaTheBest) {
				cout << "query> ";
				getline(cin, command);
				toLowerCase(command);
				str_vec v_cmd = split(command, ' ');
				if (v_cmd[0] == "select") { // select [*|colname|colname1;colname2]( where [colname2=val|colname2=val;colname3=val2])?

					str_vec col_names;   // For storing column_names such as colname1 and colname2 etc.
					matrix  condition;   // For storing conditions such as colname_1 = 123, colname2 = abcds etc.

					if (v_cmd.size() > 1) {
						col_names = split(v_cmd[1], ';');
						if (v_cmd.size() == 4) { // select column_name where column_name2=value;column_name3=value
							str_vec condition_splitted = split(v_cmd[3], ';'); // We get N conditions
							for (unsigned int i = 0; i < condition_splitted.size(); i++) {
								try {
									str_vec* element = new str_vec(2);
									element->push_back((split(condition_splitted[i], '=')).at(0));
									element->push_back((split(condition_splitted[i], '=')).at(1));
									condition.push_back(*element);
									delete element;
								}
								catch (std::exception&) {
									continue;
								} // the try-catch
							} // the for loop
						} // query command size == 4
					} // query command size > 1
					else {
						cout << "output> Invalid syntax!\n";
					}
					matrix result;

					if (condition.size() == 0)  result = select(col_names, _table);
					else                        result = select(col_names, condition, _table);
				} // query == "select"
				else if (v_cmd[0] == "end" || v_cmd[0] == "exit" || v_cmd[0] == "quit") {
					break;
				}
			}
		} // command == "query"
		else if (command == "clr") { // Clear the console window
			system("cls");
		} // command == "clr"
		else if (command == "mode_simple") { // Chnage to simple mode
			system("cls");
			initModeSimple();
			break;
		}
		else { // If invalid command
			cout << "output> No command found: " << command << endl;
		} // command invalid
	}
}*/