#include "database.h"
#include "utils/hashUtils.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

string cleanInput(string input) {
	string expandedString = "";
	for (int i = 0; i < (int)input.size(); ++i) {
		if (input[i] == ',') {
			expandedString += " , ";
		}
		else if (input[i] == '(') {
			expandedString += "( ";
		}
		else if (input[i] == ')') {
			expandedString += " )";
		}
		else if (input[i] == '<') {
			expandedString += " < ";
		}
		else if (input[i] == '>') {
			expandedString += " > ";
		}
		else if (input[i] == '=' and input[i-1] != '=') {
			expandedString += " == ";
			i++;
		} else {
			expandedString += input[i];
		}
	}
	int newBegin = 0, newEnd = expandedString.size()-1;
	while (expandedString[newBegin] == ' ')
		newBegin++;
	while (expandedString[newEnd] == ' ')
		newEnd--;

	string cleanString = "";
	for (int i = newBegin; i <= newEnd; ++i) {
		if (expandedString[i] != ' ')
			cleanString += expandedString[i];
		else if (expandedString[i] == ' ' and expandedString[i-1] != ' ')
			cleanString += ' ';
	}

	string normalString = "";
	for (int i = 0; i < (int)cleanString.size(); ++i) {
		if (cleanString[i] != '(' and cleanString[i] != ')' and
			cleanString[i] != ',' and 
			cleanString[i] != '<' and cleanString[i] != '>' and cleanString[i] != '=' and
			cleanString[i] != ' ')
				normalString += cleanString[i];
		else if (cleanString[i] == '(') {
			normalString += "(";
			i++;
		}
		else if (cleanString[i] == ' ' and cleanString[i+1] == ')') {
			normalString += ")";
			i++;
		}
		else if (cleanString[i] == ' ' and cleanString[i+1] == ',') {
			normalString += ",";
			i+=2;
		}
		else if (cleanString[i] == ' ' and cleanString[i+1] == '<') {
			normalString += "<";
			i+=2;
		}
		else if (cleanString[i] == ' ' and cleanString[i+1] == '>') {
			normalString += ">";
			i+=2;
		}
		else if (cleanString[i] == ' ' and cleanString[i+1] == '=') {
			normalString += "==";
			i+=3;
		} 
		else if (cleanString[i] == ' ' and cleanString[i+1] != ' ') {
			normalString += ' ';
		}
	}
	return normalString;
}

int main() {
	vector<database*> databaseList;
	string inputLine = "";
	//CREATE TABLE {table name} ( column1 type , column2 type , ... )
	//INSERT INTO {table name} VALUES ( field1 , field2 , ... )
	//DELETE FROM {table name} WHERE {cond i tion}
	//UPDATE {table name} SET ( "Hamid" , 2022/8/7 , 50000 ) WHERE {cond i tion}
	//SELECT {( column1 , column2 , ... ) or *} FROM {table name} WHERE cond i tion
	int qCnt;
	cin >> qCnt;
	cin.ignore();
	while (qCnt--) {
		getline(cin, inputLine);
		stringstream commandLineInput(cleanInput(inputLine));
		string parsedWord;
		getline(commandLineInput, parsedWord, ' ');
		if (parsedWord == "CREATE") {
			getline(commandLineInput, parsedWord, ' '); // to ignore "TABLE"
			getline(commandLineInput, parsedWord, ' '); // current name
			string databaseName = parsedWord;
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
			databaseList.push_back(new database(databaseName, columns.size(), tmp1, tmp2));
		}
		else if(parsedWord == "INSERT") {
			getline(commandLineInput, parsedWord, ' '); // to ignore INTO
			getline(commandLineInput, parsedWord, ' '); // current name
			int tableIndex = 0;
			while(databaseList[tableIndex]->getName() != parsedWord) tableIndex++;
			getline(commandLineInput, parsedWord, ' '); //to ignore VALUES
			getline(commandLineInput, parsedWord, ' ');
			vector<string> inputee;
			stringstream inputeeAtt(parsedWord);
			while(getline(inputeeAtt, parsedWord, ',')) {
				inputee.push_back(parsedWord);
			}
			inputee[0] = inputee[0].substr(1);
			inputee[inputee.size()-1] = inputee[inputee.size()-1].substr(0, inputee[inputee.size()-1].size()-1);
			cerr << "INSERT" << endl;
			for (int i = 0; i < (int)inputee.size(); ++i) cerr << inputee[i] << " ";
			cerr << endl << endl;
			databaseList[tableIndex]->insert(inputee);
		}
		else if (parsedWord == "DELETE") {
			getline(commandLineInput, parsedWord, ' '); // to ignore FROM
			getline(commandLineInput, parsedWord, ' '); // current name
			int tableIndex = 0;
			while(databaseList[tableIndex]->getName() != parsedWord) tableIndex++;
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
					break;
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
			while(databaseList[tableIndex]->getName() != parsedWord) tableIndex++;
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
					break;
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
			while(databaseList[tableIndex]->getName() != parsedWord) tableIndex++;
			getline(commandLineInput, parsedWord, ' '); // to ignore WHERE
			getline(commandLineInput, parsedWord, ' ');
			string firstOperand, secondOperand;
			for (int k = 0; k < (int)parsedWord.size(); ++k) {
				if (parsedWord[k] == '<') {
					firstOperand = parsedWord.substr(0, k);
					secondOperand = parsedWord.substr(k+1);
					databaseList[tableIndex]->printSelectChunk(SMALLER, firstOperand, secondOperand, inputee);
					break;
				} else if (parsedWord[k] == '=') {
					firstOperand = parsedWord.substr(0, k);
					secondOperand = parsedWord.substr(k+2);
					databaseList[tableIndex]->printSelectChunk(EQUAL, firstOperand, secondOperand, inputee);
					break;
				} else if (parsedWord[k] == '>') {
					firstOperand = parsedWord.substr(0, k);
					secondOperand = parsedWord.substr(k+1);
					databaseList[tableIndex]->printSelectChunk(BIGGER, firstOperand, secondOperand, inputee);
					break;
				}
			}
		}
	}
	return 0;
}
