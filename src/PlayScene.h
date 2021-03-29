#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Button.h"
#include "Enemy.h"
#include "Heuristic.h"
#include "Label.h"
#include "Obstacle.h"
#include "ship.h"
#include "SpaceShip.h"
#include "Target.h"
#include "Tile.h"
#include "StateMachine.h"
#include "Condition.h"
#include "FloatCondition.h"

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

	Enemy* m_pEnemy;
	Ship* m_pShip;
	Obstacle* m_pObstacle1;
	Target* m_pTarget;
	void m_CheckEnemyLOS(DisplayObject* object);


	//sate machine properties 

	Condition* m_pHasLOSCondition;
	Condition* m_pIsWithinDectectionRadius;
	FloatCondition* m_pIsWithinCombatRange;

	StateMachine* m_pStateMachine;
	void m_buildStateMachine();

	//heuristic
	Heuristic currentHeuristic;

	std::vector<Tile*> m_pOpenList;
	std::vector<Tile*> m_pClosedList;
	std::vector<Tile*> m_pPathLists;

};

#endif /* defined (__PLAY_SCENE__) */