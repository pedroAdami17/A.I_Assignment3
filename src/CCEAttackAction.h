#pragma once
#ifndef __CCE_ATTACK_ACTION__
#define __CCE_ATTACK_ACTION__
#include "ActionNode.h"

class CCEAttackAction :public ActionNode
{
public:
	CCEAttackAction();
	virtual ~CCEAttackAction();

	virtual void Action() override;
private:

};
#endif /* defined (__CCE_ATTACK_ACTION__)*/
