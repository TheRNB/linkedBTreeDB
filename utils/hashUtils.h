#ifndef _HASH_UTILS_
#define _HASH_UTILS_

#include <string>
#include "../database.h"

long long hashString(std::string);

long long hashInteger(std::string);

long long hashDate(std::string);

long long hashh(std::string, Type);

std::string deHashString(long long);

std::string deHashInteger(long long);

std::string deHashDate(long long);

std::string deHash(long long, Type);

#endif
