#pragma once
#ifndef __BULLET__
#define __BULLET__

#include <iostream>
#include <SDL_rect.h>
#include <SDL_scancode.h>

#include "DisplayObject.h"

class Bullet final : public DisplayObject
{
public:
	Bullet(SDL_Point spawnLoc = { 486, 560 }, int angle = 0) // Non default constructor
	{
		std::cout << "Constructing Player Bullet" << std::endl;
		this->m_rect.x = spawnLoc.x - 50;
		this->m_rect.y = spawnLoc.y;
		this->m_rect.w = 73;
		this->m_rect.h = 126;
		m_bulletAngle = angle;
	}

	Bullet();
	~Bullet();

	void SetBulletAngle(int angle)
	{
		m_bulletAngle = angle;
	}
	int GetBulletAngle()
	{
		return m_bulletAngle;
	}
	void SetLoc(SDL_Point loc)
	{
		m_rect.x = loc.x;
		m_rect.y = loc.y;
	}
	void Update()
	{
		if (m_bulletAngle == 0) // Bullets going Up
			m_rect.y -= 20;
		if (m_bulletAngle == 90) // Bullets going Right
			m_rect.x += 20;
		if (m_bulletAngle == 180) // Bullets going Down
			m_rect.y += 20;
		if (m_bulletAngle == 270) // Bullets going Left
			m_rect.x -= 20;
	}
	SDL_Rect* GetDst() { return &m_rect; }

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	int m_speed = 3;

	void setMaxSpeed(float speed);
	float getRotation() const;
	void setRotation(float angle);
	float getTurnRate() const;
	void setTurnRate(float rate);
	float getAccelerationRate() const;
	void setAccelerationRate(float rate);
	glm::vec2 getOrientation() const;
	void setOrientation(glm::vec2 orientation);

private:
	void m_move();
	void m_checkBounds();
	void m_reset();

	glm::vec2 m_orientation;
	float m_rotationAngle;
	float m_maxSpeed;
	float m_turnRate;
	float m_accelerationRate;

	SDL_Rect m_rect;
	int m_bulletAngle;
};

#endif /* defined (__BULLET__) */