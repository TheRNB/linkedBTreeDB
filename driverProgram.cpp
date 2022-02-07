#include "database.h"
#include "hashUtils.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
	Type* tps = new Type[2]; 
	tps[0] = STRING; 
	tps[1] = INTEGER; 
	int* tpi = new int[2];
	tpi[0] = 0;
	tpi[1] = 1;
	database* test = new database(10, 2, tps, tpi);
	int* tpi1 = new int[2];
	tpi1[0] = 10;
	tpi1[1] = 100;
	int* tpi2 = new int[2];
	tpi2[0] = 15;
	tpi2[1] = 1000;
	test->insert(tpi1);
	test->insert(tpi2);
	Comparisson testComp = SMALLER;
	test->printSelectChunk(testComp, -1, 3, tpi1, 0);
	tpi2[0] = 115;
	tpi2[1] = 1000;
	test->updateChunk(testComp, -1, 3, tpi2);
	testComp = EQUAL;
	vector<Node*> res = test->select(testComp, 0, 115);
	cout << res.size() << endl;
	cout << "done1" << endl;
	test->printSelectChunk(testComp, 0, 115, tpi1, 0);
	return 0;
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
