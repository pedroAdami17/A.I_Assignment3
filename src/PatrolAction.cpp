#include "PatrolAction.h"
#include <iostream>

PatrolAction::PatrolAction()
{
	name = "Patrol Action";
}

PatrolAction::~PatrolAction()
= default;

void PatrolAction::Action()
{
	std::cout << "Preforming Patrol Action" << std::endl;
}
