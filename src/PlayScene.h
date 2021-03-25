#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Button.h"
#include "Heuristic.h"
#include "Label.h"
#include "Obstacle.h"
#include "ship.h"
#include "SpaceShip.h"
#include "Target.h"
#include "Tile.h"
#include "Walls.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	glm::vec2 m_mousePosition;
	bool m_isGridEnabled;

	Label* m_pInstructionsLabel_1;
	Label* m_pInstructionsLabel_2;
	Label* m_pInstructionsLabel_3;
	Label* m_pInstructionsLabel_4;
	Target* m_pTarget;
	Ship* m_pShip;
	Wall* m_pWall_1;
	Wall* m_pWall_2;
	Wall* m_pWall_3;
	Wall* m_pWall_4;
	Wall* m_pWall_5;
	Wall* m_pWall_6;
	Wall* m_pWall_7;
	Wall* m_pWall_8;
	Wall* m_pWall_9;
	Wall* m_pWall_10;
	Wall* m_pWall_11;
	Wall* m_pWall_12;
	Wall* m_pWall_13;
	Wall* m_pWall_14;
	Wall* m_pWall_15;
	Wall* m_pWall_16;
	Wall* m_pWall_17;
	Wall* m_pWall_18;
	Wall* m_pWall_19;
	Wall* m_pWall_20;

	// Pathfinding functions and objects
	void m_buildGrid();
	void m_computeTileCosts();
	void m_findShortestPath();
	void m_displayPathList();


	void m_setGridEnabled(bool state);
	bool m_getGridEnabled() const;
	std::vector<Tile*> m_pGrid;

	// convenience functions
	Tile* m_getTile(int col, int row);
	Tile* m_getTile(glm::vec2 grid__position);

	//heuristic
	Heuristic currentHeuristic;

	std::vector<Tile*> m_pOpenList;
	std::vector<Tile*> m_pClosedList;
	std::vector<Tile*> m_pPathLists;

	void m_moveShip();
	int moveCounter = 0;
	bool m_shipIsMoving = false;
};

#endif /* defined (__PLAY_SCENE__) */