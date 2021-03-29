#include "Patrol.h"
#include <iostream>

Patrol::Patrol()
= default;
Patrol::~Patrol()
= default;

void Patrol::Execute()
{
	std::cout << "Preforming Patrol Action" << std::endl;
}
