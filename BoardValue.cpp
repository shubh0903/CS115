//
//  BoardValue.cpp
//

#include "BoardValue.h"



bool isBoardValueValid (char value_in)
{
	switch(value_in)
	{
	case BOARD_VALUE_EMPTY:
	case BOARD_VALUE_BLACK:
	case BOARD_VALUE_WHITE:
		return true;
	default:
		return false;
	}
}

