#pragma once
#include "Utils.h"
#include "Event.h"
#include "GameObject.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

class Scene
{
public:
	Scene(Vector2u _sceneSize, sf::RenderWindow* _window, bool _bUnloadPreviousSceneOnLoad = true);
	virtual ~Scene() = default;

	// Object Methods
	void AddSlider(Vector2f _position, unsigned int _iValue, unsigned int _iMaxValue, shared_ptr<Event<void, int>> _dragEvent);
	void AddButton(Vector2f _position, string _strTexturePath, string _strSoundPath, shared_ptr<Event<void, void>> _event);
	void AddImage(Vector2f _position, string _strTexturePath);
	void AddGameObject(shared_ptr<GameObject> _gameObject);

	// Process Methods
	virtual void ProcessEvents(sf::Event& _event, sf::RenderWindow* _window);

	// Update Methods
	virtual void Update(float _fDeltaTime, sf::RenderWindow* _window);

	// Render Methods
	void Render(sf::RenderWindow* _window);

	// Scene Properties
	bool GetUnloadPreviousScene();

private:
	void Resize(sf::RenderWindow* _window);

protected:
	bool m_bUnloadPreviousSceneOnLoad;
	vector<shared_ptr<GameObject>> m_objects;

	sf::RenderTexture m_sceneBuffer;
	Vector2u m_canvasSize;
	Vector2f m_bufferDisplacement;
};