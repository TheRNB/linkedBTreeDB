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
	//CREATE TABLE {table name} (column1 type,column2 type,...)
	//INSERT INTO {table name} VALUES (field1,field2,...)
	//DELETE FROM {table name} WHERE {condition}
	//UPDATE {table name} SET ("Hamid",2022/8/7,50000) WHERE {condition}
	//SELECT {(column1,column2,...) or *} FROM {table name} WHERE condition
	cerr << "not Done" << endl;
	int qCnt;
	cin >> qCnt;
	cerr << "done" << endl;
	while (qCnt--) {
		getline(cin, inputLine);
		cerr << inputLine << endl;
		stringstream commandLineInput(inputLine);
		string parsedWord;
		getline(commandLineInput, parsedWord, ' ');
		if (parsedWord == "CREATE") {
			getline(commandLineInput, parsedWord, ' '); // to ignore "TABLE"
			getline(commandLineInput, parsedWord, ' '); // current name
			long long databaseName = hashh(parsedWord, Type(STRING));
			vector<long long> columns;
			vector<Type> types;
			while (getline(commandLineInput, parsedWord, ',')) {
				stringstream column(parsedWord);
				getline(column, parsedWord, ' ');
				if(parsedWord[0] == '(') {
					columns.push_back(hashh(parsedWord.substr(1), Type(STRING)));
				} else {
					columns.push_back(hashh(parsedWord, Type(STRING)));
				}
				getline(column, parsedWord, ' ');
				if(parsedWord[parsedWord.size()-1] == ')') {
					parsedWord = parsedWord.substr(0, parsedWord.size()-1);
				}
				cerr << "parsedType is " << parsedWord << endl;
				if (parsedWord == "string") {
					types.push_back(Type(STRING));
				} else if (parsedWord == "timestamp") {
					types.push_back(Type(DATE));
				} else if (parsedWord == "int"){
					types.push_back(Type(INTEGER));
				}
			}
			Type* tmp1 = new Type [columns.size()];
			long long* tmp2 = new long long [columns.size()];
			for (int i = 0; i < columns.size(); ++i) {
				tmp1[i] = types[i];
				tmp2[i] = columns[i];
			}
			cerr << "here " << databaseName << " " << columns.size() << endl;
			for (int i = 0; i < types.size(); ++i) cout << types[i] << " ";
			cout << endl;
			databaseList.push_back(new database(databaseName, columns.size(), tmp1, tmp2));
		}
		else if(parsedWord == "INSERT") {
			getline(commandLineInput, parsedWord, ' '); // to ignore INTO
			getline(commandLineInput, parsedWord, ' '); // current name
			int tableIndex = 0;
			while(databaseList[tableIndex]->getName() != hashh(parsedWord, STRING)) tableIndex++;
			getline(commandLineInput, parsedWord, ' '); //to ignore VALUES
			getline(commandLineInput, parsedWord, ' ');
			vector<string> inputee;
			stringstream inputeeAtt(parsedWord);
			while(getline(inputeeAtt, parsedWord, ',')) {
				inputee.push_back(parsedWord);
			}
			inputee[0] = inputee[0].substr(1);
			inputee[inputee.size()-1] = inputee[inputee.size()-1].substr(0, inputee[inputee.size()-1].size()-1);
			databaseList[tableIndex]->insert(inputee);
		}
		else if (parsedWord == "DELETE") {
			getline(commandLineInput, parsedWord, ' '); // to ignore FROM
			getline(commandLineInput, parsedWord, ' '); // current name
			int tableIndex = 0;
			while(databaseList[tableIndex]->getName() != hashh(parsedWord, STRING)) tableIndex++;
			getline(commandLineInput, parsedWord, ' '); // to ignore WHERE
			getline(commandLineInput, parsedWord, ' ');
			string firstOperand, secondOperand;
			for (int k = 0; k < (int)parsedWord.size(); ++k) {
				if (parsedWord[k] == '<') {
					firstOperand = parsedWord.substr(0, k);
					secondOperand = parsedWord.substr(k+1);
					databaseList[tableIndex]->deleteChunk(SMALLER, firstOperand, secondOperand);
				} else if (parsedWord[k] == '=') {
					firstOperand = parsedWord.substr(0, k);
					secondOperand = parsedWord.substr(k+2);
					databaseList[tableIndex]->deleteChunk(EQUAL, firstOperand, secondOperand);
				} else if (parsedWord[k] == '>') {
					firstOperand = parsedWord.substr(0, k);
					secondOperand = parsedWord.substr(k+1);
					databaseList[tableIndex]->deleteChunk(BIGGER, firstOperand, secondOperand);
				}
			}
		}
		else if (parsedWord == "UPDATE") {
			getline(commandLineInput, parsedWord, ' '); // current name
			int tableIndex = 0;
			while(databaseList[tableIndex]->getName() != hashh(parsedWord, STRING)) tableIndex++;
			getline(commandLineInput, parsedWord, ' '); // to ignore SET
			getline(commandLineInput, parsedWord, ' ');
			vector<string> inputee;
			stringstream inputeeAtt(parsedWord);
			while(getline(inputeeAtt, parsedWord, ',')) {
				inputee.push_back(parsedWord);
			}
			inputee[0] = inputee[0].substr(1);
			inputee[inputee.size()-1] = inputee[inputee.size()-1].substr(0, inputee[inputee.size()-1].size()-1);
			getline(commandLineInput, parsedWord, ' '); // to ignore WHERE
			getline(commandLineInput, parsedWord, ' ');
			string firstOperand, secondOperand;
			for (int k = 0; k < (int)parsedWord.size(); ++k) {
				if (parsedWord[k] == '<') {
					firstOperand = parsedWord.substr(0, k);
					secondOperand = parsedWord.substr(k+1);
					databaseList[tableIndex]->updateChunk(SMALLER, firstOperand, secondOperand, inputee);
				} else if (parsedWord[k] == '=') {
					firstOperand = parsedWord.substr(0, k);
					secondOperand = parsedWord.substr(k+2);
					databaseList[tableIndex]->updateChunk(EQUAL, firstOperand, secondOperand, inputee);
				} else if (parsedWord[k] == '>') {
					firstOperand = parsedWord.substr(0, k);
					secondOperand = parsedWord.substr(k+1);
					databaseList[tableIndex]->updateChunk(BIGGER, firstOperand, secondOperand, inputee);
				}
			}
		}
		else if (parsedWord == "SELECT") {
			getline(commandLineInput, parsedWord, ' ');
			vector<string> inputee;
			stringstream inputeeAtt(parsedWord);
			while(getline(inputeeAtt, parsedWord, ',')) {
				if (parsedWord == "*") break;
				inputee.push_back(parsedWord);
			}
			if (inputee.size() > 0) {
				inputee[0] = inputee[0].substr(1);
				inputee[inputee.size()-1] = inputee[inputee.size()-1].substr(0, inputee[inputee.size()-1].size()-1);
			}
			getline(commandLineInput, parsedWord, ' ');//to ignore FROM
			getline(commandLineInput, parsedWord, ' ');
			int tableIndex = 0;
			while(databaseList[tableIndex]->getName() != hashh(parsedWord, STRING)) tableIndex++;
			getline(commandLineInput, parsedWord, ' '); // to ignore WHERE
			getline(commandLineInput, parsedWord, ' ');
			string firstOperand, secondOperand;
			for (int k = 0; k < (int)parsedWord.size(); ++k) {
				if (parsedWord[k] == '<') {
					firstOperand = parsedWord.substr(0, k);
					secondOperand = parsedWord.substr(k+1);
					databaseList[tableIndex]->printSelectChunk(SMALLER, firstOperand, secondOperand, inputee);
				} else if (parsedWord[k] == '=') {
					firstOperand = parsedWord.substr(0, k);
					secondOperand = parsedWord.substr(k+2);
					databaseList[tableIndex]->printSelectChunk(EQUAL, firstOperand, secondOperand, inputee);
				} else if (parsedWord[k] == '>') {
					firstOperand = parsedWord.substr(0, k);
					secondOperand = parsedWord.substr(k+1);
					databaseList[tableIndex]->printSelectChunk(BIGGER, firstOperand, secondOperand, inputee);
				}
			}
		}
	}
	return 0;
}
