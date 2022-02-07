#include <string>

bool validator_int(std::string input) {
	for (int i = 0; i < input.size(); ++i)
		if (input[i] < '0' or input[i] > '9')
			return false;

	return true;
}
bool validator_date(std::string input) {
	if ((int)input.size() != 10)
		return false;
	for (int i = 0; i < 10; ++i)
		if (i == 4 or i == 7) {
			if (input[i] != '/')
				return false;
		}
		else if (input[i] < '0' or input[i] > '9')
			return false;
	return true;
}