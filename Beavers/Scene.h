#pragma once
#include "GameObject.h"
#include "Event.h"
#include "Object.h"

class Image;
class Button;
class Text;

class Scene
{
public:
	Scene(Vec2u _sceneSize, sf::RenderWindow* _window, bool _bUnloadPreviousSceneOnLoad = true);
	virtual ~Scene() = default;

	// Object Methods
	void AddSlider(Vec2f _position, unsigned int _iValue, unsigned int _iMaxValue, shared_ptr<Event<void, int>> _dragEvent, int _iLayer = 0);
	shared_ptr<Button> AddButton(Vec2f _position, string _strTexturePath, string _strSoundPath, shared_ptr<Event<void, void>> _event, int _iLayer = 0);
	shared_ptr<Image> AddImage(Vec2f _position, string _strTexturePath, int _iLayer = 0);
	shared_ptr<Text> AddText(Vec2f _position, string _strText, int _iSize, sf::Color _colour = sf::Color::White, int _iLayer = 0);
	void AddGameObject(shared_ptr<GameObject> _gameObject, int _iLayer = 0);

	// Process Methods
	virtual void ProcessEvents(sf::Event& _event, sf::RenderWindow* _window);

	virtual void SetPauseMenu(bool _bisActive) {};

	// Update Methods
	virtual void Update(float _fDeltaTime, sf::RenderWindow* _window);
	void DestroyObjects();

	// Render Methods
	virtual void Render(sf::RenderWindow* _window);

	// Scene Properties
	bool GetUnloadPreviousScene();

	// Getter Methods


private:
	void Resize(sf::RenderWindow* _window);
	void CheckLayer(int _iLayer);

protected:
	bool m_bUnloadPreviousSceneOnLoad;
	map<int, vector<shared_ptr<GameObject>>> m_objects;
	sf::RenderTexture m_sceneBuffer;
	Vec2u m_canvasSize;
	Vec2f m_bufferDisplacement;
};

struct RenderSorter
{
	// Render-Order Sorter Function
	bool operator()(const shared_ptr<GameObject>& _gameObjectA, const shared_ptr<GameObject>& _gameObjectB)
	{
		Object* objA = dynamic_cast<Object*>(_gameObjectA.get());
		Object* objB = dynamic_cast<Object*>(_gameObjectB.get());
		if (objA && objB)
		{
			return objA->GetPosition().y < objB->GetPosition().y;
		}
		else if (!objA && objB)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};