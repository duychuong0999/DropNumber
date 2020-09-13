#include "Block.h"
#include<iostream>

Block::Block()
{
}

Block::~Block()
{
}

void Block::SetInfo(float typeValue){
	value = typeValue;
	float valueP = pow(2, value);
	std::shared_ptr<Texture> texture = ResourceManagers::GetInstance()->GetTexture("DropNumberTextures/" + to_string((int)valueP));
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	block = std::make_shared<Sprite2D>(model, shader, texture);
}