#include "Walls.h"
#include "TextureManager.h"

Wall::Wall()
{
	TextureManager::Instance()->load("..Assets/textures/wall.png", "Wall");

	const auto size = TextureManager::Instance()->getTextureSize("Wall");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(300.0f, 400.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(WALL);
}

Wall::~Wall()
= default;

void Wall::draw()
{
	TextureManager::Instance()->draw("Wall", 
		getTransform()->position.x,getTransform()->position.y,0,255,true);
}

void Wall::update()
{
	m_move();
	m_checkBounds();
}

void Wall::clean()
{
}

void Wall::m_move()
{
	getTransform()->position = getTransform()->position + getRigidBody()->velocity * 5.0f;
}

void Wall::m_checkBounds()
{
}

void Wall::m_reset()
{
}
