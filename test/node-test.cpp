#include "catch.hpp"
#include "../database.h"

TEST_CASE("testing database") {
	Type* testType = new Type[2];
	std::string* testColumn = new std::string[2];
    database test("test510", 2, testType, testColumn);
}