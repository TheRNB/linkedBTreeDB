#include <string>
#include "database.h"

long long hashString(std::string inputString) {
	long long result = 0;
	for (int i = 0; i < (int)inputString.size(); ++i) {
		if (((i == 0) or (i == ((int)inputString.size()-1))) and inputString[i] == '\"') continue;
		if (inputString[i] == ' ') continue;
		result *= 37;
		if ('0' >= inputString[i] and inputString[i] <= '9') {
			result += ((long long)(inputString[i] - '0') + 1);
		}
		else {
			result += ((long long)(inputString[i] - 'a') + 11);
		}
	}
	return result;
}

long long hashInteger(std::string inputString) {
	long long result = 0;
	for (int i = 0; i < (int)inputString.size(); ++i) {
		if (inputString[i] == ' ') continue;
		result *= 10;
		result += (long long)(inputString[i] - '0');
	}
	return result;
}

long long hashDate(std::string inputString) {
	long long result = 0;
	for (int i = 0; i < (int)inputString.size(); ++i) {
		if (inputString[i] == ' ') continue;
		result *= 11;
		if (inputString[i] == '/') result += 10;
		else result += (long long)(inputString[i] - '0');
	}
	return result;
}

long long hashh(std::string inputString, Type inputType) {
	if (inputType == STRING) {
		return hashString(inputString);
	} else if (inputType == INTEGER) {
		return hashInteger(inputString);
	} else {
		return hashDate(inputString);
	}
}

std::string deHashString(long long hashedString) {
	if(hashedString == 0)
		return "0";
	std::string result = "";
	while (hashedString > 0) {
		int remainder = hashedString % 37;
		hashedString/=37;
		if (remainder < 10) {
			result = char('0' + remainder -1) + result;
		} else {
			result = char('a' + remainder - 11) + result;
		}
	}
	return result;
}

std::string deHashInteger(long long hashedInteger) {
	if(hashedInteger == 0)
		return "0";
	std::string result = "";
	while (hashedInteger > 0) {
		int remainder = hashedInteger % 10;
		hashedInteger /= 10;
		result = char('0' + remainder) + result;
	}
	return result;
}

std::string deHashDate(long long hashedDate) {
	if(hashDate == 0)
		return "0";
	std::string result = "";
	int cnt = 0;
	while (hashedDate > 0) {
		int remainder = hashedDate % 11;
		hashedDate /= 11;
		if (remainder == 10) result = "/" + result; 
		else result = char('0' + remainder) + result;
	}
	return result;
}

std::string deHash(long long inputString, Type inputType) {
		if (inputType == STRING) {
		return deHashString(inputString);
	} else if (inputType == INTEGER) {
		return deHashInteger(inputString);
	} else {
		return deHashDate(inputString);
	}
}

/*
8
CREATE TABLE x (name string,joinDate timestamp,income int)
INSERT INTO x VALUES ("atena",2019/7/6,55000)
INSERT INTO x VALUES ("sajede",2020/5/24,20000)
INSERT INTO x VALUES ("sajede",2020/5/24,20000)
INSERT INTO x VALUES ("sag",2010/5/24,110000)
INSERT INTO x VALUES ("atena",2019/7/6,550400)
//UPDATE x SET ("narges20", 2022/1/14, 4000) WHERE income>100000
SELECT * FROM x WHERE name=="narges20"
*/