#pragma once
#include <iostream>
#include <limits>
#include <typeinfo>
#include <string>

using namespace std;

#ifndef INPUTCHECKER_H

#define INPUTCHECKER_H

// Checks the user input against the given type.
// Params:
//	int min, [int max], [int exceptionNum]
template <typename T> T inputChecker(int min, int max = 0, int sentinelNum = 0) {

	T input = 0;

	if (max == 0) {
		
		while (!(std::cin >> input && input >= min)) {

			std::cout << "\nInvalid input. Enter a " << typeid(T).name() <<" value minimum (" << min << "): ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	else if (sentinelNum != 0) {

		while (!(cin >> input && input >= min && input <= max || input == sentinelNum)) {
			std::cout << "\nInvalid input. Enter a integer value in range of (" << min << "-" << max << ") or (" << sentinelNum << "): ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	else {
		while (!(std::cin >> input && input >= min && input <= max)) {

			std::cout << "\nInvalid input. Enter a integer value in range of (" << min << "-" << max << "): ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	return input;
}

// asdw
template <typename T> string inputChecker() {

	bool isStringAcceptable = false;
	string str = "";

	// Clear any previous inputs.
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	do {
		cout << "Enter a name: ";
		getline(cin, str);

		// Checks the input string for whitespaces.
		if (isspace(str[0]) || str.empty()) {			
			isStringAcceptable = false;
		}
		// Checks the input string for numbers.
		else {
			for (char& c : str) {
				if (isdigit(c)) {
					isStringAcceptable = false;
				}
				else {
					isStringAcceptable = true;
				}
			}
		}

		if(!isStringAcceptable)
			cout << "Error! Name cannot include numbers or only whitespaces! ";

	} while (!isStringAcceptable);

	return str;
}

template <typename T> char inputChecker(char c, string options = "") {

	// Initialize the variables.
	string str = "";
	bool isStringAcceptable = false;

	if (options == "") {
		do {

			cout << "Enter (Y/N): ";

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			getline(cin, str);

			// Checks the input string for whitespaces.
			if (isspace(str[0]) || str.empty()) {
				isStringAcceptable = false;
			}
			else {
				// Checks the input string for numbers.
				for (char& c : str) {
					if (isdigit(c)) {
						isStringAcceptable = false;
					}
					else {
						isStringAcceptable = true;
					}
				}
			}

			if (isStringAcceptable) {
				c = str[0];
			}

		} while (toupper(c) != 'Y' && toupper(c) != 'N');
	}
	else {
		do {

			getline(cin, str);
			cout << "Enter " << options << ": ";


			// Checks the input string for whitespaces.
			if (isspace(str[0]) || str.empty()) {
				isStringAcceptable = false;
			}
			else {
				// Checks the input string for numbers.
				for (char& c : str) {
					if (isdigit(c)) {
						isStringAcceptable = false;
					}
					else {
						isStringAcceptable = true;
					}
				}
			}

			if (isStringAcceptable) {
				c = str[0];
			}

		} while (toupper(c) != 'Y');
	}

	return c;
}

#endif
