#include "RCEAttackAction.h"
#include <iostream>

RCEAttacKAction::RCEAttacKAction()
{
	name = "RCE Attack Action";
}

RCEAttacKAction::~RCEAttacKAction()
= default;

void RCEAttacKAction::Action()
{
	std::cout << "RCE Attack Action" << std::endl;
}
