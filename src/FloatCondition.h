#pragma once
#ifndef __FLOAT_CONDITION__
#define __FLOAT_CONDITION__
#include "Condition.h"

class FloatCondition :public Condition
{
public:
	FloatCondition(const float min_value = 0.0f, const float max_value= 1.0f);
	~FloatCondition();

	void setTestValue(const float value);

	bool Test() override;
private:
	float m_minValue;
	float m_maxValue;
	float m_testValue;
};

#endif /* defined (__FLOAT_CONDITION__) */
