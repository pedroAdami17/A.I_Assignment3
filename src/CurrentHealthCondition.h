#pragma once
#ifndef __CURRENT_HEALTH_CONDITION__
#define __CURRENT_HEALTH_CONDITION__
#include "ConditionNode.h"

class CurrentHealthCondition : public ConditionNode
{
public:
	CurrentHealthCondition(bool health = false);
	virtual ~CurrentHealthCondition();

	//Getters and Setters
	void setHasHealth(bool state);

	virtual bool Condition() override;
private:
	bool m_hasHealth;
};

#endif // defined (__CURRENT_HEALTH_CONDITION__)
