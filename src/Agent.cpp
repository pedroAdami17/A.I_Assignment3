#include "Agent.h"

#include "Util.h"

Agent::Agent()
{
}

Agent::~Agent()
= default;

glm::vec2 Agent::getTargetPosition() const
{
	return m_targetPosition;
}

glm::vec2 Agent::getCurrentDirection() const
{
	return m_currentDirection;
}

float Agent::getLOSDistance() const
{
	return m_LOSDistance;
}

bool Agent::hasLOS() const
{
	return m_hasLOS;
}

float Agent::getRadiusDistance() const
{
	return m_RadiusDistance;
}

bool Agent::hasRadius() const
{
	return m_hasRadius;
}

float Agent::getRange() const
{
	return m_Range;
}

bool Agent::hasRange() const
{
	return m_hasRange;
}

float Agent::getCurrentHeading() const
{
	return m_currentHeading;
}

glm::vec4 Agent::getLOSColour() const
{
	return m_LOSColour;
}

glm::vec4 Agent::getRadiusColour() const
{
	return m_RadiusColour;
}

void Agent::setTargetPosition(const glm::vec2 new_position)
{
	m_targetPosition = new_position;
}

void Agent::setCurrentDirection(const glm::vec2 new_direction)
{
	m_currentDirection = new_direction;
}

void Agent::setLOSDistance(const float distance)
{
	m_LOSDistance = distance;
}

void Agent::setHasLOS(const bool state)
{
	m_hasLOS = state;
	m_LOSColour = (m_hasLOS) ? glm::vec4(0, 1, 0, 1) : glm::vec4(1, 0, 0, 1);
}

void Agent::setRadiusDistance(const float radius)
{
	m_RadiusDistance = radius;
}

void Agent::setHasRadius(const bool state)
{
	m_hasRadius = state;
	m_RadiusColour = (m_hasRadius) ? glm::vec4(1, 1, 0, 1) : glm::vec4(0, 0, 1, 1);
}

void Agent::setRange(float range)
{
	m_Range = range;
}

void Agent::setHasRange(const bool state)
{
	m_Range = state;
}

void Agent::setCurrentHeading(const float heading)
{
	m_currentHeading = heading;
	m_changeDirection();
}

void Agent::setLOSColour(const glm::vec4 colour)
{
	m_LOSColour = colour;
}

void Agent::setRadiusColour(const glm::vec4 colour)
{
	m_RadiusColour = colour;
}

void Agent::m_changeDirection()
{
	const auto x = cos(m_currentHeading * Util::Deg2Rad);
	const auto y = sin(m_currentHeading * Util::Deg2Rad);
	m_currentDirection = glm::vec2(x, y);
}