#pragma once

#include "Sprite2D.h"
#include "ResourceManagers.h"
#include<math.h>
#include "Block.h"

using namespace std;

class Board
{
public:
	Board();
	~Board();

	int maxRow = 7;
	Block block[5][7];

	int getPosDrop(int line);
	bool CheckGameOver();
};
