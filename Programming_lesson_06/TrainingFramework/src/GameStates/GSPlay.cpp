#include "GSPlay.h"
#include "Block.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include<time.h>

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("DropNumberTextures/Background");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//board
	texture = ResourceManagers::GetInstance()->GetTexture("DropNumberTextures/Board");
	m_BoardImage = std::make_shared<Sprite2D>(model, shader, texture);
	m_BoardImage->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BoardImage->SetSize(400, 480);
	//spawn
	texture = ResourceManagers::GetInstance()->GetTexture("DropNumberTextures/Spawn");
	m_SpawnImage = std::make_shared<Sprite2D>(model, shader, texture);
	m_SpawnImage->Set2DPosition(screenWidth / 2, screenHeight / 2 - 280);
	m_SpawnImage->SetSize(400, 100);

	//tap to start text
	m_SizeTapToStart = 1;
	m_PosXTapToStart = screenWidth / 2 - 70;
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Poppin");
	m_TapToStart = std::make_shared< Text>(shader, font, "Tap to Start", TEXT_COLOR::WHILE, m_SizeTapToStart);
	m_TapToStart->Set2DPosition(Vector2(screenWidth / 2-70, screenHeight / 2 -50));

	board = Board();
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			board.block[i][j].value = -1;
		}
	}
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (key == KEY_DOWN && bIsPressed && mainBlock.isMove) {
		mainBlock.isMove = false;
		mainBlock.block->Set2DPosition(mainBlock.positionX, mainBlock.DesPosY);
		//isSpawn = true;
		board.block[currentLine][PosYMove] = mainBlock;
		board.block[currentLine][PosYMove].PosX = currentLine;
		board.block[currentLine][PosYMove].PosY = PosYMove;
		board.block[currentLine][PosYMove].positionX = mainBlock.positionX;
		board.block[currentLine][PosYMove].positionY = mainBlock.DesPosY;
		blockQueue.push(board.block[currentLine][PosYMove]);
		CheckCombine();
	}
	else isFast = false;

	if (key == KEY_LEFT && bIsPressed && mainBlock.isMove) {
		if (currentLine > 0) {
			currentLine -= 1;
			mainBlock.positionX = screenWidth / 2 + (currentLine - 2) * 75;
			mainBlock.block->Set2DPosition(mainBlock.positionX, mainBlock.positionY);
			PosYMove = board.getPosDrop(currentLine);
			mainBlock.DesPosY = screenHeight / 2 + 185 - PosYMove * 75;
		}
	}
	if (key == KEY_RIGHT && bIsPressed && mainBlock.isMove) {
		if (currentLine < 4) {
			currentLine += 1;
			mainBlock.positionX = screenWidth / 2 + (currentLine - 2) * 75;
			mainBlock.block->Set2DPosition(mainBlock.positionX, mainBlock.positionY);
			PosYMove = board.getPosDrop(currentLine);
			mainBlock.DesPosY = screenHeight / 2 + 185 - PosYMove * 75;
		}
	}

}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	if (bIsPressed && !isFirstTouched) {
		isFirstTouched = true;
		isSpawn = true;
	}
}

void GSPlay::Update(float deltaTime)
{
	AnimTextScale(deltaTime);
	Spawn();
	Move(deltaTime);
	CombineBlock(CombinePosX, CombinePosY, isCombineLeft, isCombineRight, isCombineUnder, numCombine, deltaTime);
	DropColumn(deltaTime);
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	m_BoardImage->Draw();
	m_SpawnImage->Draw();
	if (!isFirstTouched) {
		m_TapToStart->Draw();
	}
	if (mainBlock.isMove) {
		mainBlock.block->Draw();
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (board.block[i][j].value != -1) {
				board.block[i][j].block->Draw();
			}
		}
	}
}

void GSPlay::SetNewPostionForBullet()
{
}

