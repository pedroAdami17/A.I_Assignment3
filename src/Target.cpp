#include "Target.h"


#include "SoundManager.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "Util.h"
#include "PlayScene.h"


Target::Target()
{
	TextureManager::Instance()->load("../Assets/textures/Player/survivor-idle_shotgun_0.png", "player");

	const auto size = TextureManager::Instance()->getTextureSize("player");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(100.0f, 100.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;
	setType(TARGET);
	setRotation(0.0f);
	setTurnRate(10.0f);
}

Target::~Target()
= default;

void Target::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance()->draw("player", x, y, 0, 255, true);
}

void Target::update()
{
	m_move();
	m_checkBounds();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		//setRotation(getRotation() + getTurnRate());
		getTransform()->position.y += m_speed;
	}
	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
	{
		//setRotation(50);
		getTransform()->position.y -= m_speed;
	}
	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		getTransform()->position.x -= m_speed;
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		getTransform()->position.x += m_speed;
	}
}

void Target::clean()
{
}

float Target::getTurnRate() const
{
	return m_turnRate;
}

void Target::setTurnRate(const float rate)
{
	m_turnRate = rate;
}

float Target::getAccelerationRate() const
{
	return m_accelerationRate;
}

void Target::setAccelerationRate(const float rate)
{
	m_accelerationRate = rate;
}

void Target::setOrientation(const glm::vec2 orientation)
{
	m_orientation = orientation;
}

void Target::setRotation(const float angle)
{
	m_rotationAngle = angle;

	const auto offset = -90.0f;
	const auto angle_in_radians = (angle + offset) * Util::Deg2Rad;

	const auto x = cos(angle_in_radians);
	const auto y = sin(angle_in_radians);

	// convert the angle to a normalized vector and store it in Orientation
	setOrientation(glm::vec2(x, y));
}

float Target::getRotation() const
{
	return m_rotationAngle;
}


void Target::m_move()
{
	getTransform()->position = getTransform()->position + getRigidBody()->velocity * 5.0f;
}

void Target::m_checkBounds()
{
}

void Target::m_reset()
{
}