#pragma once

#include "Sprite2D.h"
#include "ResourceManagers.h"
#include<math.h>

using namespace std;

class Block
{
public:
	Block();
	~Block();

	std::shared_ptr<Sprite2D> block;
	float value = -1;
	int PosX;
	int PosY;
	GLfloat positionX;
	GLfloat positionY;	
	int DesPosY;
	bool isMove = false;
	void SetInfo(float typeValue);
};
