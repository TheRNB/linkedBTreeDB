#include <string>
#include "database.h"

long long hashString(std::string inputString) {
	long long result = 0;
	for (int i = 0; i < (int)inputString.size(); ++i) {
		result *= 36;
		if ('0' <= inputString[i] and inputString[i] >= '9') {
			result += int(inputString[i] - '0');
		}
		else {
			result += (int(inputString[i] - 'a') + 10);
		}
	}
	return result;
}

long long hashInteger(std::string inputString) {
	long long result = 0;
	for (int i = 0; i < (int)inputString.size(); ++i) {
		result *= 10;
		result += int(inputString[i] - '0');
	}
	return result;
}

long long hashDate(std::string inputString) {
	long long result = 0;
	for (int i = 0; i < (int)inputString.size(); ++i) {
		if (inputString[i] == '/')
			continue;
		result *= 10;
		result += int(inputString[i] - '0');
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
	std::string result = "";
	while (hashedString > 0) {
		int remainder = hashedString % 36;
		hashedString/=36;
		if (remainder < 10) {
			result = char('0' + remainder) + result;
		} else {
			result = char('a' + remainder) + result;
		}
	}
	return result;
}

std::string deHashInteger(long long hashedInteger) {
	std::string result = "";
	while (hashedInteger > 0) {
		int remainder = hashedInteger % 10;
		hashedInteger /= 10;
		result = char('0' + remainder) + result;
	}
	return result;
}

std::string deHashDate(long long hashedDate) {
	std::string result = "";
	int cnt = 0;
	while (hashedDate > 0) {
		cnt++;
		if (cnt == 2 or cnt == 4)
			result = '/' + result;
		int remainder = hashedDate % 10;
		hashedDate /= 10;
		result = char('0' + remainder) + result;
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

