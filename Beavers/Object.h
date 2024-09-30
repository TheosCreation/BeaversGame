#pragma once
#include "GameObject.h"
#include <Box2D/box2d.h>
#include <type_traits>

#define PixelsPerMeter 64.0f

class Object : public GameObject
{
public:
	Object(Vec2f _position, string _strTexturePath, weak_ptr<b2World> _sceneWorld, bool _bIsStatic = false);
	Object(Vec2f _position, weak_ptr<b2World> _sceneWorld, bool _bIsStatic = false);
	~Object();

	// Position Methods
	void SetPosition(Vec2f _newPosition) override;
	void AddPosition(Vec2f _displacement) override;
	virtual Vec2f GetPosition() override;

	// Physics Methods
	void ApplyForce(Vec2f _force);

	// Collision Methods
	void AddBoxCollider(Vec2f _relativePosition, Vec2f _size, bool _bIsTrigger = false);
	void AddCircleCollider(Vec2f _relativePosition, float _fRadius, bool _bIsTrigger = false);
	virtual void OnBeginContact(Object* _otherObject);
	virtual void OnEndContact(Object* _otherObject);

	// Texture Methods
	void SetTexture(string _strTexturePath);

	void SetColor(sf::Color _color);
	void SetDrawRect(sf::IntRect _drawRect);
	const sf::Texture* GetTexture() const;

	// Render Methods
	virtual void Render(sf::RenderTexture* _sceneBuffer) override;

	template <std::derived_from<Object> T>
	bool IsOfType();

	template <std::derived_from<Object> T>
	bool IsOfType(T** _objectPointer);

protected:
	sf::Sprite m_sprite;

	weak_ptr<b2World> m_world;
	b2Body* m_body;
};

/*
	Checks to See if Object is of a Subclass
	Called using IsOfType<T>();

	@author Jamuel Bocacao
	@param <T>: Subclass of Object Class
	@return bool: Object is of Type T
*/
template<std::derived_from<Object> T>
inline bool Object::IsOfType()
{
	T* cast = dynamic_cast<T*>(this);
	return (cast) ? true : false;
}

/*
	Checks to See if Object is of a Subclass, then converts it to Subclass
	Called using IsOfType<T>();

	@author Jamuel Bocacao
	@param <T>: Subclass of Object Class
	@param T**: Pointer to store converted Object* to
	@return bool: Object is of Type T
*/
template<std::derived_from<Object> T>
inline bool Object::IsOfType(T** _objectPointer)
{
	*_objectPointer = dynamic_cast<T*>(this);
	return (*_objectPointer) ? true : false;
}
