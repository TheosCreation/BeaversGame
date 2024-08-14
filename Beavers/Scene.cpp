#include "Scene.h"

/*
	Creates a Scene

	@author Jamuel Bocacao
	@param Vec2u: Size of Scene Viewport in Pixels
	@param sf::RenderWindow*: Window Handle
	@param bool: Whether previous Scene should be unloaded when this Scene is loaded
*/
Scene::Scene(Vec2u _sceneSize, sf::RenderWindow* _window, bool _bUnloadPreviousSceneOnLoad)
{
	// Set Scene Properties
	m_bUnloadPreviousSceneOnLoad = _bUnloadPreviousSceneOnLoad;

	// Set Viewport Properties
	m_canvasSize = _sceneSize;
	Resize(_window);
}

/*
	Adds a Slider Object to Scene
	
	@author Jamuel Bocacao
	@param Vec2f: Position of Slider
	@param unsigned int: Initial Value of Slider
	@param unsigned int: Max Value of Slider
	@param shared_ptr<Event<void, int>>: Event that is called when the slider is dragged
*/
void Scene::AddSlider(Vec2f _position, unsigned int _iValue, unsigned int _iMaxValue, shared_ptr<Event<void, int>> _dragEvent)
{
	m_objects.push_back(make_shared<Slider>(_position, _iValue, _iMaxValue, _dragEvent));
}

/*
	Adds a Button Object to Scene

	@author Jamuel Bocacao
	@param Vec2f: Position of Button
	@param string: Texture File Path
	@param shared_ptr<Event<void, void>>: Event that is called when the Button is clicked
*/
void Scene::AddButton(Vec2f _position, string _strTexturePath, string _strSoundPath, shared_ptr<Event<void, void>> _event)
{
	m_objects.push_back(make_shared<Button>(_position, _strTexturePath, _strSoundPath, _event));
}

/*
	Adds an Image Object to Scene

	@author Jamuel Bocacao
	@param Vec2f: Position of Button
	@param string: Texture File Path
*/
void Scene::AddImage(Vec2f _position, string _strTexturePath)
{
	m_objects.push_back(make_shared<Image>(_position, _strTexturePath));
}

/*
	Adds any Game Object to Scene

	@author Jamuel Bocacao
	@param shared_ptr<GameObject>: Game Object to be added
*/
void Scene::AddGameObject(shared_ptr<GameObject> _gameObject)
{
	m_objects.push_back(_gameObject);
}

/*
	Processes Scene-Specific Events

	@author Jamuel Bocacao
	@param sf::Event: Event Handle
	@param sf::RenderWindow*: Window Handle
*/
void Scene::ProcessEvents(sf::Event& _event, sf::RenderWindow* _window)
{
	switch (_event.type)
	{
		case sf::Event::MouseButtonPressed:
		{
			auto mousePos = sf::Mouse::getPosition(*_window);
			auto worldPos = m_sceneBuffer.mapPixelToCoords(Vec2i(_window->mapPixelToCoords(mousePos) - m_bufferDisplacement));
			
			for (auto object : m_objects)
			{
				object->OnClick(worldPos);
			}
			break;
		}
		case sf::Event::MouseButtonReleased:
		{
			auto mousePos = sf::Mouse::getPosition(*_window);
			auto worldPos = m_sceneBuffer.mapPixelToCoords(mousePos);

			for (auto object : m_objects)
			{
				object->OnRelease(worldPos);
			}
			break;
		}
		case sf::Event::MouseMoved:
		{
			auto mousePos = sf::Mouse::getPosition(*_window);
			auto worldPos = m_sceneBuffer.mapPixelToCoords(mousePos);

			for (auto object : m_objects)
			{
				object->OnDrag(worldPos);
			}
			break;
		}
		case sf::Event::KeyPressed:
		{
			for (auto object : m_objects)
			{
				object->OnKeyDown(_event);
			}
			break;
		}
		case sf::Event::KeyReleased:
		{
			for (auto object : m_objects)
			{
				object->OnKeyUp(_event);
			}
			break;
		}
		case sf::Event::Resized:
		{
			auto windowSize = _window->getSize();
			bool bClamp = false;

			// Clamp Window Width to 1280 and above
			if (windowSize.x < 1280)
			{
				windowSize.x = 1280;
				bClamp = true;
			}
			
			// Clamp Window Height to 720 and above
			if (windowSize.y < 720)
			{
				windowSize.y = 720;
				bClamp = true;
			}
			
			// Change Window Size if 
			if (bClamp)
			{
				_window->setSize(windowSize);
			}
			else
			{
				Resize(_window);
			}
			break;
		}
	}
}

