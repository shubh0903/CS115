//
//  main.cpp
//
//  Name: __________
//  Student Number: __________
//

#include <cassert>
#include <string>
#include <iostream>
#include <iomanip>

#include "PlaceString.h"
#include "BoardSize.h"
#include "BoardValue.h"
#include "Search.h"
#include "Board.h"

using namespace std;

static const float KOMI = 7.5f;

void printEnd (const Board& board_in, 
               const string moves_in[],
               int move_count_in);


int main ()
{
	cout << "Welcome to my Go game!" << endl;
	string name;
	while(name == "")
	{
		cout << "Enter your name:  ";
		getline(cin, name);
	}
	cout << "Hello " << name << ".  You will play black." << endl;
	cout << endl;

	Board board;
	boardClear(board);

	const int MOVE_COUNT_MAX = 1000;
	string moves[MOVE_COUNT_MAX];
	int move_count = 0;

	bool playing = true;
	while(playing)
	{
		boardPrint(board);
		cout << "Enter your move:  ";
		string move_string;
		getline(cin, move_string);

		if(move_string == "quit")
			playing = false;
		else if(move_string == "load")
		{
			string filename;
			cout << "Enter the file name:  ";
			getline(cin, filename);
			boardLoad(board, filename);
		}
		else if(move_string == "pass")
		{
			cout << "Black passed" << endl;
			cout << "White passed" << endl;
		}
		else if(isPlaceStringWellFormed(move_string))
		{
			int row    = placeStringToRow   (move_string);
			int column = placeStringToColumn(move_string);

			if(isOnBoard(row, column))
			{
				if(boardGetAt(board, row, column) == BOARD_VALUE_EMPTY)
				{
					cout << "Black played a stone at row " << row << ", column " << column << endl;
					boardSetAt(board, row, column, BOARD_VALUE_BLACK);

					moves[move_count] = move_string;
					move_count++;

					cout << "White passed" << endl;
				}
				else
					cout << "Forbidden: Place row " << row << ", column " << column << " is not empty" << endl;
			}
			else
				cout << "Forbidden: Place row " << row << ", column " << column << " is outside board" << endl;
		}
		else
			cout << "\"" << move_string << "\" is ill-formed." << endl;
		cout << endl;
	}

	boardPrint(board);
	cout << endl;
	mySort(moves, move_count);
	printEnd(board, moves, move_count);

	cout << "Goodbye, " << name << "!" << endl;
	return 0;
}



void printEnd (const Board& board_in, 
               const string moves_in[],
               int move_count_in)
{
	float black_score = boardCountWithValue(board_in, BOARD_VALUE_BLACK) + 0.0f;
	float white_score = boardCountWithValue(board_in, BOARD_VALUE_WHITE) + KOMI;
	if(black_score > white_score)
		cout << "Black wins " << black_score << " to " << white_score << " (with komi)" << endl;
	else if(black_score < white_score)
		cout << "White wins " << white_score << " to " << black_score << " (with komi)" << endl;
	else
		cout << "Tie game" << endl;
	cout << endl;

	cout << "Black played " << move_count_in << " stones total" << endl;
	if(move_count_in > 0)
	{
		int smallest = sortedFindSmallest(moves_in, move_count_in);
		int largest  = sortedFindLargest (moves_in, move_count_in);
		int index_K9 = binarySearch(moves_in, move_count_in, "K9");

		cout << "Smallest place was \"" << moves_in[smallest] << "\" (index " << smallest << ")" << endl;
		cout << "Largest place was \""  << moves_in[largest]  << "\" (index " << largest  << ")" << endl;
		if(index_K9 == VALUE_NOT_FOUND)
			cout << "Did not play at \"K9\"" << endl;
		else
			cout << "Did play at \"K9\"" << endl;
	}
}

