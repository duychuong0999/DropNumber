#pragma once
#include "gamestatebase.h"
#include "Block.h"
#include "Board.h"
#include<queue>

using namespace std;

class Sprite2D;
class Sprite3D;
class Text;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

	
	void SetNewPostionForBullet();

	void AnimTextScale(float deltaTime);
	void Spawn();
	void Move(float deltaTime);
	void CheckCombine();
	void CombineBlock(int x,int y,bool isCombineLeft, bool isCombineRight, bool isCombineUnder,int numCombine, float del);
	void AddDropQueue(int x, int y);
	void DropColumn(float deltaTime);

private:

	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Sprite2D> m_BoardImage;
	std::shared_ptr<Sprite2D> m_SpawnImage;
	std::shared_ptr<Text> m_TapToStart;
	float m_SizeTapToStart;
	float m_PosXTapToStart;
	float slowSpeed = 30;
	float fastSpeed = 200;
	int currentLine = 2;
	int PosYMove;
	bool isScaleUp = true;
	bool isFirstTouched = false;
	bool isSpawn = false;
	bool isMove = false;
	bool isFast = false;
	bool isCombine = false;
	bool isCombineLeft = false;
	bool isCombineRight = false;
	bool isCombineUnder = false;
	bool isDropColumn = false;
	int numCombine = 0;
	int CombinePosX;
	int CombinePosY;

	Block mainBlock;
	Board board;
	queue<Block> blockQueue;
	std::list<Block*>dropQueue;
};

