#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "Enemy.h"
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

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

	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();

	if (m_shipIsMoving)
	{
		m_moveShip();
	}

	m_CheckEnemyLOS(m_pShip);
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
		m_findShortestPath();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_M))
	{
		m_shipIsMoving = true;
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pInstructionsLabel_1 = new Label("Press F to find the shortest path.", "Consolas", 12, blue, glm::vec2(400.0f, 80.0f));
	m_pInstructionsLabel_1->setParent(this);
	addChild(m_pInstructionsLabel_1);

	m_pInstructionsLabel_2 = new Label("Press M to move the ship to the target.", "Consolas", 12, blue, glm::vec2(400.0f, 100.0f));
	m_pInstructionsLabel_2->setParent(this);
	addChild(m_pInstructionsLabel_2);

	m_pInstructionsLabel_3 = new Label("Press H to show the grid.", "Consolas", 12, blue, glm::vec2(400.0f, 120.0f));
	m_pInstructionsLabel_3->setParent(this);
	addChild(m_pInstructionsLabel_3);

	m_pInstructionsLabel_4 = new Label("Press R to reset the positions.", "Consolas", 12, blue, glm::vec2(400.0f, 140.0f));
	m_pInstructionsLabel_4->setParent(this);
	addChild(m_pInstructionsLabel_4);


	m_buildGrid();
	auto offset = glm::vec2(Config::TILE_SIZE * 0.5f, Config::TILE_SIZE * 0.5f);
	currentHeuristic = EUCLIDEAN;

	//add the ship to the scene as a start project
	m_pShip = new Ship();
	m_pShip->getTransform()->position = glm::vec2(200.0f, 300.0f);
	addChild(m_pShip);

	//add the Enemy to the scene 
	m_pEnemy = new Enemy();
	m_pEnemy->getTransform()->position = glm::vec2(400.0f, 300.0f);
	addChild(m_pEnemy, 2);

	//add the walls as obstacles for the ship
	m_pWall_1 = new Wall();
	m_pWall_1->getTransform()->position = m_getTile(3, 0)->getTransform()->position + offset;
	m_pWall_1->setGridPosition(3, 0);
	m_getTile(3, 0)->setTileStatus(IMPASSABLE);
	addChild(m_pWall_1);

	m_pWall_2 = new Wall();
	m_pWall_2->getTransform()->position = m_getTile(3, 1)->getTransform()->position + offset;
	m_pWall_2->setGridPosition(3, 1);
	m_getTile(3, 1)->setTileStatus(IMPASSABLE);
	addChild(m_pWall_2);
	
	m_pWall_3 = new Wall();
	m_pWall_3->getTransform()->position = m_getTile(3, 2)->getTransform()->position + offset;
	m_pWall_3->setGridPosition(3, 2);
	m_getTile(3, 2)->setTileStatus(IMPASSABLE);
	addChild(m_pWall_3);

	m_pWall_4 = new Wall();
	m_pWall_4->getTransform()->position = m_getTile(3, 3)->getTransform()->position + offset;
	m_pWall_4->setGridPosition(3, 3);
	m_getTile(3, 3)->setTileStatus(IMPASSABLE);
	addChild(m_pWall_4);

	m_pWall_5 = new Wall();
	m_pWall_5->getTransform()->position = m_getTile(3, 4)->getTransform()->position + offset;
	m_pWall_5->setGridPosition(3, 4);
	m_getTile(3, 4)->setTileStatus(IMPASSABLE);
	addChild(m_pWall_5);

	m_pWall_6 = new Wall();
	m_pWall_6->getTransform()->position = m_getTile(3, 5)->getTransform()->position + offset;
	m_pWall_6->setGridPosition(3, 5);
	m_getTile(3, 5)->setTileStatus(IMPASSABLE);
	addChild(m_pWall_6);

	m_pWall_7 = new Wall();
	m_pWall_7->getTransform()->position = m_getTile(4, 5)->getTransform()->position + offset;
	m_pWall_7->setGridPosition(4, 5);
	m_getTile(4,5)->setTileStatus(IMPASSABLE);
	addChild(m_pWall_7);

	m_pWall_8 = new Wall();
	m_pWall_8->getTransform()->position = m_getTile(5, 5)->getTransform()->position + offset;
	m_pWall_8->setGridPosition(5, 5);
	m_getTile(5, 5)->setTileStatus(IMPASSABLE);
	addChild(m_pWall_8);

	m_pWall_9 = new Wall();
	m_pWall_9->getTransform()->position = m_getTile(6, 5)->getTransform()->position + offset;
	m_pWall_9->setGridPosition(6, 5);
	m_getTile(6, 5)->setTileStatus(IMPASSABLE);
	addChild(m_pWall_9);

	m_pWall_10 = new Wall();
	m_pWall_10->getTransform()->position = m_getTile(6, 6)->getTransform()->position + offset;
	m_pWall_10->setGridPosition(6,6);
	m_getTile(6,6)->setTileStatus(IMPASSABLE);
	addChild(m_pWall_10);

	m_pWall_11 = new Wall();
	m_pWall_11->getTransform()->position = m_getTile(6, 7)->getTransform()->position + offset;
	m_pWall_11->setGridPosition(6, 7);
	m_getTile(6, 7)->setTileStatus(IMPASSABLE);
	addChild(m_pWall_11);

	m_pWall_12 = new Wall();
	m_pWall_12->getTransform()->position = m_getTile(6, 8)->getTransform()->position + offset;
	m_pWall_12->setGridPosition(6, 8);
	m_getTile(6, 8)->setTileStatus(IMPASSABLE);
	addChild(m_pWall_12);

	m_pWall_13 = new Wall();
	m_pWall_13->getTransform()->position = m_getTile(6, 9)->getTransform()->position + offset;
	m_pWall_13->setGridPosition(6, 9);
	m_getTile(6, 9)->setTileStatus(IMPASSABLE);
	addChild(m_pWall_13);

	m_pWall_14 = new Wall();
	m_pWall_14->getTransform()->position = m_getTile(6, 10)->getTransform()->position + offset;
	m_pWall_14->setGridPosition(6, 10);
	m_getTile(6, 10)->setTileStatus(IMPASSABLE);
	addChild(m_pWall_14);

	m_pWall_15 = new Wall();
	m_pWall_15->getTransform()->position = m_getTile(6, 11)->getTransform()->position + offset;
	m_pWall_15->setGridPosition(6, 11);
	m_getTile(6, 11)->setTileStatus(IMPASSABLE);
	addChild(m_pWall_11);

	m_pWall_16 = new Wall();
	m_pWall_16->getTransform()->position = m_getTile(7, 11)->getTransform()->position + offset;
	m_pWall_16->setGridPosition(7, 11);
	m_getTile(7, 11)->setTileStatus(IMPASSABLE);
	addChild(m_pWall_16);

	m_pWall_17 = new Wall();
	m_pWall_17->getTransform()->position = m_getTile(8, 11)->getTransform()->position + offset;
	m_pWall_17->setGridPosition(8, 11);
	m_getTile(8, 11)->setTileStatus(IMPASSABLE);
	addChild(m_pWall_17);

	m_pWall_18 = new Wall();
	m_pWall_18->getTransform()->position = m_getTile(14,10)->getTransform()->position + offset;
	m_pWall_18->setGridPosition(14,10);
	m_getTile(14,10)->setTileStatus(IMPASSABLE);
	addChild(m_pWall_18);

	m_pWall_19 = new Wall();
	m_pWall_19->getTransform()->position = m_getTile(14, 11)->getTransform()->position + offset;
	m_pWall_19->setGridPosition(14, 11);
	m_getTile(14, 11)->setTileStatus(IMPASSABLE);
	addChild(m_pWall_19);

	m_pWall_20 = new Wall();
	m_pWall_20->getTransform()->position = m_getTile(14, 12)->getTransform()->position + offset;
	m_pWall_20->setGridPosition(14, 12);
	m_getTile(14, 12)->setTileStatus(IMPASSABLE);
	addChild(m_pWall_20);

	m_computeTileCosts();

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

	static int survivorPosition[] = { m_pShip->getTransform()->position.x, m_pShip->getTransform()->position.y };
	if (ImGui::SliderInt2("Start Position", survivorPosition, 0, 800))
	{
		m_pShip->getTransform()->position.x = survivorPosition[0];
		m_pShip->getTransform()->position.y = survivorPosition[1];
		//// Row adjustment
		//if (StartPosition[1] > Config::ROW_NUM - 1)
		//{
		//	StartPosition[1] = Config::ROW_NUM - 1;
		//}

		//SDL_RenderClear(Renderer::Instance()->getRenderer());
		///*m_getTile(m_pShip->getGridPosition())->setTileStatus(UNVISITED);
		//m_pShip->getTransform()->position = m_getTile(StartPosition[0], StartPosition[1])->getTransform()->position + offset;
		//m_pShip->setGridPosition(StartPosition[0], StartPosition[1]);
		//m_getTile(m_pShip->getGridPosition())->setTileStatus(START);*/
		//SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
		//SDL_RenderPresent(Renderer::Instance()->getRenderer());
	}

	static int enemyPosition[] = { m_pEnemy->getTransform()->position.x, m_pEnemy->getTransform()->position.y };
	if (ImGui::SliderInt2("Enemy Position", enemyPosition, 0, 800))
	{
		m_pEnemy->getTransform()->position.x = enemyPosition[0];
		m_pEnemy->getTransform()->position.y = enemyPosition[1];
		//// Row adjustment
		//if (enemyPosition[1] > Config::ROW_NUM - 1)
		//{
		//	enemyPosition[1] = Config::ROW_NUM - 1;
		//}

		//SDL_RenderClear(Renderer::Instance()->getRenderer());
		///*m_getTile(m_pTarget->getGridPosition())->setTileStatus(UNVISITED);*/
		//m_pEnemy->setGridPosition(targetPosition[0], targetPosition[1]);
		//m_getTile(m_pTarget->getGridPosition())->setTileStatus(GOAL);
		//m_computeTileCosts();
		//SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
		//SDL_RenderPresent(Renderer::Instance()->getRenderer());
	}

	ImGui::Separator();

	if (ImGui::Button("Start"))
	{
		m_findShortestPath();
	}

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

void PlayScene::m_buildGrid()
{
	auto tileSize = Config::TILE_SIZE;

	// add tiles to the grid
	for (int row = 0; row < Config::ROW_NUM; ++row)
	{
		for (int col = 0; col < Config::COL_NUM; ++col)
		{
			Tile* tile = new Tile(); // create empty tile
			tile->getTransform()->position = glm::vec2(col * tileSize, row * tileSize);
			tile->setGridPosition(col, row);
			addChild(tile);
			tile->addLabels();
			tile->setEnabled(false);
			m_pGrid.push_back(tile);
		}
	}

	// create references for each tile to its neighbours
	for (int row = 0; row < Config::ROW_NUM; ++row)
	{
		for (int col = 0; col < Config::COL_NUM; ++col)
		{
			Tile* tile = m_getTile(col, row);

			// Topmost row
			if (row == 0)
			{
				tile->setNeighbourTile(TOP_TILE, nullptr);
			}
			else
			{
				tile->setNeighbourTile(TOP_TILE, m_getTile(col, row - 1));
			}

			// rightmost column
			if (col == Config::COL_NUM - 1)
			{
				tile->setNeighbourTile(RIGHT_TILE, nullptr);
			}
			else
			{
				tile->setNeighbourTile(RIGHT_TILE, m_getTile(col + 1, row));
			}

			// bottommost row
			if (row == Config::ROW_NUM - 1)
			{
				tile->setNeighbourTile(BOTTOM_TILE, nullptr);
			}
			else
			{
				tile->setNeighbourTile(BOTTOM_TILE, m_getTile(col, row + 1));
			}

			// leftmost  column
			if (col == 0)
			{
				tile->setNeighbourTile(LEFT_TILE, nullptr);
			}
			else
			{
				tile->setNeighbourTile(LEFT_TILE, m_getTile(col - 1, row));
			}
		}
	}

	std::cout << m_pGrid.size() << std::endl;
}

//void PlayScene::m_computeTileCosts()
//{
//	float distance, dx, dy;
//
//	for (auto tile : m_pGrid)
//	{
//		switch (currentHeuristic)
//		{
//		case MANHATTAN:
//			//Manhattan Distance
//			dx = abs(tile->getGridPosition().x - m_p->getGridPosition().x);
//			dy = abs(tile->getGridPosition().y - m_pTarget->getGridPosition().y);
//			distance = dx + dy;
//			break;
//		case EUCLIDEAN:
//			//Euclidean Distance
//			distance = Util::distance(m_pTarget->getGridPosition(), tile->getGridPosition());
//			break;
//		}
//
//		tile->setTileCost(distance);
//	}
//}

//void PlayScene::m_findShortestPath()
//{
//	if (m_pPathLists.empty())
//	{
//		// add start position to the open list
//		auto startTile = m_getTile(m_pShip->getGridPosition());
//		startTile->setTileStatus(OPEN);
//		m_pOpenList.push_back(startTile);
//
//		bool goalFound = false;
//
//		// Loop until the OpenList is empty or the Goal is found
//		while (!m_pOpenList.empty() && !goalFound)
//		{
//			auto min = INFINITY;
//			Tile* minTile;
//			int minTileIndex = 0;
//			int count = 0;
//
//			std::vector<Tile*> neighbourList;
//			for (int index = 0; index < NUM_OF_NEIGHBOUR_TILES; ++index)
//			{
//				neighbourList.push_back(m_pOpenList[0]->getNeighbourTile(NeighbourTile(index)));
//			}
//
//			for (auto neighbour : neighbourList)
//			{
//				if (neighbour->getTileStatus() != GOAL)
//				{
//					if (neighbour->getTileCost() < min)
//					{
//						min = neighbour->getTileCost();
//						minTile = neighbour;
//						minTileIndex = count;
//					}
//					count++;
//				}
//				else
//				{
//					minTile = neighbour;
//					m_pPathLists.push_back(minTile);
//					goalFound = true;
//					break;
//				}
//			}
//
//			for (auto neighbour : neighbourList)
//			{
//				if (neighbour->getTileStatus() != IMPASSABLE)
//				{
//					if (neighbour->getTileCost() < min)
//					{
//						min = neighbour->getTileCost();
//						m_pOpenList.push_back(minTile);
//						minTile = neighbour;
//						minTileIndex = count;
//					}
//					count++;
//				}
//				else 
//				{
//					minTile = neighbour;
//					m_pClosedList.push_back(minTile);
//					minTile->setTileStatus(CLOSED);
//				}
//			}
//
//			// remove the reference of the current tile in the open list
//			m_pPathLists.push_back(m_pOpenList[0]);
//			m_pOpenList.pop_back(); // empties the open list
//
//			//adding the min tile to the open list
//				m_pOpenList.push_back(minTile);
//				minTile->setTileStatus(OPEN);
//				neighbourList.erase(neighbourList.begin() + minTileIndex);
//			
//			// push all remaining neighbours onto the closed list
//			for (auto neighbour : neighbourList)
//			{
//				if (neighbour->getTileStatus() == UNVISITED)
//				{
//					neighbour->setTileStatus(CLOSED);
//					m_pClosedList.push_back(neighbour);
//				}
//			}
//		}
//
//		m_displayPathList();
//	}
//}

void PlayScene::m_setGridEnabled(bool state)
{
	for (auto tile : m_pGrid)
	{
		tile->setEnabled(state);
		tile->setLabelsEnabled(state);
	}

	if (state == false)
	{
		SDL_RenderClear(Renderer::Instance()->getRenderer());
	}
	m_isGridEnabled = state;
}

bool PlayScene::m_getGridEnabled() const
{
	return m_isGridEnabled;
}

Tile* PlayScene::m_getTile(const int col, const int row)
{
	return m_pGrid[(row * Config::COL_NUM) + col];
}

Tile* PlayScene::m_getTile(const glm::vec2 grid_position)
{
	const auto col = grid_position.x;
	const auto row = grid_position.y;
	return m_pGrid[(row * Config::COL_NUM) + col];
}

void PlayScene::m_moveShip()
{
	auto offest = glm::vec2(Config::TILE_SIZE * 0.5f, Config::TILE_SIZE * 0.5f);
	if (moveCounter < m_pPathLists.size())
	{
		m_pShip->getTransform()->position = m_getTile(m_pPathLists[moveCounter]->getGridPosition())->getTransform()->position + offest;
		//m_pShip->setGridPosition(m_pPathLists[moveCounter]->getGridPosition().x, m_pPathLists[moveCounter]->getGridPosition().y);
		if (Game::Instance()->getFrames() % 20 == 0)
		{
			moveCounter++;
		}
	}

	else
	{
		m_shipIsMoving = false;
	}
}

void PlayScene::m_CheckEnemyLOS(DisplayObject* survivor_object)
{
	//if enemy to survivor distance is less than or equal to LOS distance
	auto EnemyToSurvivorDistance = Util::distance(m_pEnemy->getTransform()->position, survivor_object->getTransform()->position);
	if (EnemyToSurvivorDistance <= m_pEnemy->getLOSDistance())
	{
		std::vector<DisplayObject*> contactList;
		for (auto object : getDisplayList())
		{
			//Check if object is farther than the target
			auto EnemyToObjectDistance = Util::distance(m_pEnemy->getTransform()->position, object->getTransform()->position);

			if (EnemyToObjectDistance <= EnemyToSurvivorDistance)
			{
				if ((object->getType() != m_pEnemy->getType()) && (object->getType() != survivor_object->getType()))
				{
					contactList.push_back(object);
				}
			}
		}
		contactList.push_back(survivor_object); // add the survivor at the end of the list.
		auto hasLOS = CollisionManager::LOSCheck(m_pEnemy->getTransform()->position,
			m_pEnemy->getTransform()->position + m_pEnemy->getCurrentDirection() * m_pEnemy->getLOSDistance(), contactList, survivor_object);

		m_pEnemy->setHasLOS(hasLOS);
	}
}