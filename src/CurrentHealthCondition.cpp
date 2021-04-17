#include "CurrentHealthCondition.h"

CurrentHealthCondition::CurrentHealthCondition(const bool health)
{
	setHasHealth(health);
	name = "Current Health Condition";
}

CurrentHealthCondition::~CurrentHealthCondition()
= default;

void CurrentHealthCondition::setHasHealth(const bool state)
{
	m_hasHealth = state;
	data = state;
}

bool CurrentHealthCondition::Condition()
{
	return m_hasHealth;
}