void GSPlay::AnimTextScale(float deltaTime) {
	if (!isFirstTouched) {
		if (m_SizeTapToStart >= 1.2) {
			isScaleUp = false;
		}
		else if (m_SizeTapToStart <= 1) isScaleUp = true;
		if (isScaleUp) {
			m_SizeTapToStart += 0.5f * deltaTime;
			m_PosXTapToStart -= 37.5 * deltaTime;
		}
		else {
			m_SizeTapToStart -= 0.75 * deltaTime;
			m_PosXTapToStart += 56.25 * deltaTime;
		}
		std::shared_ptr<Shaders> shader = ResourceManagers::GetInstance()->GetShader("TextShader");
		std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Poppin");
		m_TapToStart = std::make_shared<Text>(shader, font, "Tap to Start", TEXT_COLOR::WHILE, m_SizeTapToStart);
		m_TapToStart->Set2DPosition(Vector2(m_PosXTapToStart, screenHeight / 2 - 50));
	}
}

void GSPlay::Spawn() {
	if (isSpawn) {
		currentLine = 2;
		srand((int)time(0));
		isSpawn = false;
		mainBlock = Block();
		int value = 1 + rand() % (5);
		mainBlock.SetInfo(value);
		mainBlock.positionX = screenWidth / 2;
		mainBlock.positionY = screenHeight / 2 - 280;
		mainBlock.block->Set2DPosition(mainBlock.positionX, mainBlock.positionY);
		mainBlock.block->SetSize(70, 70);
		PosYMove = board.getPosDrop(currentLine);
		mainBlock.DesPosY = screenHeight / 2 + 185 - PosYMove * 75;
		mainBlock.isMove = true;
	}
}

void GSPlay::Move(float deltaTime) {
	if (mainBlock.isMove) {
		if (mainBlock.positionY < mainBlock.DesPosY) {
			mainBlock.positionY = mainBlock.positionY + slowSpeed * deltaTime;
		}
		else {
			mainBlock.isMove = false;
			//isSpawn = true;
			board.block[currentLine][PosYMove] = mainBlock;
			board.block[currentLine][PosYMove].PosX = currentLine;
			board.block[currentLine][PosYMove].PosY = PosYMove;
			board.block[currentLine][PosYMove].positionX = mainBlock.positionX;
			board.block[currentLine][PosYMove].positionY = mainBlock.DesPosY;
			blockQueue.push(board.block[currentLine][PosYMove]);
			CheckCombine();
		}
		mainBlock.block->Set2DPosition(mainBlock.positionX, mainBlock.positionY);
	}
}

void GSPlay::CheckCombine() {
	Block blockCheck = blockQueue.front();
	CombinePosX = blockCheck.PosX;
	CombinePosY = blockCheck.PosY;
	isCombineLeft = false;
	isCombineRight = false;
	isCombineUnder = false;
	numCombine = 0;
	if (CombinePosX > 0)
	{
		if (board.block[CombinePosX - 1][CombinePosY].value != -1 && blockCheck.value != -1) {
			if (blockCheck.value == board.block[CombinePosX - 1][CombinePosY].value)
			{
				isCombineLeft = true;
				numCombine += 1;
			}
		}
	}
	
	if (CombinePosX < 4)
	{
		if (board.block[CombinePosX + 1][CombinePosY].value != -1 && blockCheck.value != -1)
		{
			if (blockCheck.value == board.block[CombinePosX + 1][CombinePosY].value)
			{
				isCombineRight = true;
				numCombine += 1;
			}
		}
	}
	if (CombinePosY > 0)
	{
		if (board.block[CombinePosX][ CombinePosY - 1].value != -1 && blockCheck.value != -1)
		{
			if (blockCheck.value == board.block[CombinePosX][CombinePosY - 1].value)
			{
				isCombineUnder = true;
				numCombine += 1;
			}
		}
	}
	
	if (numCombine > 0)
	{
		isCombine = true;
		int blockCombineValue = board.block[CombinePosX][CombinePosY].value + numCombine;
		board.block[CombinePosX][CombinePosY].SetInfo(blockCombineValue);
		board.block[CombinePosX][CombinePosY].block->SetSize(70, 70);
		board.block[CombinePosX][CombinePosY].block->Set2DPosition(board.block[CombinePosX][CombinePosY].positionX, board.block[CombinePosX][CombinePosY].positionY);
	}
	else
	{
		blockQueue.pop();
		if (blockQueue.size() == 0)
		{			
			if (!board.CheckGameOver())
			{
				isSpawn = true;
			}
			else
			{
				GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_GameOver);
			}
		}
		else CheckCombine();
	}
}

