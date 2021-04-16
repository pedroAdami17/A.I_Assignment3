#pragma once
#ifndef __WAIT_BEHIND_COVER__
#define __WAIT_BEHIND_COVER__
#include "ActionNode.h"

class WaitBehindCover :public ActionNode
{
public:
	WaitBehindCover();
	virtual ~WaitBehindCover();

	virtual void Action() override;
private:

};

#endif /* defined (__WAIT_BEHIND_COVER__)*/
