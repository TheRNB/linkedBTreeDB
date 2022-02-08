#include <string>
#include <sstream>
#include <stdexcept>
#include "utils/hashUtils.h"
#include <iostream>

bool validator_int(std::string input) {
	for (int i = 0; i < input.size(); ++i) {
		if (i == 0 and input[i] == '-') continue;
		if (input[i] < '0' or input[i] > '9')
			return false;
	}
	return true;
}

bool validator_date(std::string input) {
	int begin = 0;
	int sectionPos = 0;
	for (int i = 0; i < input.size(); ++i) 
		if (input[i] != '/' and (input[i] > '9' or  input[i] < '0')) 
			return false;
	for (int i = 0; i < input.size(); ++i) {
		if (input[i] == '/') {
			int currNum = hashh(input.substr(begin, i-begin), INTEGER);
			if (sectionPos == 0) {
				if (currNum > 9999)
					return false;
			} else if (sectionPos == 1) {
				if (currNum > 12)
					return false;
			} else {
				if (currNum > 31)
					return false;
			}
			begin = i+1;
			sectionPos++;
		}
	}
	return true;
}

bool validator_string(std::string input) {
	for (int i = 0; i < input.size(); ++i) {
		if ((input[i] > 'z' or input[i] < 'a') and (input[i] > '9' or input[i] < '0'))
			return false;
	}
	return true;
}

void validator_inputField (std::string input, Type inputType) {
	if (inputType == INTEGER) {
		if (validator_int(input) == false)
			throw std::invalid_argument("the input number is not valid");
	} else if (inputType == DATE) {
		if (validator_date(input) == false)
			throw std::invalid_argument("the input date is not valid");
	} else {
		if (validator_string(input) == false)
			throw std::invalid_argument("the input string must only contain lowercase letters and numbers");
	}
	return;
}


//CREATE TABLE {table name} ( column1 type , column2 type , ... )
bool validator_command_create (std::string input) {
	stringstream command(input);
	std::string parse;
	std::string validInputs[] = {"CREATE", "TABLE", "", ""};
	for (int i = 0; i < 3; ++i) {
		getline(cin, parse, ' ');
		if (validInputs[i] != "" and parse != validInputs[0])
			return false;
	}
	getline(cin, parse, ' ');
	stringstream kwargs(parse);
	while(getline(kwargs, parse, ',')) {
		stringstream arg(parse);
		getline(arg, parse, ' ');
		getline(arg, parse);
		return false;
	}
	return true;
}

//INSERT INTO {table name} VALUES ( field1 , field2 , ... )
bool validator_command_insert (std::string input) {
	stringstream command(input);
	std::string parse;
	std::string validInputs[] = {"INSERT", "INTO", "", "VALUE", ""};
	for (int i = 0; i < 4; ++i) {
		getline(cin, parse, ' ');
		if (validInputs[i] != "" and parse != validInputs[0])
			return false;
	}
	return true;
}

//DELETE FROM {table name} WHERE {cond i tion}
bool validator_command_delete (std::string input) {
	stringstream command(input);
	std::string parse;
	std::string validInputs[] = {"DELETE", "FROM", "", "WHERE", ""};
	for (int i = 0; i < 4; ++i) {
		getline(cin, parse, ' ');
		if (validInputs[i] != "" and parse != validInputs[0])
			return false;
	}
	return true;
}

//UPDATE {table name} SET ( "Hamid" , 2022/8/7 , 50000 ) WHERE {cond i tion}
bool validator_command_update (std::string input) {
	stringstream command(input);
	std::string parse;
	std::string validInputs[] = {"UPDATE", "", "SET", "", "WHERE", ""};
	for (int i = 0; i < 5; ++i) {
		getline(cin, parse, ' ');
		if (validInputs[i] != "" and parse != validInputs[0])
			return false;
	}
	return true;
}

//SELECT {( column1 , column2 , ... ) or *} FROM {table name} WHERE cond i tion
bool validator_command_select (std::string input) {
	stringstream command(input);
	std::string parse;
	std::string validInputs[] = {"SELECT", "", "FROM", "", "WHERE", ""};
	for (int i = 0; i < 5; ++i) {
		getline(cin, parse, ' ');
		if (validInputs[i] != "" and parse != validInputs[0])
			return false;
	}
	return true;
}

bool validator_command (std::string input) {
	if (input[0] == 'S') {
		if (validator_command_select(input) == false)
			throw std::invalid_argument("the SELECT command was not recognized");
	} else if (input[0] == 'U') {
		if (validator_command_update(input) == false)
			throw std::invalid_argument("the UPDATE command was not recognized");
	}  else if (input[0] == 'D') {
		if (validator_command_delete(input) == false)
			throw std::invalid_argument("the DELETE command was not recognized");
	}  else if (input[0] == 'I') {
		if (validator_command_update(input) == false)
			throw std::invalid_argument("the INSERT command was not recognized");
	}  else if (input[0] == 'C') {
		if (validator_command_update(input) == false)
			throw std::invalid_argument("the CREATE command was not recognized");
	} else {
		throw std::invalid_argument("the command was not recognized");
	}
	return;
}