void GSPlay::CombineBlock(int x, int y, bool isCombineLeft, bool isCombineRight, bool isCombineUnder, int numCombine, float deltaTime) {
	if (isCombine) {	
		for (int j = 5; j >= 0; j--)
		{
			for (int i = 0; i < 5; i++)
			{
				cout << board.block[i][j].value << " ";
			}
			cout << endl;
		}

		if (isCombineLeft) {
			if (board.block[x - 1][y].positionX < board.block[x][y].positionX) {
				board.block[x - 1][y].positionX += 150 * deltaTime;
				board.block[x - 1][y].block->Set2DPosition(board.block[x - 1][y].positionX, board.block[x - 1][y].positionY);
			}
		}
		if (isCombineRight) {
			if (board.block[x + 1][y].positionX > board.block[x][y].positionX) {
				board.block[x + 1][y].positionX -= 150 * deltaTime;
				board.block[x + 1][y].block->Set2DPosition(board.block[x + 1][y].positionX, board.block[x + 1][y].positionY);
			}
		}
		if (isCombineUnder) {
			if (board.block[x][y - 1].positionY > board.block[x][y].positionY) {				
				board.block[x][y - 1].positionY -= 150 * deltaTime;
				board.block[x][y - 1].block->Set2DPosition(board.block[x][y - 1].positionX, board.block[x][y - 1].positionY);
			}
		}
		if ((!isCombineLeft || board.block[x - 1][y].positionX >= board.block[x][y].positionX)
			&& (!isCombineRight || board.block[x + 1][y].positionX <= board.block[x][y].positionX)
			&& (!isCombineUnder || board.block[x][y - 1].positionY <= board.block[x][y].positionY))
		{
			isCombine = false;
			if (isCombineUnder) { board.block[x][y - 1].value = -1; AddDropQueue(x, y - 1); }		
			if (isCombineLeft) { board.block[x - 1][y].value = -1; AddDropQueue(x - 1, y); }
			if (isCombineRight) { board.block[x + 1][y].value = -1; AddDropQueue(x + 1, y);}

			isDropColumn = true;

		}
	}
}

void GSPlay::AddDropQueue(int x, int y) {
	int i = y + 1;
	for (int j = 5; j >= 0; j--)
	{
		for (int i = 0; i < 5; i++)
		{
			cout << board.block[i][j].value << " ";
		}
		cout << endl;
	}
	while (board.block[x][i].value != -1 && i < 7)
	{
		cout << "added";
		board.block[x][ i - 1] = board.block[x][i];
		board.block[x][i - 1].PosY -= 1;
		board.block[x][i - 1].DesPosY = board.block[x][i - 1].positionY + 75;
		dropQueue.push_back(&board.block[x][ i - 1]);
		blockQueue.push(board.block[x][i - 1]);
		i++;
	}
	if (i < board.maxRow)
	{
		board.block[x][i - 1].value = -1;
	}
}

void GSPlay::DropColumn(float deltaTime) {
	if (isDropColumn) {
		for (auto i :dropQueue)
		{
			//cout << i.positionY << " " << i.DesPosY << endl;
			if (i->positionY < i->DesPosY) {
				i->positionY += 130 * deltaTime;
				cout << i->positionY << " " << i->DesPosY << endl;
				i->block->Set2DPosition(i->positionX, i->positionY);
				cout << "drop1";
			}
		}
		bool check = true;
		for (auto i : dropQueue)
		{
			if (i->positionY < i->DesPosY) {
				check = false;
			}
		}

		if (check) {
			isDropColumn = false;
			while (dropQueue.size() > 0) dropQueue.pop_back();
			CheckCombine();
		}
	}
}