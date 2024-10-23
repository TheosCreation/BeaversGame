#include "Level.h"
#include "Warehouse.h"
#include "Beaver.h"

/*
	Creates a Level

	@author Jamuel Bocacao
	@param Vec2u: Size of Scene in Pixels
	@param sf::RenderWindow*: Window Handle
	@param bool: Whether previous Scene should be unloaded when this Scene is loaded
*/
Level::Level(Vec2u _sceneSize, sf::RenderWindow* _window, bool _bUnloadPreviousSceneOnLoad) : Scene(_sceneSize, _window, _bUnloadPreviousSceneOnLoad)
{
	m_world = make_shared<b2World>(b2Vec2_zero);
	m_world->SetContactListener(&m_listener);
	m_flowField = make_unique<FlowField>(Vec2i(0, 0), Vec2i(60, 34), 32);
}

/*
	Handles unloading Scene
*/
Level::~Level()
{
	m_world.reset();
}

/*
	Handles updating objects 

	@author Jamuel Bocacao
	@param float: Delta Time
	@param sf::RenderWindow*: Window Handle
*/
void Level::Update(float _fDeltaTime, sf::RenderWindow* _window)
{
	// Updates Scene Objects first
	Scene::Update(_fDeltaTime, _window);

	m_world->Step(_fDeltaTime, 8, 3);
}

void Level::SetPauseMenu(bool _bisActive)
{
	if (m_openPauseMenuEvent != nullptr)
	{
		m_openPauseMenuEvent->execute(_bisActive);
	}
}

/*
	Adds an Object to Scene

	@author Jamuel Bocacao
	@param Vec2f: Position of Object
	@param string: Texture File Path
	@param bool: Object can move
	@return weak_ptr<Object>: Reference to Game Object
*/
weak_ptr<Object> Level::AddObject(Vec2f _position, string _strTexturePath, bool _bIsStatic)
{
	auto object = make_shared<Object>(_position, _strTexturePath, true);
	AddGameObject(object);
	return object;
}

/*
	Get's Level's Physics World

	@author Jamuel Bocacao
	@return shared_ptr<b2World>: World Handle
*/
shared_ptr<b2World> Level::GetWorld()
{
	return m_world;
}

Vec2f Level::GetFlowFieldValue(Vec2f _worldPos)
{
	return m_flowField->GetCellValue(_worldPos);
}

void Level::SetFlowFieldGoal(Vec2f _topLeft, Vec2f _bottomRight)
{
	Vec2i topLeftCell = m_flowField->GetCellPos(_topLeft);
	Vec2i btmRightCell = m_flowField->GetCellPos(_bottomRight);

	vector<Vec2i> goalCells;

	Vec2i diff = btmRightCell - topLeftCell;

	for (int x = topLeftCell.x; x < btmRightCell.x; x++)
	{
		for (int y = topLeftCell.y; y < btmRightCell.y; y++)
		{
			goalCells.push_back(Vec2i(x, y));
		}
	}

	m_flowField->CalculateField(goalCells);
}

void Level::Render(sf::RenderWindow* _render)
{
	Scene::Render(_render);
	return;
	m_flowField->Render(&m_sceneBuffer);

	sf::Sprite buffer(m_sceneBuffer.getTexture());
	buffer.setPosition(m_bufferDisplacement);
	_render->draw(buffer);
}

void Level::SetOpenPauseMenuEvent(shared_ptr<Event<void, bool>> _event)
{
	m_openPauseMenuEvent = _event;
}
