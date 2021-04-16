#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void StartScene::start()
{
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pInstructionsLabel = new Label("Pedro Augusto ID: 101300796", "Consolas", 30, blue, glm::vec2(400.0f, 80.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);

	m_pInstructionsLabel = new Label("Alexander Thompson ID: 101311657", "Consolas", 30, blue, glm::vec2(400.0f, 150.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);

	m_pInstructionsLabel = new Label("Press 'F' to flee.", "Consolas", 20, blue, glm::vec2(400.0f, 180.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);
	m_pInstructionsLabel = new Label("Press 'W' to wait behind cover.", "Consolas", 20, blue, glm::vec2(400.0f, 210.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);
	m_pInstructionsLabel = new Label("Press 'M' to move to the player.", "Consolas", 20, blue, glm::vec2(400.0f, 240.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);


	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->getTransform()->position = glm::vec2(400.0f, 400.0f); 

	m_pStartButton->addEventListener(CLICK, [&]()-> void
	{
		m_pStartButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});
	
	m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pStartButton->setAlpha(128);
	});

	m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pStartButton->setAlpha(255);
	});
	addChild(m_pStartButton);

	
}

