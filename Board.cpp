//
//  Board.h
//

#include "Board.h"

#include <cassert>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "BoardSize.h"
#include "BoardValue.h"

using namespace std;



char boardGetAt (const Board& board_in,
                 int row_in, int column_in)
{
	assert(isOnBoard(row_in, column_in));

	return board_in.places[row_in][column_in];
}

void boardSetAt (Board& board_in,
                 int row_in, int column_in,
                 char value_in)
{
	assert(isOnBoard(row_in, column_in));
	assert(isBoardValueValid(value_in));

	board_in.places[row_in][column_in] = value_in;
}

void boardClear (Board& board_in)
{
	for(int r = 0; r < BOARD_SIZE; r++)
	{
		for(int c = 0; c < BOARD_SIZE; c++)
		{
			board_in.places[r][c] = BOARD_VALUE_EMPTY;
		}
	}
}

void boardLoad (Board& board_in,
                const string& filename_in)
{
	assert(filename_in != "");

	// open file with name filename_in
	// fin will read from that file
	// use fin like you use cin
	ifstream fin(filename_in);

	if(!fin)
	{
		cout << "Error: Could not open file \"" << filename_in << "\"" << endl;
		return;  // end function immediately
	}

	// read in the board size
	string line;
	int board_size_read;
	fin >> board_size_read;
	if(!fin)
	{
		cout << "Error: File \"" << filename_in << "\" does not start with board size" << endl;
		return;  // end function immediately
	}
	if(board_size_read != BOARD_SIZE)
	{
		cout << "Error: File \"" << filename_in << "\" has board size "
		     << board_size_read << ", but must be " << BOARD_SIZE << endl;
		return;  // end function immediately
	}
	assert(fin);
	string dummy;
	getline(fin, dummy);  // throw away whatever else is on the line

	// read in board state
	bool is_print_error = true;
	for(int r = 0; r < BOARD_SIZE; r++)
	{
		string line;
		getline(fin, line);
		if(!fin)
		{
			if(is_print_error)
			{
				cout << "Error: Could not read line " << r
				     << " of file \"" << filename_in << "\"" << endl;
				cout << "       Replacing with '.'s" << endl;
				is_print_error = false;
			}
			line = string(BOARD_VALUE_EMPTY, BOARD_SIZE);  // set to '.'s
		}
		else if((int)(line.length()) < BOARD_SIZE)
		{
			if(is_print_error)
			{
				cout << "Error: Line " << r << " of file \"" << filename_in
				     << "\" only contains " << line.length()
				     << " / " << BOARD_SIZE << " characters" << endl;
				cout << "       Adding '.'s to end" << endl;
				is_print_error = false;
			}
			line += string(BOARD_VALUE_EMPTY, BOARD_SIZE);  // add '.'s
		}

		for(int c = 0; c < BOARD_SIZE; c++)
		{
			if(isBoardValueValid(line[c]))
				boardSetAt(board_in, r, c, line[c]);
			else
			{
				boardSetAt(board_in, r, c, BOARD_VALUE_EMPTY);
				if(is_print_error)
				{
					cout << "Error: Line " << r << ", character " << c
						 << " of file \"" << filename_in
						 << "\" is an invalid '" << line[c] << "' character" << endl;
					cout << "       Substituting '" << BOARD_VALUE_EMPTY << "'" << endl;
					is_print_error = false;
				}
			}
		}
	}

	// file will be closed automatically when fin goes out of scope
}

int boardCountWithValue (const Board& board_in,
                         char value_in)
{
	assert(isBoardValueValid(value_in));

	int count = 0;

	for(int r = 0; r < BOARD_SIZE; r++)
	{
		for(int c = 0; c < BOARD_SIZE; c++)
		{
			if(board_in.places[r][c] == value_in)
				count++;
		}
	}

	return count;
}

void boardPrint (const Board& board_in)
{
	boardPrintColumnLetters();

	for(int r = 0; r < BOARD_SIZE; r++)
	{
		boardPrintRowNumber(r);
		cout << " ";

		for(int c = 0; c < BOARD_SIZE; c++)
		{
			if(board_in.places[r][c] == BOARD_VALUE_EMPTY &&
			   boardIsAlignedForStarPoint(r) &&
			   boardIsAlignedForStarPoint(c))
			{
				cout << "*";
			}
			else
				cout << board_in.places[r][c];
			cout << " ";
		}

		boardPrintRowNumber(r);
		cout << endl;
	}

	boardPrintColumnLetters();
}

bool boardIsAlignedForStarPoint (int index_in)
{
	assert(index_in >= 0);

	int center_modulus = (BOARD_SIZE / 2) % STAR_POINT_SPACING;
	int index_modulus  = index_in         % STAR_POINT_SPACING;

	if(index_modulus == center_modulus)
		return true;
	else
		return false;
}

void boardPrintRowNumber (int row_in)
{
	cout << right << setw(2) << row_in;
}

void boardPrintColumnLetters ()
{
	cout << "   ";  // space for row numbers

	// column headings
	for(int c = 0; c < BOARD_SIZE; c++)
	{
		char letter = 'A' + c;
		if(letter >= 'I')
			letter++;
		if(letter >= 'O')
			letter++;
		cout << letter << " ";
	}

	// don't need to leave space at end of line
	cout << endl;
}

