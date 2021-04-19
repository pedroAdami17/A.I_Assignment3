#pragma once
#ifndef __AGENT__
#define __AGENT__

#include "DisplayObject.h"
#include <glm/vec4.hpp>

class Agent : public DisplayObject
{
public:
	Agent();
	~Agent();

	// Inherited via GameObject
	void draw() override = 0;
	void update() override = 0;
	void clean() override = 0;

	// getters
	glm::vec2 getTargetPosition() const;
	glm::vec2 getCurrentDirection() const;
	float getLOSDistance() const; 
	bool hasLOS() const;
	float getRadiusDistance() const;
	bool hasRadius() const;
	float getRange() const;
	bool hasRange() const;
	float getCurrentHeading() const;
	glm::vec4 getLOSColour() const;
	glm::vec4 getRadiusColour() const;

	// setters
	void setTargetPosition(glm::vec2 new_position);
	void setCurrentDirection(glm::vec2 new_direction);
	void setLOSDistance(float distance);
	void setHasLOS(bool state);
	void setRadiusDistance(float radius);
	void setHasRadius(bool state);
	void setRange(float range);
	void setHasRange(bool state);
	void setCurrentHeading(float heading);
	void setLOSColour(glm::vec4 colour);
	void setRadiusColour(glm::vec4 colour);

private:
	void m_changeDirection();
	float m_currentHeading;
	glm::vec2 m_currentDirection;
	glm::vec2 m_targetPosition;

	//LOS
	float m_LOSDistance;
	bool m_hasLOS;
	glm::vec4 m_LOSColour;

	//Radius
	float m_RadiusDistance;
	bool m_hasRadius;
	glm::vec4 m_RadiusColour;

	//Range
	float m_Range;
	bool m_hasRange;
};

#endif /* defined (__AGENT__)*/
