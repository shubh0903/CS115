//
//  BoardSize.cpp
//

#include "BoardSize.h"



bool isOnBoard (int row_in, int column_in)
{
	if(row_in < 0)
		return false;
	if(row_in >= BOARD_SIZE)
		return false;
	if(column_in < 0)
		return false;
	if(column_in >= BOARD_SIZE)
		return false;
	return true;
}
