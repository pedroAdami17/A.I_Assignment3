#pragma once
#ifndef __ACTION__
#define __ACTION__

//Action interface
class Action
{
public:
	Action() = default;
	virtual ~Action() = default;

	virtual void Execute() = 0;
};
#endif /* defined (__ACTION__) */
