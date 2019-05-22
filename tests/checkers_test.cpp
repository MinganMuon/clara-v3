#include "catch.hpp"

#include "checkers.h"

// this is very much an exercise in copy-and-paste...gotta be a better way
TEST_CASE ("padded to coords conversion and vice versa", "[checkers][checkers-board]") {
	SECTION ("paddedToCoords") {
		SECTION ("invalid tiles") {
			Checkers::CoordsType coords = {0,0};
			REQUIRE (!Checkers::Board::paddedToCoords(0,coords));
			REQUIRE (!Checkers::Board::paddedToCoords(45,coords));
			REQUIRE (!Checkers::Board::paddedToCoords(41,coords));
			REQUIRE (!Checkers::Board::paddedToCoords(36,coords));
			REQUIRE (!Checkers::Board::paddedToCoords(9,coords));
			REQUIRE (!Checkers::Board::paddedToCoords(4,coords));
		}
		SECTION ("valid tiles") {
			Checkers::CoordsType coords = {0,0};

			REQUIRE (Checkers::Board::paddedToCoords(5,coords));
			REQUIRE((coords[0] == 0 && coords[1] == 7));
			
			coords[0] = 0; coords[1] = 0;
			REQUIRE (Checkers::Board::paddedToCoords(10,coords));
			REQUIRE ((coords[0] == 1 && coords[1] == 6));
			
			coords[0] = 0; coords[1] = 0;
			REQUIRE (Checkers::Board::paddedToCoords(13,coords));
			REQUIRE ((coords[0] == 7 && coords[1] == 6));
			
			coords[0] = 0; coords[1] = 0;
			REQUIRE (Checkers::Board::paddedToCoords(15,coords));
		        REQUIRE ((coords[0] == 2 && coords[1] == 5));
			
			coords[0] = 0; coords[1] = 0;
			REQUIRE (Checkers::Board::paddedToCoords(23,coords));
		        REQUIRE ((coords[0] == 0 && coords[1] == 3));
			
			coords[0] = 0; coords[1] = 0;
			REQUIRE (Checkers::Board::paddedToCoords(30,coords));
		        REQUIRE ((coords[0] == 5 && coords[1] == 2));
			
			coords[0] = 0; coords[1] = 0;
			REQUIRE (Checkers::Board::paddedToCoords(37,coords));
		        REQUIRE ((coords[0] == 1 && coords[1] == 0));
			
			coords[0] = 0; coords[1] = 0;
			REQUIRE (Checkers::Board::paddedToCoords(40,coords));
		        REQUIRE ((coords[0] == 7 && coords[1] == 0));
		}
	}
	SECTION ("coordsToPadded") {
		SECTION ("tile off the board") {
			int t;
			REQUIRE_FALSE (Checkers::Board::coordsToPadded(Checkers::CoordsType{8,8},t));
			REQUIRE_FALSE (Checkers::Board::coordsToPadded(Checkers::CoordsType{232323,2323},t));
		}
		SECTION ("tile not legal") {
			int t;
			REQUIRE_FALSE (Checkers::Board::coordsToPadded(Checkers::CoordsType{0,0},t));
			REQUIRE_FALSE (Checkers::Board::coordsToPadded(Checkers::CoordsType{1,1},t));
			REQUIRE_FALSE (Checkers::Board::coordsToPadded(Checkers::CoordsType{3,7},t));
			REQUIRE_FALSE (Checkers::Board::coordsToPadded(Checkers::CoordsType{4,2},t));
			REQUIRE_FALSE (Checkers::Board::coordsToPadded(Checkers::CoordsType{7,5},t));
		}
		SECTION ("tile valid") {
			int t=0;
			REQUIRE (Checkers::Board::coordsToPadded(Checkers::CoordsType{0,1},t));
			REQUIRE (t == 32);
			
			t=0;
			REQUIRE (Checkers::Board::coordsToPadded(Checkers::CoordsType{0,7},t));
			REQUIRE (t == 5);

			t=0;
			REQUIRE (Checkers::Board::coordsToPadded(Checkers::CoordsType{5,0},t));
			REQUIRE (t == 39);

			t=0;
			REQUIRE (Checkers::Board::coordsToPadded(Checkers::CoordsType{4,5},t));
			REQUIRE (t == 16);

			t=0;
			REQUIRE (Checkers::Board::coordsToPadded(Checkers::CoordsType{7,6},t));
			REQUIRE (t == 13);

			t=0;
			REQUIRE (Checkers::Board::coordsToPadded(Checkers::CoordsType{3,6},t));
			REQUIRE (t == 11);
		}
	}
}

TEST_CASE ("isTileOn(White/Black)KingLine", "[checkers][checkers-board]") {
	SECTION ("WhiteKingLine") {
		REQUIRE( Checkers::Board::isTileOnWhiteKingLine(37) );
		REQUIRE( Checkers::Board::isTileOnWhiteKingLine(38) );
		REQUIRE( Checkers::Board::isTileOnWhiteKingLine(39) );
		REQUIRE( Checkers::Board::isTileOnWhiteKingLine(40) );
		REQUIRE_FALSE( Checkers::Board::isTileOnWhiteKingLine(45) );
		REQUIRE_FALSE( Checkers::Board::isTileOnWhiteKingLine(4) );
		REQUIRE_FALSE( Checkers::Board::isTileOnWhiteKingLine(23) );
	}
	SECTION ("BlackKingLine") {
		REQUIRE( Checkers::Board::isTileOnBlackKingLine(5) );
		REQUIRE( Checkers::Board::isTileOnBlackKingLine(6) );
		REQUIRE( Checkers::Board::isTileOnBlackKingLine(7) );
		REQUIRE( Checkers::Board::isTileOnBlackKingLine(8) );
		REQUIRE_FALSE( Checkers::Board::isTileOnBlackKingLine(45) );
		REQUIRE_FALSE( Checkers::Board::isTileOnBlackKingLine(4) );
		REQUIRE_FALSE( Checkers::Board::isTileOnBlackKingLine(23) );
	}
}

