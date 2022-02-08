#include "catch.hpp"
#include "../tree.h"

TEST_CASE("testing tree") {
    BTree test("test420");
    
	REQUIRE(test.getName() == "test420"); 
	REQUIRE(test.size() == 0);
}