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

	///*if (CollisionManager::AABBCheck(m_pTarget, m_pObstacles.at(2)))
	//{
	//	obstacle2Lives--;
	//}*/
	//if (CollisionManager::AABBCheck(m_pTarget, m_pObstacles.at(3)))
	//{
	//	obstacle3Lives--;
	//}
	//if(CollisionManager::AABBCheck(m_pTarget, m_pObstacles.at(5)))
	//{
	//	obstacle4Lives--;
	//}

	for(auto obstacle : m_pObstacles)
	{
		if(CollisionManager::AABBCheck(m_pTarget, obstacle))
		{
			if(obstacle == m_pObstacles.at(2))
			{
				obstacle2Lives--;
			}
			else if(obstacle == m_pObstacles.at(3))
			{
				obstacle3Lives--;
			}
			else if(obstacle == m_pObstacles.at(4))
			{
				obstacle4Lives--;
			}
		}
	}


	for(auto i = m_pObstacles.begin(); i < m_pObstacles.end(); ++i)
	{
		if(i == m_pObstacles.at(2) && obstacle2Lives == 0)
		{
			removeChild(*i);
			delete *i;
			m_pObstacles.erase(i);
		}
		if (i == m_pObstacles.at(3) && obstacle3Lives == 0)
		{
			removeChild(*i);
			delete* i;
			m_pObstacles.erase(i);
		}
		if (i == m_pObstacles.at(4) && obstacle4Lives == 0)
		{
			removeChild(*i);
			delete* i;
			m_pObstacles.erase(i);
		}
	}

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

	m_pCCE = new CloseCombatEnemy();
	m_pCCE->getTransform()->position = glm::vec2(200.0f, 300.0f);
	addChild(m_pCCE, 2);

	m_pObstacles.push_back(new Obstacle());
	m_pObstacles.back()->getTransform()->position = glm::vec2(400.0f, 300.0f);
	addChild(m_pObstacles.back());

	m_pObstacles.push_back(new Obstacle());
	m_pObstacles.back()->getTransform()->position = glm::vec2(300.0f, 100.0f);
	addChild(m_pObstacles.back());
	
	m_pObstacles.push_back(new Obstacle());
	m_pObstacles.back()->getTransform()->position = glm::vec2(700.0f, 530.0f);
	addChild(m_pObstacles.back());
	
	m_pObstacles.push_back(new Obstacle());
	m_pObstacles.back()->getTransform()->position = glm::vec2(600.0f, 200.0f);
	addChild(m_pObstacles.back());

	m_pObstacles.push_back(new Obstacle());
	m_pObstacles.back()->getTransform()->position = glm::vec2(70.0f, 80.0f);
	addChild(m_pObstacles.back());

	m_pObstacles.push_back(new Obstacle());
	m_pObstacles.back()->getTransform()->position = glm::vec2(230.0f, 450.0f);
	addChild(m_pObstacles.back());

	m_pTarget = new Target();
	m_pTarget->getTransform()->position = glm::vec2(600.0f, 300.0f);
	addChild(m_pTarget);

	cceTree = new CCETree();
	cceTree->setAgent(m_pCCE);
	cceTree->DisplayTree();

	std::cout << "------------------------" << std::endl;
	std::cout << cceTree->MakeDecision() << std::endl;
	std::cout << "------------------------\n" << std::endl;

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

	ImGui::Begin("GAME3001 - Assignment 4", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	// Allow enemy rotation
	static int angle;
	if(ImGui::SliderInt("Enemy Direction", &angle, -360, 360))
	{
		m_pCCE->setCurrentHeading(angle);
	}

	ImGui::Separator();

	static int survivorPosition[] = { m_pTarget->getTransform()->position.x, m_pTarget->getTransform()->position.y };
	if (ImGui::SliderInt2("Start Position", survivorPosition, 0, 800))
	{
		m_pTarget->getTransform()->position.x = survivorPosition[0];
		m_pTarget->getTransform()->position.y = survivorPosition[1];
	}

	static int enemyPosition[] = { m_pCCE->getTransform()->position.x, m_pCCE->getTransform()->position.y };
	if (ImGui::SliderInt2("Enemy Position", enemyPosition, 0, 800))
	{
		m_pCCE->getTransform()->position.x = enemyPosition[0];
		m_pCCE->getTransform()->position.y = enemyPosition[1];

		std::cout << "------------------------" << std::endl;
		std::cout << cceTree->MakeDecision() << std::endl;
		std::cout << "------------------------\n" << std::endl;
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


void PlayScene::m_CheckEnemyLOS(DisplayObject* target_object) // move to the enemy some how for ease of coding
{
	// if ship to target distance is less than or equal to LOS Distance
	auto ShipToTargetDistance = Util::distance(m_pCCE->getTransform()->position, target_object->getTransform()->position);
	if (ShipToTargetDistance <= m_pCCE->getLOSDistance())
	{
		std::vector<DisplayObject*> contactList;
		for (auto object : getDisplayList())
		{
			// check if object is farther than than the target
			auto ShipToObjectDistance = Util::distance(m_pCCE->getTransform()->position, object->getTransform()->position);

			if (ShipToObjectDistance <= ShipToTargetDistance)
			{
				if ((object->getType() != m_pCCE->getType()) && (object->getType() != target_object->getType()))
				{
					contactList.push_back(object);
				}
			}
		}
		contactList.push_back(target_object); // add the target to the end of the list
		auto hasLOS = CollisionManager::LOSCheck(m_pCCE->getTransform()->position,
			m_pCCE->getTransform()->position + m_pCCE->getCurrentDirection() * m_pCCE->getLOSDistance(), contactList, target_object);

		m_pCCE->setHasLOS(hasLOS);
	}
}
