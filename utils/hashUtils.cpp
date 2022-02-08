#include <string>
#include "database.h"

long long hashString(std::string inputString) {
	long long result = 0;
	for (int i = 0; i < (int)inputString.size(); ++i) {
		if (((i == 0) or (i == ((int)inputString.size()-1))) and inputString[i] == char(34)) continue;
		result *= 37;
		if ('0' <= inputString[i] and inputString[i] <= '9') {
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
	int sign = 1;
	for (int i = 0; i < (int)inputString.size(); ++i) {
		if (i == 0 and inputString[i] == '-') {
			sign = -1;
			continue;
		}
		if (inputString[i] == ' ') continue;
		result *= 10;
		result += (long long)(inputString[i] - '0');
	}
	return sign * result;
}

long long hashDate(std::string inputString) {
	//cerr << "hashing " << inputString << endl;
	long long result = 0;
	for (int i = 0; i < (int)inputString.size(); ++i) {
		if (inputString[i] == ' ') continue;
		else if (inputString[6] == '/' and i == 5) {
			result *= 11;
			result *= 11;
			result += (long long)(inputString[i] - '0');
		}
		else if ((inputString.size() == 8 or (inputString.size() == 9 and inputString[7] == '/')) and i == inputString.size()-1) {
			result *= 11;
			result *= 11;
			result += (long long)(inputString[i] - '0');
		}
		else if (inputString[i] == '/') {
			result *= 11;
			result += 10;
		}
		else {
			result *= 11;
			result += (long long)(inputString[i] - '0');
		}
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
		if (remainder <= 10) {
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
	
	bool isNeg = false;
	if (hashedInteger < 0) {
		hashedInteger = -hashedInteger;
		isNeg = true;
	}
	std::string result = "";
	while (hashedInteger > 0) {
		int remainder = hashedInteger % 10;
		hashedInteger /= 10;
		result = char('0' + remainder) + result;
	}
	if (isNeg) result = "-" + result;
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
		if (remainder == 0 and (hashedDate % 11) == 10) continue;
		else if (remainder == 10) result = "/" + result; 
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
