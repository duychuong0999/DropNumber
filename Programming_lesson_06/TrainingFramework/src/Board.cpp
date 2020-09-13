#include "Board.h"
#include<iostream>

Board::Board()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			block[i][j].value = -1;
		}
	}
}

Board::~Board()
{
}

int Board::getPosDrop(int line) {
	for (int i = 0; i < maxRow; i++)
	{
		if (block[line][i].value == -1) {
			return i;
		}		
	}
	return (maxRow - 1);
}

bool Board::CheckGameOver() {
	for (int i = 0; i < 4; i++)
	{
		if (block[i][5].value != -1) return true;
	}
	return false;
}