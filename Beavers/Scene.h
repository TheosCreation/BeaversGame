#pragma once
#include "GameObject.h"
#include "Event.h"

class Scene
{
public:
	Scene(Vec2u _sceneSize, sf::RenderWindow* _window, bool _bUnloadPreviousSceneOnLoad = true);
	virtual ~Scene() = default;

	// Object Methods
	void AddSlider(Vec2f _position, unsigned int _iValue, unsigned int _iMaxValue, shared_ptr<Event<void, int>> _dragEvent);
	void AddButton(Vec2f _position, string _strTexturePath, string _strSoundPath, shared_ptr<Event<void, void>> _event);
	void AddImage(Vec2f _position, string _strTexturePath);
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
	Vec2u m_canvasSize;
	Vec2f m_bufferDisplacement;
};