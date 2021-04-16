#include "MoveToRange.h"
#include <iostream>

MoveToRangeAction::MoveToRangeAction()
{
	name = "Patrol Action";
}

MoveToRangeAction::~MoveToRangeAction()
= default;

void MoveToRangeAction::Action()
{
	std::cout << "Moving to Range" << std::endl;
}