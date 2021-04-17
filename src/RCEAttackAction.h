#pragma once
#ifndef __RCE_ATTACK_ACTION__
#define __RCE_ATTACK_ACTION__
#include "ActionNode.h"

class RCEAttacKAction :public ActionNode
{
public:
	RCEAttacKAction();
	virtual ~RCEAttacKAction();

	virtual void Action() override;
private:

};
#endif /* defined (__RCE_ATTACK_ACTION__)*/

