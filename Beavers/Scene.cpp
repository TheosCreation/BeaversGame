#include "Scene.h"
#include "Slider.h"
#include "Button.h"
#include "Object.h"
#include <iostream>
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
void Scene::AddSlider(Vec2f _position, unsigned int _iValue, unsigned int _iMaxValue, shared_ptr<Event<void, int>> _dragEvent, int _iLayer)
{
	CheckLayer(_iLayer);
	m_objects.at(_iLayer).push_back(make_shared<Slider>(_position, _iValue, _iMaxValue, _dragEvent));
}

/*
	Adds a Button Object to Scene

	@author Jamuel Bocacao and Theo Morris
	@param Vec2f: Position of Button
	@param string: Texture File Path
	@param shared_ptr<Event<void, void>>: Event that is called when the Button is clicked
*/
shared_ptr<Button> Scene::AddButton(Vec2f _position, string _strTexturePath, string _strSoundPath, shared_ptr<Event<void, void>> _event, int _iLayer)
{
	CheckLayer(_iLayer);
	auto button = make_shared<Button>(_position, _strTexturePath, _strSoundPath, _event);
	m_objects.at(_iLayer).push_back(button);
	return button;
}

/*
	Adds an Image Object to Scene

	@author Jamuel Bocacao and Theo Morris
	@param Vec2f: Position of Image
	@param string: Texture File Path
*/
shared_ptr<Image> Scene::AddImage(Vec2f _position, string _strTexturePath, int _iLayer)
{
	CheckLayer(_iLayer);
	auto image = make_shared<Image>(_position, _strTexturePath);
	m_objects.at(_iLayer).push_back(image);
	return image;
}

/*
	Adds an Text Object to Scene

	@author Theo Morris
	@param Vec2f: Position of Text
	@param string: Text to display
*/
shared_ptr<Text> Scene::AddText(Vec2f _position, string _strText, int _iSize, sf::Color _colour, int _iLayer)
{
	CheckLayer(_iLayer);
	auto text = make_shared<Text>(_position, _strText, "Resources/Fonts/AlteHaasGroteskBold.ttf");
	text->SetSize(_iSize);
	text->SetColour(_colour);
	m_objects.at(_iLayer).push_back(text);
	return text;
}

/*
	Adds any Game Object to Scene

	@author Jamuel Bocacao
	@param shared_ptr<GameObject>: Game Object to be added
*/
void Scene::AddGameObject(shared_ptr<GameObject> _gameObject, int _iLayer)
{

	CheckLayer(_iLayer);
	m_objects.at(_iLayer).push_back(_gameObject);

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
			
			for (auto const& [layer, objects] : m_objects)
			{
				for (auto object : objects)
				{
					if (object->OnClick(worldPos))
					{
						return;
					}
				}
			}
			break;
		}
		case sf::Event::MouseButtonReleased:
		{
			auto mousePos = sf::Mouse::getPosition(*_window);
			auto worldPos = m_sceneBuffer.mapPixelToCoords(mousePos);
			
			for (auto const& [layer, objects] : m_objects)
			{
				for (auto object : objects)
				{
					object->OnRelease(worldPos);
				}
			}
			
			break;
		}
		case sf::Event::MouseMoved:
		{
			auto mousePos = sf::Mouse::getPosition(*_window);
			auto worldPos = m_sceneBuffer.mapPixelToCoords(mousePos);

			for (auto const& [layer, objects] : m_objects)
			{
				for (auto object : objects)
				{
					object->OnDrag(worldPos);
				}
			}
			break;
		}
		case sf::Event::KeyPressed:
		{
			for (auto const& [layer, objects] : m_objects)
			{
				for (auto object : objects)
				{
					object->OnKeyDown(_event);
				}
			}
			break;
		}
		case sf::Event::KeyReleased:
		{
			for (auto const& [layer, objects] : m_objects)
			{
				for (auto object : objects)
				{
					object->OnKeyUp(_event);
				}
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
			//Debug::Log("START");
	for (auto const& [layer, objects] : m_objects)
	{
			//Debug::Log("layer" + ToString(layer));
		for (auto& object : objects)
		{
			// crash is happening somewhere here before debugin when checking the objects list 
			if (object == nullptr || !object) {
				Debug::Log("null object");
				continue;
			}
			//Debug::Log(object);
			object->Update(_fDeltaTime);
			//Debug::Log("object end");
		}
			//Debug::Log("layer end");
	}
			//Debug::Log("END");
	return;
}

/*
	Deletes all Marked for Destruction Game Objects

	@author Jamuel Bocacao
*/
void Scene::DestroyObjects()
{
	for (auto &[layer, objects] : m_objects)
	{
		std::erase_if(objects, [](shared_ptr<GameObject> _object) { return _object->MarkedForDestroy(); });
	}
}

/*
	Renders Scene to Window

	@author Jamuel Bocacao
	@param sf::RenderWindow: Window Handle to Render to
*/
void Scene::Render(sf::RenderWindow* _window)
{
	
	m_sceneBuffer.clear(sf::Color(0, 0, 0, 0));
	for (auto &layer : m_objects)
	{
		std::sort(layer.second.begin(), layer.second.end(), RenderSorter());
		for (auto object : layer.second)
		{
			object->Render(&m_sceneBuffer);
		}
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

/*
	Check if Layer has been created already, if not create one

	@author Jamuel Bocacao
	@param int: Layer ID
*/
void Scene::CheckLayer(int _iLayer)
{
	if (!m_objects.contains(_iLayer))
	{
		m_objects.emplace(_iLayer, vector<shared_ptr<GameObject>>());
	}
}
