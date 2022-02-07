#include "database.h"
#include "hashUtils.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
	vector<database*> databaseList;
	string inputLine = "";
	while (getline(cin, inputLine)) {
		stringstream commandLineInput(inputLine);
		string parsedWord;
		getline(commandLineInput, parsedWord, ' ');
		if (parsedWord == "CREATE") {
			getline(commandLineInput, parsedWord, ' '); // to ignore "TABLE"
			getline(commandLineInput, parsedWord, ' '); // current name
			int databaseName = hashh(parsedWord, Type(STRING));
		}
	}
	return 0;
}
