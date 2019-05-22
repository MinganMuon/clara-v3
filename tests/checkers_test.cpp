#include "catch.hpp"

#include "checkers.h"

// I feel queasy about this using statement...
using namespace Checkers;

TEST_CASE ("applyMove", "[checkers][checkers-board]") {
	SECTION ("invalid tile numbers")
	{
		Board b = Board(BlackAboveWhiteBoard);
		REQUIRE_FALSE (b.applyMove(Move(-1,5,std::vector<int>(),false)));
		REQUIRE_FALSE (b.applyMove(Move(6,-1,std::vector<int>(),false)));
		REQUIRE_FALSE (b.applyMove(Move(256,5,std::vector<int>(),false)));
		REQUIRE_FALSE (b.applyMove(Move(7,256,std::vector<int>(),false)));
		REQUIRE_FALSE (b.applyMove(Move(7,8,std::vector<int>{-1,5},false)));
		REQUIRE_FALSE (b.applyMove(Move(7,8,std::vector<int>{-1,54},false)));
		REQUIRE_FALSE (b.applyMove(Move(256,-1,std::vector<int>{-1,54},false)));
	}
}

TEST_CASE ("piece count functions", "[checkers][checkers-board]") {
	// these tests also test countPiecesOfType for if these tests succeed, then that function must be operating properly
	SECTION ("countPiecesOfPlayer")
	{
		SECTION ("empty board")
		{
			BoardType eb;
			eb.fill(TILE_EMPTY);
			Board b = Board(eb);
			REQUIRE (b.countPiecesOfPlayer(PLAYER_WHITE) == 0);
			REQUIRE (b.countPiecesOfPlayer(PLAYER_BLACK) == 0);
		}
		SECTION ("board with just white tiles")
		{
			BoardType eb;
			eb.fill(TILE_EMPTY);
			for (int i : std::vector<int>{5,11,20,29,30,39})
				eb[i] = TILE_WHITE;
			Board b = Board(eb);
			REQUIRE (b.countPiecesOfPlayer(PLAYER_WHITE) == 6);
			REQUIRE (b.countPiecesOfPlayer(PLAYER_BLACK) == 0);
		}
		SECTION ("board with just white and white king tiles")
		{
			BoardType eb;
			eb.fill(TILE_EMPTY);
			for (int i : std::vector<int>{5,11,20})
				eb[i] = TILE_WHITE;
			for (int i : std::vector<int>{29,30,39})
				eb[i] = TILE_WHITE_KING;
			Board b = Board(eb);
			REQUIRE (b.countPiecesOfPlayer(PLAYER_WHITE) == 6);
			REQUIRE (b.countPiecesOfPlayer(PLAYER_BLACK) == 0);
		}
		SECTION ("board with just black tiles")
		{
			BoardType eb;
			eb.fill(TILE_EMPTY);
			for (int i : std::vector<int>{5,11,20,29,30,39})
				eb[i] = TILE_BLACK;
			Board b = Board(eb);
			REQUIRE (b.countPiecesOfPlayer(PLAYER_WHITE) == 0);
			REQUIRE (b.countPiecesOfPlayer(PLAYER_BLACK) == 6);
		}
		SECTION ("board with just black and black king tiles")
		{
			BoardType eb;
			eb.fill(TILE_EMPTY);
			for (int i : std::vector<int>{5,11,20})
				eb[i] = TILE_BLACK;
			for (int i : std::vector<int>{29,30,39})
				eb[i] = TILE_BLACK_KING;
			Board b = Board(eb);
			REQUIRE (b.countPiecesOfPlayer(PLAYER_WHITE) == 0);
			REQUIRE (b.countPiecesOfPlayer(PLAYER_BLACK) == 6);
		}
		SECTION ("board with both color tiles")
		{
			BoardType eb;
			eb.fill(TILE_EMPTY);
			for (int i : std::vector<int>{5,11,20,29,30,39})
				eb[i] = TILE_WHITE;
			for (int i : std::vector<int>{8,13,16,28,35,40})
				eb[i] = TILE_BLACK;
			Board b = Board(eb);
			REQUIRE (b.countPiecesOfPlayer(PLAYER_WHITE) == 6);
			REQUIRE (b.countPiecesOfPlayer(PLAYER_BLACK) == 6);
		}
		SECTION ("board with both color tiles and some kings of both colors")
		{
			BoardType eb;
			eb.fill(TILE_EMPTY);
			for (int i : std::vector<int>{5,11,20,29,30,39})
				eb[i] = TILE_WHITE;
			for (int i : std::vector<int>{8,13,16,28,35,40})
				eb[i] = TILE_BLACK;
			for (int i : std::vector<int>{6,17,23,34})
				eb[i] = TILE_WHITE_KING;
			for (int i : std::vector<int>{26,38,7})
				eb[i] = TILE_BLACK_KING;
			Board b = Board(eb);
			REQUIRE (b.countPiecesOfPlayer(PLAYER_WHITE) == 10);
			REQUIRE (b.countPiecesOfPlayer(PLAYER_BLACK) == 9);
		}
		SECTION ("starting board")
		{
			Board sb = Board(BlackAboveWhiteBoard);
			REQUIRE (sb.countPiecesOfPlayer(PLAYER_WHITE) == 12);
			REQUIRE (sb.countPiecesOfPlayer(PLAYER_BLACK) == 12);
		}
	}
}

