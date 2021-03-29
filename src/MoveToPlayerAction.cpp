#include "MoveToPlayerAction.h"
#include <iostream>

MoveToPlayerAction::MoveToPlayerAction()
{
	name = "Move To Player Action";
}

MoveToPlayerAction::~MoveToPlayerAction()
= default;

void MoveToPlayerAction::Action()
{
	std::cout << "Preforming Move Player Action" << std::endl;
}
