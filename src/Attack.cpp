#include "Attack.h"
#include <iostream>

Attack::Attack()
= default;

Attack::~Attack()
= default;

void Attack::Execute()
{
	std::cout << "Preforming Attack Action" << std::endl;
}

