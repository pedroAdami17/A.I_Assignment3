#include "WaitBehindCover.h"
#include <ctime>
#include <iostream>

WaitBehindCover::WaitBehindCover()
{
	name = "Patrol Action";
}

WaitBehindCover::~WaitBehindCover()
= default;

void WaitBehindCover::Action()
{
	std::cout << "Waiting behind cover" << std::endl;
}