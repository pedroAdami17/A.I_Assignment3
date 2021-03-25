#pragma once
#ifndef __WALLS__
#define __WALLS__

#include "DisplayObject.h"
#include "NavigationObject.h"
#include "TextureManager.h"

class Wall final : public NavigationObject
{
public:
	Wall();
	~Wall();

	// Inherited via GameObject
	void draw() override;
	void update() override;
	void clean() override;

private:
	void m_move();
	void m_checkBounds();
	void m_reset();
};
#endif 