// this is very much an exercise in copy-and-paste...gotta be a better way
TEST_CASE ("padded to coords conversion and vice versa", "[checkers][checkers-board]") {
	SECTION ("paddedToCoords") {
		SECTION ("invalid tiles") {
			CoordsType coords = {0,0};
			REQUIRE (!Board::paddedToCoords(0,coords));
			REQUIRE (!Board::paddedToCoords(45,coords));
			REQUIRE (!Board::paddedToCoords(41,coords));
			REQUIRE (!Board::paddedToCoords(36,coords));
			REQUIRE (!Board::paddedToCoords(9,coords));
			REQUIRE (!Board::paddedToCoords(4,coords));
		}
		SECTION ("valid tiles") {
			CoordsType coords = {0,0};

			REQUIRE (Board::paddedToCoords(5,coords));
			REQUIRE((coords[0] == 0 && coords[1] == 7));
			
			coords[0] = 0; coords[1] = 0;
			REQUIRE (Board::paddedToCoords(10,coords));
			REQUIRE ((coords[0] == 1 && coords[1] == 6));
			
			coords[0] = 0; coords[1] = 0;
			REQUIRE (Board::paddedToCoords(13,coords));
			REQUIRE ((coords[0] == 7 && coords[1] == 6));
			
			coords[0] = 0; coords[1] = 0;
			REQUIRE (Board::paddedToCoords(15,coords));
		        REQUIRE ((coords[0] == 2 && coords[1] == 5));
			
			coords[0] = 0; coords[1] = 0;
			REQUIRE (Board::paddedToCoords(23,coords));
		        REQUIRE ((coords[0] == 0 && coords[1] == 3));
			
			coords[0] = 0; coords[1] = 0;
			REQUIRE (Board::paddedToCoords(30,coords));
		        REQUIRE ((coords[0] == 5 && coords[1] == 2));
			
			coords[0] = 0; coords[1] = 0;
			REQUIRE (Board::paddedToCoords(37,coords));
		        REQUIRE ((coords[0] == 1 && coords[1] == 0));
			
			coords[0] = 0; coords[1] = 0;
			REQUIRE (Board::paddedToCoords(40,coords));
		        REQUIRE ((coords[0] == 7 && coords[1] == 0));
		}
	}
	SECTION ("coordsToPadded") {
		SECTION ("tile off the board") {
			int t;
			REQUIRE_FALSE (Board::coordsToPadded(CoordsType{8,8},t));
			REQUIRE_FALSE (Board::coordsToPadded(CoordsType{232323,2323},t));
		}
		SECTION ("tile not legal") {
			int t;
			REQUIRE_FALSE (Board::coordsToPadded(CoordsType{0,0},t));
			REQUIRE_FALSE (Board::coordsToPadded(CoordsType{1,1},t));
			REQUIRE_FALSE (Board::coordsToPadded(CoordsType{3,7},t));
			REQUIRE_FALSE (Board::coordsToPadded(CoordsType{4,2},t));
			REQUIRE_FALSE (Board::coordsToPadded(CoordsType{7,5},t));
		}
		SECTION ("tile valid") {
			int t=0;
			REQUIRE (Board::coordsToPadded(CoordsType{0,1},t));
			REQUIRE (t == 32);
			
			t=0;
			REQUIRE (Board::coordsToPadded(CoordsType{0,7},t));
			REQUIRE (t == 5);

			t=0;
			REQUIRE (Board::coordsToPadded(CoordsType{5,0},t));
			REQUIRE (t == 39);

			t=0;
			REQUIRE (Board::coordsToPadded(CoordsType{4,5},t));
			REQUIRE (t == 16);

			t=0;
			REQUIRE (Board::coordsToPadded(CoordsType{7,6},t));
			REQUIRE (t == 13);

			t=0;
			REQUIRE (Board::coordsToPadded(CoordsType{3,6},t));
			REQUIRE (t == 11);
		}
	}
}

TEST_CASE ("isTileOn(White/Black)KingLine", "[checkers][checkers-board]") {
	SECTION ("WhiteKingLine") {
		REQUIRE( Board::isTileOnWhiteKingLine(37) );
		REQUIRE( Board::isTileOnWhiteKingLine(38) );
		REQUIRE( Board::isTileOnWhiteKingLine(39) );
		REQUIRE( Board::isTileOnWhiteKingLine(40) );
		REQUIRE_FALSE( Board::isTileOnWhiteKingLine(45) );
		REQUIRE_FALSE( Board::isTileOnWhiteKingLine(4) );
		REQUIRE_FALSE( Board::isTileOnWhiteKingLine(23) );
	}
	SECTION ("BlackKingLine") {
		REQUIRE( Board::isTileOnBlackKingLine(5) );
		REQUIRE( Board::isTileOnBlackKingLine(6) );
		REQUIRE( Board::isTileOnBlackKingLine(7) );
		REQUIRE( Board::isTileOnBlackKingLine(8) );
		REQUIRE_FALSE( Board::isTileOnBlackKingLine(45) );
		REQUIRE_FALSE( Board::isTileOnBlackKingLine(4) );
		REQUIRE_FALSE( Board::isTileOnBlackKingLine(23) );
	}
}

