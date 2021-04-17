#include "CCEAttackAction.h"
#include <iostream>

CCEAttackAction::CCEAttackAction()
{
	name = "CCE Attack Action";
}

CCEAttackAction::~CCEAttackAction()
= default;

void CCEAttackAction::Action()
{
	std::cout << "CCE Attack Action" << std::endl;
}
