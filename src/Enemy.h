#pragma once
#ifndef __ENEMY__
#define __ENEMY__

#include "TextureManager.h"
#include <glm/vec4.hpp>
#include "Agent.h"
#include "Line.h"

class Enemy : public Agent
{
public:
	Enemy();
	~Enemy();

	// Inherited via GameObject
	void draw() override;
	void update() override;
	void clean() override;

	void turnRight();
	void turnLeft();
	void moveForward();
	void moveBack();

	void move();

	// getters
	float getMaxSpeed() const;

	// setters
	void setMaxSpeed(float newSpeed);
	void setLeftWhisker(glm::vec2 start, glm::vec2 end);
	void setRightWhisker(glm::vec2 start, glm::vec2 end);

private:
	void m_checkBounds();
	void m_reset();

	// steering behaviours
	float m_maxSpeed;
	float m_turnRate;
	Line m_leftWhisker;
	Line m_rightWhisker;

};



#endif
