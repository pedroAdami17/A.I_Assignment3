#pragma once
#ifndef __TARGET__
#define __TARGET__

#include <SDL_scancode.h>

#include "DisplayObject.h"

class Target final : public DisplayObject 
{
public:
	Target();
	~Target();

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
};

#endif /* defined (__TARGET__) */