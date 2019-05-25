// checkers.cpp

#include "checkers.h"

namespace Checkers {

// class Board
// -----------

BoardType Board::getBoard()
{
	return m_theboard;
}

void Board::setBoard(BoardType newboard)
{
	m_theboard = newboard;
}

bool Board::applyMove(const Move &move)
{
	// note: does not check if the move is legal or not!
	// only checks if any of the tile numbers are invalid!
	
	std::vector<int> tocheck = move.tilesJumped;
	tocheck.push_back(move.tileFrom);
	tocheck.push_back(move.tileTo);
	for (int t : tocheck)
		if (t > 45 || t < 0)
			return false;

	m_theboard[move.tileTo] = m_theboard[move.tileFrom];
	m_theboard[move.tileFrom] = TILE_EMPTY;
	for (int t : move.tilesJumped)
		m_theboard[t] = TILE_EMPTY;

	if (move.pieceKinged)
	{
		if (m_theboard[move.tileTo] == TILE_WHITE)
			m_theboard[move.tileTo] = TILE_WHITE_KING;
		if (m_theboard[move.tileTo] == TILE_BLACK)
			m_theboard[move.tileTo] = TILE_BLACK_KING;
	}

	return true;
}

MoveList Board::getMoveMoves(const int tile)
{
	MoveList ml = {{}};

	// prevent issues with bad indexes
	if (tile > 40 || tile < 5)
		return ml;
	
	for (int i : std::vector<int>{4,5,-4,5})
	{
		if (m_theboard[tile+i] == TILE_EMPTY)
		{
			if (isTileOnWhiteKingLine(tile+i) && m_theboard[tile] == TILE_WHITE) {
				ml.push_back(Move(tile,tile+i,std::vector<int>(),true));
			} else if (isTileOnBlackKingLine(tile+i) && m_theboard[tile] == TILE_BLACK) {
				ml.push_back(Move(tile,tile+i,std::vector<int>(),true));
			} else {
				ml.push_back(Move(tile,tile+i,std::vector<int>(),false));
			}
		}
	}

	return ml;
}

MoveList Board::getJumpMoves(const int tile)
{
	// general idea:
	// 	iterate over an expanding movelist
	// 	finding all the jumps that can be made from a specific move's end tile
	// 	creating new Moves for those new moves
	// 	appending them to the end of the movelist
	// 	then deleting the move that generated those new moves if any new moves were found
	// repeat until the end of the movelist is reached
	// i.e. until all moves in the movelist have no possible moves that can be made from them
	
	MoveList ml = {{}};
	ml.push_back(Move(tile,tile,std::vector<int>(),false));
	auto enditer = std::end(ml);
	auto iter = std::begin(ml);
	while (iter != enditer)
	{
		if (!(*iter).pieceKinged) { // kinging a piece ends the turn
			bool newjump = false;
			int tt = (*iter).tileTo;
			for (int i=4;i<6;i++) {
				if ((m_theboard[tt] == TILE_WHITE || m_theboard[tt] == TILE_WHITE_KING) && (m_theboard[tt+i] == TILE_BLACK || m_theboard[tt+i] == TILE_BLACK_KING) && (m_theboard[tt+i+i] == TILE_EMPTY))
				{
					std::vector<int> tj = (*iter).tilesJumped;
					tj.push_back(tt+i);
					bool kinged = isTileOnWhiteKingLine(tt+i+i) && m_theboard[tt] == TILE_WHITE;
					ml.push_back(Move(tile,tt+i+i,tj,kinged));
					newjump = true;
				}
				if ((m_theboard[tt] == TILE_BLACK_KING) && (m_theboard[tt+i] == TILE_WHITE || m_theboard[tt+i] == TILE_WHITE_KING) && (m_theboard[tt+i+i] == TILE_EMPTY))
				{
					std::vector<int> tj = (*iter).tilesJumped;
					tj.push_back(tt+i);
					ml.push_back(Move(tile,tt+i+i,tj,false));
					newjump = true;
				}
			}
			for (int i=-4;i>-6;i--) {
				if ((m_theboard[tt] == TILE_BLACK || m_theboard[tt] == TILE_BLACK_KING) && (m_theboard[tt+i] == TILE_WHITE || m_theboard[tt+i] == TILE_WHITE_KING) && (m_theboard[tt+i+i] == TILE_EMPTY))
				{
					std::vector<int> tj = (*iter).tilesJumped;
					tj.push_back(tt+i);
					bool kinged = isTileOnBlackKingLine(tt+i+i) && m_theboard[tt] == TILE_BLACK;
					ml.push_back(Move(tile,tt+i+i,tj,kinged));
					newjump = true;
				}
				if ((m_theboard[tt] == TILE_WHITE_KING) && (m_theboard[tt+i] == TILE_BLACK || m_theboard[tt+i] == TILE_BLACK_KING) && (m_theboard[tt+i+i] == TILE_EMPTY))
				{
					std::vector<int> tj = (*iter).tilesJumped;
					tj.push_back(tt+i);
					ml.push_back(Move(tile,tt+i+i,tj,false));
					newjump = true;
				}
			}
			if (newjump) {
				iter = ml.erase(iter);
			} else {
				++iter;
			}
		} else {
			++iter;
		}
	}
	// if that works...I'll be quite relieved.
	
	// check to see if we found any moves
	if (!ml.empty() && (ml[0].tileTo == tile))
		return MoveList();
	
	return ml;
}

MoveList Board::getPieceMoves(const int tile)
{
	MoveList ml = {{}};

	MoveList jml = getJumpMoves(tile);
	if (!jml.empty())
	{
		for (Move m : jml)
			ml.push_back(m);
	} else {
		MoveList mml = getMoveMoves(tile);
		for (Move m : mml)
			ml.push_back(m);
	}

	return ml;
}

MoveList Board::getPlayerMoves(const PlayerType player)
{
	MoveList ml = {{}};

	// a piece can not move without jumping if another piece can jump
	// remember that getPieceMoves will filter out all non-jump moves if the piece can jump
	bool jumps = false;
	for (int tile : m_theboard)
	{
		MoveList tml = getPieceMoves(tile);
		if (jumps)
		{
			for (Move m : tml)
			{
				if (!m.tilesJumped.empty())
					ml.push_back(m);
			}
		} else {
			for (Move m : tml)
			{
				if (!m.tilesJumped.empty())
					jumps = true;
				ml.push_back(m);
			}
		}
	}

	return ml;
}

int Board::countPiecesOfPlayer(const PlayerType targetPlayerType)
{
	int count = 0;
	if (targetPlayerType == PLAYER_WHITE) {
		count += countPiecesOfType(TILE_WHITE) + countPiecesOfType(TILE_WHITE_KING);
	} else {
		count += countPiecesOfType(TILE_BLACK) + countPiecesOfType(TILE_BLACK_KING);
	}
	return count;
}

int Board::countPiecesOfType(const TileType targetTileType)
{
	int count = 0;
	for (TileType tt : m_theboard) {
		if (tt == targetTileType)
			count++;
	}
	return count;
}

bool Board::hasPlayerWon(const PlayerType targetPlayerType)
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

bool Board::paddedToCoords(const int tile, CoordsType &coords)
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

bool Board::coordsToPadded(const CoordsType coords, int &tile)
{
	// do the coords point to an actual tile on the board?
	if (coords[0] > 7 || coords[1] > 7)
		return false;
	// do the coords point to a legal tile?
	if (coords[0] % 2) {
		if (coords[1] % 2)
			return false;
	} else {
		if (coords[1] % 2 == 0)
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

bool Board::isTileOnWhiteKingLine(const int tile)
{
	if (tile == 37 || tile == 38 || tile == 39 || tile == 40)
		return true;
	else
		return false;
}

bool Board::isTileOnBlackKingLine(const int tile)
{
	if (tile == 5 || tile == 6 || tile == 7 || tile == 8)
		return true;
	else
		return false;
}

// class CheckersGame
// ------------------

Board CheckersGame::getBoard()
{
	return m_board;
}

PlayerType CheckersGame::whoIsToMove()
{
	return m_playertomove;
}

int CheckersGame::getTurnNumber()
{
	return m_turnnumber;
}

WinnerType CheckersGame::getWinStatus()
{
	return m_winstatus;
}

MoveList CheckersGame::getListOfMoves()
{
	return m_listofmoves;
}

int CheckersGame::getMovesWithoutCapture()
{
	return m_moveswithoutcapture;
}

bool CheckersGame::makeMove(const Move &themove)
{
	// valid indexes?
	std::vector<int> tocheck = themove.tilesJumped;
	tocheck.push_back(themove.tileFrom);
	tocheck.push_back(themove.tileTo);
	for (int t : tocheck)
		if (t > 45 || t < 0)
			return false;

	// valid tile type given the current player?
	//if ((whoIsToMove() == PLAYER_WHITE && (m_board[themove.tileFrom] != TILE_WHITE || m_board[themove.tileFrom] != TILE_WHITE_KING)) || (whoIsToMove() == PLAYER_BLACK && (m_board[themove.tileFrom] != TILE_BLACK || m_board[themove.tileFrom] != TILE_BLACK_KING)))
	//	return false;
	// note: I don't think the above is needed becuase checking if the move is legal for the current player would filter out exactly what the above is filtering out

	// is the move legal?
	MoveList playermoves = m_board.getPlayerMoves(whoIsToMove());
	bool good = false;
	for (Move m : playermoves)
	{
		if (m.tileTo == themove.tileTo && m.tileFrom == themove.tileFrom && m.tilesJumped == themove.tilesJumped && m.pieceKinged == themove.pieceKinged)
		{
			good = true;
			break;
		}
	}
	if (!good)
		return false; // the move isn't legal!

	// make the move and update the stats!
	m_board.applyMove(themove);
	m_turnnumber++;
	if (themove.tilesJumped.empty()) {
		m_moveswithoutcapture++;
	} else {
		m_moveswithoutcapture = 0;
	}
	if (m_playertomove == PLAYER_WHITE)
	{
		m_playertomove = PLAYER_BLACK;
	} else {
		m_playertomove = PLAYER_WHITE;
	}
	m_listofmoves.push_back(themove);
	updateWinStatus();

	return true;
}

void CheckersGame::agreeToADraw()
{
	m_winstatus = DRAW;
}

void CheckersGame::updateWinStatus()
{
	if (m_board.hasPlayerWon(PLAYER_WHITE)) {
		m_winstatus = WHITE_WON;
	} else if (m_board.hasPlayerWon(PLAYER_BLACK)) {
		m_winstatus = BLACK_WON;
	} else if (m_moveswithoutcapture > m_moveswithoutcapturelimit) {
		m_winstatus = DRAW;
	} else {
		m_winstatus = GAME_IN_PROGRESS;
	}
}

}

