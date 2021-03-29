#pragma once
#ifndef __CONDITION__
#define __CONDITION__
class Condition
{
public:
	Condition(const bool condition = false);
	~Condition();

	virtual bool Test();
	void SetCondition(const bool condition);

private:
	bool m_condition{};
};

#endif /* defined (__CONDITION__) */
