// checkers.h
//
// Checkers subsystem for Clara

#ifndef CHECKERS_H
#define CHECKERS_H

#include <array>
#include <vector>

namespace Checkers {

// Checkers boards are represented via a padded array inside the checkers subsystem.
// The padded array is an array of length 46 and it maps to a checkerboard as follows:
// 
//    37  38  39  40
//  32  33  34  35
//    28  29  30  31
//  23  24  25  26
//    19  20  21  22
//  14  15  16  17
//    10  11  12  13
//  05  06  07  08  
//
// This way, incrementing the array by +5/+4/-4/-5 moves to the space up right/up left/down left/down right or a space that isn't on the board if the move is invalid.

typedef std::array<int,2> CoordsType;

enum PlayerType : short {
	PLAYER_BLACK, PLAYER_WHITE
};

enum TileType : short {
	TILE_BLACK, TILE_BLACK_KING, TILE_WHITE, TILE_WHITE_KING, TILE_EMPTY, TILE_INVALID
};

typedef std::array<TileType,46> BoardType;
const BoardType BlackAboveWhiteBoard = {TILE_INVALID, TILE_INVALID, TILE_INVALID, TILE_INVALID, TILE_INVALID, TILE_WHITE, TILE_WHITE, TILE_WHITE, TILE_WHITE, TILE_INVALID, TILE_WHITE, TILE_WHITE, TILE_WHITE, TILE_WHITE, TILE_WHITE, TILE_WHITE, TILE_WHITE, TILE_WHITE, TILE_INVALID, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_EMPTY, TILE_INVALID, TILE_BLACK, TILE_BLACK, TILE_BLACK, TILE_BLACK, TILE_BLACK, TILE_BLACK, TILE_BLACK, TILE_BLACK, TILE_INVALID, TILE_BLACK, TILE_BLACK, TILE_BLACK, TILE_BLACK, TILE_INVALID, TILE_INVALID, TILE_INVALID, TILE_INVALID, TILE_INVALID};

class Move {
	public:
		Move(int tileFrom, int tileTo, std::vector<int> tilesJumped, bool pieceKinged=false) : m_tileFrom(tileFrom), m_tileTo(tileTo), m_tilesJumped(tilesJumped), m_pieceKinged(pieceKinged) {};
		int tileFrom;
		int tileTo;
		std::vector<int> tilesJumped;
		bool pieceKinged;
};

typedef MoveList std::vector<Move>;

class Board {
	public:
		Board (BoardType theboard) : m_theboard(theboard);

		// get the board
		BoardType getBoard();

		// apply a move, does not check to see if it is legal or not
		bool applyMove(const Move &move);

		// functions to generate lists of possible moves
		private:
		MoveList getMoveMoves(int tile);
		MoveList getJumpMoves(int tile);
		public:
		// note: getPieceMoves does not check if other pieces of the same player can jump and restrict the piece in question's ability to move without jumping, but does remove non-jump moves from the list if the piece can jump
		MoveList getPieceMoves(int tile);
		MoveList getPlayerMoves(PlayerType player);

		// functions relating only to the board
		int countPiecesOfPlayer(PlayerType targetPlayerType);
		int countPiecesOfType(TileType targetTileType);
		// checks number of tiles and ability to move
		bool hasPlayerWon(PlayerType targetPlayerType);

		// static functions
		static CoordsType paddedToCoords(int tile);
		static int coordsToPadded(CoordsType coords);

		static bool isTileOnWhiteKingLine(int tile);
		static bool isTileOnBlackKingLine(int tile);
	private:
		BoardType m_theboard;
};

enum WinnerType : short {
	BLACK_WON, WHITE_WON, DRAW, GAME_IN_PROGRESS
};

class CheckersGame {
	public:
		CheckersGame(int movesWithoutCaptureLimit=50) : m_moveswithoutcapturelimit(movesWithoutCaptureLimit), m_board(BlackAboveWhiteBoard), m_playertomove(PLAYER_WHITE), m_turnnumber(0), m_moveswithoutcapture(0), m_listofmoves({{}}), m_winner(GAME_IN_PROGRESS) {};

		// get data
		Board getBoard();
		PlayerType whoIsToMove();
		int getTurnNumber();
		WinnerType getWinStatus();
		MoveList getListOfMoves();
		int getMovesWithoutCapture();

		// do things
		bool makeMove(const Move &themove);
		void agreeToADraw();
	private:
		Board m_board;
		PlayerType m_playertomove;
		int m_turnnumber;
		int m_moveswithoutcapture;
		int m_moveswithoutcapturelimit;
		MoveList m_listofmoves;
		WinnerType m_winstatus;

		void updateWinStatus();
};

}

#endif

