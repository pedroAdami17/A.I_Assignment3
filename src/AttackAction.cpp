#include "AttackAction.h"
#include <iostream>

AttackAction::AttackAction()
{
	name = "Attack Action";
}

AttackAction::~AttackAction()
= default;

void AttackAction::Action()
{
	std::cout << "Preforming Attack Action" << std::endl;
}