/*
	Interface for Scene-specific updates

	@author Jamuel Bocacao
	@param float: Delta Time
	@param sf::RenderWindow*: Window Handle
*/
void Scene::Update(float _fDeltaTime, sf::RenderWindow* _window)
{
	return;
}

/*
	Renders Scene to Window

	@author Jamuel Bocacao
	@param sf::RenderWindow: Window Handle to Render to
*/
void Scene::Render(sf::RenderWindow* _window)
{
	m_sceneBuffer.clear(sf::Color(0, 0, 0, 0));
	for (auto object : m_objects)
	{
		object->Render(&m_sceneBuffer);
	}

	sf::Sprite buffer(m_sceneBuffer.getTexture());
	buffer.setPosition(m_bufferDisplacement);
	_window->draw(buffer);
}

/*
	Gets whether Game should store current Scene before loading this Scene

	@author Jamuel Bocacao
	@return bool: Whether or not Previous Scene is unloaded after new Scene is loaded
*/
bool Scene::GetUnloadPreviousScene()
{
	return m_bUnloadPreviousSceneOnLoad;
}

/*
	Updates the size of the Scene's Viewport

	@author Jamuel Bocacao
	@param sf::RenderWindow*: Window Handle
*/
void Scene::Resize(sf::RenderWindow* _window)
{
	// Sets Canvas Screen-Space Dimensions to scale with Canvas
	// Get Aspect Ratios of Screen and Scene Canvas
	auto screenSize = _window->getSize();
	float fCanvasAspectRatio = float(m_canvasSize.x) / float(m_canvasSize.y);
	float fScreenAspectRatio = float(screenSize.x) / float(screenSize.y);

	// Check if Screen Width is larger than Scene Canvas' Aspect Ratio
	if (fScreenAspectRatio > fCanvasAspectRatio)
	{
		// Resize Canvas' Width and Position so that it scales properly
		int iViewportWidth = int(fCanvasAspectRatio * float(screenSize.y));	// Calculate new Width
		int iViewportX = (screenSize.x - iViewportWidth) / 2;				// Calculate new X Pos

		m_bufferDisplacement = Vec2f(float(iViewportX), 0.0f);
		m_sceneBuffer.create(iViewportWidth, screenSize.y);
	}
	// Check if Screen Height is larger than Scene Canvas' Aspect Ratio
	else if (fScreenAspectRatio < fCanvasAspectRatio)
	{
		// Resize Canvas' Height and Position so that it scales properly
		int iViewportHeight = int((1.0f / fCanvasAspectRatio) * float(screenSize.x)); // Calculate new Height
		int iViewportY = (screenSize.y - iViewportHeight) / 2;						  // Calculate new Y Pos

		m_bufferDisplacement = Vec2f(0.0f, float(iViewportY));
		m_sceneBuffer.create(screenSize.x, iViewportHeight);
	}
	// Check if Aspect Ratios are Equal
	else
	{
		// Scale Normally
		m_sceneBuffer.create(screenSize.x, screenSize.y);
		m_bufferDisplacement = Vec2f(0.0f, 0.0f);
	}

	// Sets Canvas World-Space Dimensions to Canvas Size
	m_sceneBuffer.setView(sf::View(Vec2f(m_canvasSize) / 2.0f, Vec2f(m_canvasSize)));
	_window->setView(sf::View(Vec2f(screenSize) / 2.0f, Vec2f(screenSize)));
}
