#include "Flee.h"
#include <iostream>

FleeAction::FleeAction()
{
	name = "Attack Action";
}

FleeAction::~FleeAction()
= default;

void FleeAction::Action()
{
	std::cout << "Preforming Flee Action" << std::endl;
}
