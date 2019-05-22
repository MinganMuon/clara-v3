#include "catch.hpp"

#include "checkers.h"

TEST_CASE ("isTileOnWhiteKingLine", "[checkers][checkers-board]") {
	REQUIRE( isTileOnWhiteKingLine(37) );
	REQUIRE( isTileOnWhiteKingLine(38) );
	REQUIRE( isTileOnWhiteKingLine(39) );
	REQUIRE( isTileOnWhiteKingLine(40) );
	REQUIRE_FALSE( isTileOnWhiteKingLine(45) );
	REQUIRE_FALSE( isTileOnWhiteKingLine(4) );
	REQUIRE_FALSE( isTileOnWhiteKingLine(23) );
}

TEST_CASE ("isTileOnWhiteKingLine", "[checkers][checkers-board]") {
	REQUIRE( isTileOnWhiteKingLine(5) );
	REQUIRE( isTileOnWhiteKingLine(6) );
	REQUIRE( isTileOnWhiteKingLine(7) );
	REQUIRE( isTileOnWhiteKingLine(8) );
	REQUIRE_FALSE( isTileOnWhiteKingLine(45) );
	REQUIRE_FALSE( isTileOnWhiteKingLine(4) );
	REQUIRE_FALSE( isTileOnWhiteKingLine(23) );
}

