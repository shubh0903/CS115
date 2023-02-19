//
//  Board.h
//

#pragma once

#include <string>

#include "BoardSize.h"
#include "BoardValue.h"



const int STAR_POINT_SPACING = 6;

//
//  Board
//
//  A record to represent the complete position of the game
//    board.  This is which colour of stone (if any) is at each
//    point.
//
struct Board
{
	char places[BOARD_SIZE][BOARD_SIZE];
};

char boardGetAt (const Board& board_in,
                 int row_in, int column_in);
void boardSetAt (Board& board_in,
                 int row_in, int column_in,
                 char value_in);
void boardClear (Board& board_in);
void boardLoad (Board& board_in,
                const std::string& filename_in);
int boardCountWithValue (const Board& board_in,
                         char value_in);

void boardPrint (const Board& board_in);
bool boardIsAlignedForStarPoint (int index_in);
void boardPrintRowNumber (int row_in);
void boardPrintColumnLetters ();
