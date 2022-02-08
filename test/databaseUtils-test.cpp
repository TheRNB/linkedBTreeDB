#include "catch.hpp"
#include "../utils/databaseUtils.cpp"

TEST_CASE("testing hashing utilities") {
	REQUIRE("nana420" == deHash(hashh("nana20", STRING), STRING));
	REQUIRE("dishiiz" == deHash(hashh("dishiiz", STRING), STRING));
	REQUIRE("123123" == deHash(hashh("123123", STRING), STRING));
	REQUIRE("classic" == deHash(hashh("classic", STRING), STRING));
	REQUIRE("test" == deHash(hashh("test", STRING), STRING));
	
	REQUIRE("0" == deHash(hashh("0", INTEGER), INTEGER));
	REQUIRE("7" == deHash(hashh("7", INTEGER), INTEGER));
	REQUIRE("24" == deHash(hashh("24", INTEGER), INTEGER));
	REQUIRE("333" == deHash(hashh("333", INTEGER), INTEGER));
	REQUIRE("1973" == deHash(hashh("1973", INTEGER), INTEGER));
	REQUIRE("51234" == deHash(hashh("51234", INTEGER), INTEGER));
	REQUIRE("666000" == deHash(hashh("666000", INTEGER), INTEGER));
	
	REQUIRE("1973/12/31" == deHash(hashh("1973/12/31", DATE), DATE));
	REQUIRE("2010/1/4" == deHash(hashh("2010/1/4", DATE), DATE));
	REQUIRE("1951/12/31" == deHash(hashh("1951/12/31", DATE), DATE));
	REQUIRE("1914/7/28" == deHash(hashh("1914/7/28", DATE), DATE));
	REQUIRE("1939/9/1"  == deHash(hashh("1939/9/1", DATE), DATE));
	REQUIRE("1944/11/7"  == deHash(hashh("1944/11/7", DATE), DATE));
}