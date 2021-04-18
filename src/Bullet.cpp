#include "Bullet.h"


#include "SoundManager.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "Game.h"
#include "Util.h"
#include "PlayScene.h"


Bullet::Bullet()
{
	TextureManager::Instance()->load("../Assets/textures/blue_laser.png", "bullet");

	const auto size = TextureManager::Instance()->getTextureSize("bullet");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(100.0f, 100.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;
	setType(BULLET);
}

Bullet::~Bullet()
= default;

void Bullet::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance()->draw("bullet", x, y, 0, 255, true);
}

void Bullet::update()
{
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_SPACE) && EventManager::Instance().m_bCanShoot)
	{
		EventManager::Instance().m_bCanShoot = false;
		//m_pBullet.push_back(new Bullet({m_pTarget.position()->x + 44, Target.position()->y - 20 })); //What should replace m_pTarger and Target? 
		//m_pBullet.shrink_to_fit(); //Why m_pBullet is not working(defined in Bullet.h)
	}
}

void Bullet::clean()
{
}


