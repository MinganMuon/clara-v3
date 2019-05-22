// checkers.cpp

#include "checkers.h"

namespace Checkers {

// class Board
// -----------

BoardType getBoard()
{
	return m_theboard;
}

bool applyMove(const Move &move)
{

}

MoveList getMoveMoves(int tile)
{

}

MoveList getJumpMoves(int tile)
{

}

MoveList getPieceMoves(int tile)
{

}

MoveList getPlayerMoves(PlayerType player)
{

}

int countPiecesOfPlayer(const PlayerType targetPlayerType)
{
	int count = 0;
	if (targetPlayerType == PLAYER_WHITE) {
		count += countPiecesOfType(TILE_WHITE) + countPiecesOfType(TILE_WHITE_KING);
	} else {
		count += countPiecesOfType(TILE_BLACK) + countPiecesOfType(TILE_BLACK_KING);
	}
	return count;
}

int countPiecesOfType(const TileType targetTileType)
{
	int count = 0;
	for (TileType tt : m_theboard) {
		if (tt == targetTileType)
			count++;
	}
	return count;
}

bool hasPlayerWon(const PlayerType targetPlayerType)
{
	PlayerType theother = PLAYER_WHITE;
	if (targetPlayerType == PLAYER_WHITE)
		theother = PLAYER_BLACK;

	if (countPiecesOfPlayer(theother) == 0)
		return true;
	if (getPlayerMoves(theother).empty())
		return true;

	return false;
}

static bool paddedToCoords(const int tile, CoordsType &coords)
{
	if (tile < 5 || tile > 40 || tile == 36 || tile == 27 || tile == 18 || tile == 9)
		return false; 

	// this is ugly but I can't think of a better way...
	if (tile < 9) {
		coords[1] = 7;
		coords[0] = (tile - 5)*2;
	} else if (tile < 14) {
		coords[1] = 6;
		coords[0] = (tile - 10)*2 + 1;
	} else if (tile < 18) {
		coords[1] = 5;
		coords[0] = (tile - 14)*2;
	} else if (tile < 23) {
		coords[1] = 4;
		coords[0] = (tile - 19)*2 + 1;
	} else if (tile < 27) {
		coords[1] = 3;
		coords[0] = (tile - 23)*2;
	} else if (tile < 32) {
		coords[1] = 2;
		coords[0] = (tile - 28)*2 + 1;
	} else if (tile < 36) {
		coords[1] = 1;
		coords[0] = (tile - 32)*2;
	} else {
		coords[1] = 0;
		coords[0] = (tile - 37)*2 + 1;
	}
	
	return true;
}

static bool coordsToPadded(const CoordsType coords, int &tile)
{
	// do the coords point to an actual tile on the board?
	if (coords[0] > 7 || coords[1] > 7)
		return false;
	// do the coords point to a legal tile?
	if (coords[0] % 2) {
		if (coords[1] % 2 != 0)
			return false;
	} else {
		if (coords[1] % 2)
			return false;
	}

	int rows = 7 - coords[1]; // how many rows are we from the bottom?
	int xoffset = rows % 2;

	tile = 4; // initial invalid tile offset
	tile += 4*rows; // tiles from the full rows
	if (xoffset) {
		// invalid tiles between even-to-odd row transitions
		tile += (rows+1)/2;
		// tiles covered by being partially through a row
		tile += (coords[0] - 1)/2 + 1;
	} else {
		// invalid tiles between even-to-odd row transitions
		tile += rows/2;
		// tiles covered by being partially through a row
		tile += (coords[0])/2 + 1;
	}

	return true;
}

static bool isTileOnWhiteKingLine(const int tile)
{
	if (tile == 37 || tile == 38 || tile == 39 || tile == 40)
		return true;
	else
		return false;
}

static bool isTileOnBlackKingLine(const int tile)
{
	if (tile == 5 || tile == 6 || tile == 7 || tile == 8)
		return true;
	else
		return false;
}

}

