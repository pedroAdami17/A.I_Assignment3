#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "Transition.h"

// required for IMGUI
#include "Enemy.h"
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"
#include "Patrol.h"
#include "MoveToLOS.h"
#include "Attack.h"
#include "MoveToPlayer.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();

	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
	
	drawDisplayList();

	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();

	m_CheckEnemyLOS(m_pTarget);

	m_pHasLOSCondition->SetCondition(m_pEnemy->hasLOS());
	m_pStateMachine->Update();
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	auto offset = glm::vec2(Config::TILE_SIZE * 0.5f, Config::TILE_SIZE * 0.5f);
	EventManager::Instance().update();

	//Scene changing functions
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}


	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_F))
	{
		//m_findShortestPath();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_M))
	{
		//m_shipIsMoving = true;
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

	m_pEnemy = new Enemy();
	m_pEnemy->getTransform()->position = glm::vec2(200.0f, 300.0f);
	addChild(m_pEnemy, 2);

	m_pObstacle1 = new Obstacle();
	m_pObstacle1->getTransform()->position = glm::vec2(400.0f, 300.0f);
	addChild(m_pObstacle1);

	//m_pShip = new Ship();
	//m_pShip->getTransform()->position = glm::vec2(600.0f, 300.0f);
	//addChild(m_pShip);

	m_pTarget = new Target();
	m_pTarget->getTransform()->position = glm::vec2(600.0f, 300.0f);
	addChild(m_pTarget);

	//test state machine
	m_buildStateMachine();

	//Background music
	SoundManager::Instance().load("../Assets/audio/bgMusic.ogg", "background_music", SOUND_MUSIC);
	SoundManager::Instance().playMusic("background_music", -1);
	SoundManager::Instance().setMusicVolume(15);
}

void PlayScene::GUI_Function()
{
	//TODO: We need to deal with this
	auto offset = glm::vec2(Config::TILE_SIZE * 0.5f, Config::TILE_SIZE * 0.5f);

	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("GAME3001 - Assignment 3", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	// Allow enemy rotation
	static int angle;
	if(ImGui::SliderInt("Enemy Direction", &angle, -360, 360))
	{
		m_pEnemy->setCurrentHeading(angle);
	}

	ImGui::Separator();

	static int survivorPosition[] = { m_pTarget->getTransform()->position.x, m_pTarget->getTransform()->position.y };
	if (ImGui::SliderInt2("Start Position", survivorPosition, 0, 800))
	{
		m_pTarget->getTransform()->position.x = survivorPosition[0];
		m_pTarget->getTransform()->position.y = survivorPosition[1];

		
	}

	static int enemyPosition[] = { m_pEnemy->getTransform()->position.x, m_pEnemy->getTransform()->position.y };
	if (ImGui::SliderInt2("Enemy Position", enemyPosition, 0, 800))
	{
		m_pEnemy->getTransform()->position.x = enemyPosition[0];
		m_pEnemy->getTransform()->position.y = enemyPosition[1];
	}

	ImGui::Separator();

	ImGui::SameLine();

	if (ImGui::Button("Reset"))
	{

	}

	ImGui::Separator();


	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}


void PlayScene::m_CheckEnemyLOS(DisplayObject* target_object)
{
	// if ship to target distance is less than or equal to LOS Distance
	auto ShipToTargetDistance = Util::distance(m_pEnemy->getTransform()->position, target_object->getTransform()->position);
	if (ShipToTargetDistance <= m_pEnemy->getLOSDistance())
	{
		std::vector<DisplayObject*> contactList;
		for (auto object : getDisplayList())
		{
			// check if object is farther than than the target
			auto ShipToObjectDistance = Util::distance(m_pEnemy->getTransform()->position, object->getTransform()->position);

			if (ShipToObjectDistance <= ShipToTargetDistance)
			{
				if ((object->getType() != m_pEnemy->getType()) && (object->getType() != target_object->getType()))
				{
					contactList.push_back(object);
				}
			}
		}
		contactList.push_back(target_object); // add the target to the end of the list
		auto hasLOS = CollisionManager::LOSCheck(m_pEnemy->getTransform()->position,
			m_pEnemy->getTransform()->position + m_pEnemy->getCurrentDirection() * m_pEnemy->getLOSDistance(), contactList, target_object);

		m_pEnemy->setHasLOS(hasLOS);
	}
}

void PlayScene::m_buildStateMachine()
{
	// define conditions
	m_pHasLOSCondition = new Condition();
	m_pIsWithinDectectionRadius = new Condition();
	m_pIsWithinCombatRange = new FloatCondition(0.0f, 2.0f);

	// define states
	State* patrolState = new State();
	State* moveToPlayerState = new State();
	State* moveToLOSState = new State();
	State* attackState = new State();

	// define Transitions
	Transition* moveToPlayerTransition = new Transition(m_pHasLOSCondition, moveToPlayerState);
	Transition* moveToLOSTransition = new Transition(m_pIsWithinDectectionRadius, moveToLOSState);
	Transition* attackTransition = new Transition(m_pIsWithinCombatRange, attackState);

	// defined actions
	Patrol* patrolAction = new Patrol();
	MoveToLOS* moveToLOSAction = new MoveToLOS();
	MoveToPlayer* moveToPlayerAction = new MoveToPlayer();
	Attack* attackAction = new Attack();

	// setup Patrol State
	patrolState->addTransition(moveToPlayerTransition);
	patrolState->addTransition(moveToLOSTransition);
	patrolState->setAction(patrolAction);

	// setup MoveToPlayer State
	moveToPlayerState->addTransition(attackTransition);
	moveToPlayerState->addTransition(moveToLOSTransition);
	moveToPlayerState->setAction(moveToPlayerAction);

	// setup MoveToLOS State
	moveToLOSState->addTransition(moveToPlayerTransition);
	moveToLOSState->setAction(moveToLOSAction);

	// setup Attack State
	attackState->addTransition(moveToPlayerTransition);
	attackState->addTransition(moveToLOSTransition);
	attackState->setAction(attackAction);

	m_pStateMachine = new StateMachine();
	m_pStateMachine->setCurrentState(patrolState);
}
