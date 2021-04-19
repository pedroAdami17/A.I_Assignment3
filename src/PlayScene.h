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
#include "DecisionTree.h"
#include "CCETree.h"
#include "CloseCombatEnemy.h"
#include "Sprite.h"
#include <vector>

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

	CloseCombatEnemy* m_pCCE;
	Ship* m_pShip;
	std::vector<Obstacle*> m_pObstacles;
	int obstacle2Lives = 3, obstacle3Lives = 3, obstacle4Lives = 4;
	Target* m_pTarget;
	void m_CheckEnemyLOS(Enemy* enemy, DisplayObject* player);
	void m_CheckEnemyRadius(Enemy* enemy, DisplayObject* player);

	CCETree* cceTree;

	//heuristic
	Heuristic currentHeuristic;

	std::vector<Tile*> m_pOpenList;
	std::vector<Tile*> m_pClosedList;
	std::vector<Tile*> m_pPathLists;

};

#endif /* defined (__PLAY_SCENE__) */