#include "catch.hpp"

#include "checkers.h"

TEST_CASE ("isTileOnWhiteKingLine", "[checkers][checkers-board]") {
	REQUIRE( Checkers::Board::isTileOnWhiteKingLine(37) );
	REQUIRE( Checkers::Board::isTileOnWhiteKingLine(38) );
	REQUIRE( Checkers::Board::isTileOnWhiteKingLine(39) );
	REQUIRE( Checkers::Board::isTileOnWhiteKingLine(40) );
	REQUIRE_FALSE( Checkers::Board::isTileOnWhiteKingLine(45) );
	REQUIRE_FALSE( Checkers::Board::isTileOnWhiteKingLine(4) );
	REQUIRE_FALSE( Checkers::Board::isTileOnWhiteKingLine(23) );
}

TEST_CASE ("isTileOnBlackKingLine", "[checkers][checkers-board]") {
	REQUIRE( Checkers::Board::isTileOnBlackKingLine(5) );
	REQUIRE( Checkers::Board::isTileOnBlackKingLine(6) );
	REQUIRE( Checkers::Board::isTileOnBlackKingLine(7) );
	REQUIRE( Checkers::Board::isTileOnBlackKingLine(8) );
	REQUIRE_FALSE( Checkers::Board::isTileOnBlackKingLine(45) );
	REQUIRE_FALSE( Checkers::Board::isTileOnBlackKingLine(4) );
	REQUIRE_FALSE( Checkers::Board::isTileOnBlackKingLine(23) );
}

