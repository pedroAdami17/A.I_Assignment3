#include "RangedCombatEnemy.h"
#include "glm/gtx/string_cast.hpp"
#include "PlayScene.h"
#include "TextureManager.h"
#include "Util.h"

RangedCombatEnemy::RangedCombatEnemy() : m_maxSpeed(10.0f)
{
	TextureManager::Instance()->load("../Assets/textures/Enemy/skeleton-idle_1.png", "ranged_enemy");

	auto size = TextureManager::Instance()->getTextureSize("ranged_enemy");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(200.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(ENEMY);

	setCurrentHeading(0.0f); // current facing angle
	setCurrentDirection(glm::vec2(1.0f, 0.0f)); //facing right
	m_turnRate = 5.0f; // 5 degrees per frame

	setLOSDistance(400.0f);
	setLOSColour(glm::vec4(1, 0, 0, 1));
}

RangedCombatEnemy::~RangedCombatEnemy()
= default;

void RangedCombatEnemy::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the ship
	TextureManager::Instance()->draw("ranged_enemy", x, y, getCurrentHeading(), 255, true);

	// draw LOS
	Util::DrawLine(getTransform()->position, getTransform()->position + getCurrentDirection() * getLOSDistance(), getLOSColour());
}


void RangedCombatEnemy::update()
{
	/*move();
	m_checkBounds();*/
}

void RangedCombatEnemy::clean()
{
}

void RangedCombatEnemy::turnRight()
{
	setCurrentHeading(getCurrentHeading() + m_turnRate);
	if (getCurrentHeading() >= 360)
	{
		setCurrentHeading(getCurrentHeading() - 360.0f);
	}
}

void RangedCombatEnemy::turnLeft()
{
	setCurrentHeading(getCurrentHeading() - m_turnRate);
	if (getCurrentHeading() < 0)
	{
		setCurrentHeading(getCurrentHeading() + 360.0f);
	}
}

void RangedCombatEnemy::moveForward()
{
	getRigidBody()->velocity = getCurrentDirection() * m_maxSpeed;
}

void RangedCombatEnemy::moveBack()
{
	getRigidBody()->velocity = getCurrentDirection() * -m_maxSpeed;
}

void RangedCombatEnemy::move()
{
	getTransform()->position += getRigidBody()->velocity;
	getRigidBody()->velocity *= 0.9f;
}


float RangedCombatEnemy::getMaxSpeed() const
{
	return m_maxSpeed;
}

void RangedCombatEnemy::setMaxSpeed(float newSpeed)
{
	m_maxSpeed = newSpeed;
}

void RangedCombatEnemy::m_checkBounds()
{

	if (getTransform()->position.x > Config::SCREEN_WIDTH)
	{
		getTransform()->position = glm::vec2(0.0f, getTransform()->position.y);
	}

	if (getTransform()->position.x < 0)
	{
		getTransform()->position = glm::vec2(800.0f, getTransform()->position.y);
	}

	if (getTransform()->position.y > Config::SCREEN_HEIGHT)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, 0.0f);
	}

	if (getTransform()->position.y < 0)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, 600.0f);
	}

}

void RangedCombatEnemy::m_reset()
{
	getRigidBody()->isColliding = false;
	const int halfWidth = getWidth() * 0.5f;
	const auto xComponent = rand() % (640 - getWidth()) + halfWidth + 1;
	const auto yComponent = -getHeight();
	getTransform()->position = glm::vec2(xComponent, yComponent);
}