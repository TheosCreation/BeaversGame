#include "Object.h"

/*
	Initialises Object Properties

	@author Jamuel Bocacao
	@param Vec2f: Position of Object
	@param string: Texture File Path
	@param weak_ptr<b2World>: Reference to Scene's Physics World
	@param bool: Whether Object will simulate movement
*/
Object::Object(Vec2f _position, string _strTexturePath, weak_ptr<b2World> _sceneWorld, bool _bIsStatic)
{
	// Create Game Object
	SetTexture(_strTexturePath);
	auto textureSize = m_sprite.getLocalBounds();

	// Setup Physics Body
	m_world = _sceneWorld;
	b2BodyUserData userData;
	userData.pointer = (uintptr_t)this;

	// Create Body Definition
	_position /= PixelsPerMeter;

	b2BodyDef bodyDef;
	bodyDef.type = (_bIsStatic) ? b2BodyType::b2_staticBody : b2BodyType::b2_dynamicBody;
	bodyDef.position = b2Vec2(_position.x, _position.y);
	bodyDef.fixedRotation = true;
	bodyDef.userData = userData;
	bodyDef.linearDamping = 10.0f;
	m_body = m_world.lock()->CreateBody(&bodyDef);

	// Create Collider
	b2PolygonShape boxCollider;
	b2Vec2 size = b2Vec2(textureSize.width / PixelsPerMeter, textureSize.height / PixelsPerMeter);
	boxCollider.SetAsBox(size.x / 2.0f, size.y / 2.0f);

	b2FixtureDef colliderDef;
	colliderDef.shape = &boxCollider;
	colliderDef.friction = 0.0f;
	colliderDef.density = 1.0f;
	colliderDef.filter.groupIndex = 1;
	m_body->CreateFixture(&colliderDef);
}

/*
	Handles deleting Object
	Deletes Object's Physics Body

	@author Jamuel Bocacao
*/
Object::~Object()
{
	if (!m_world.expired())
	{
		m_world.lock()->DestroyBody(m_body);
	}
}

/*
	Sets the Object's Position

	@author Jamuel Bocacao
	@param Vec2f: New position
*/
void Object::SetPosition(Vec2f _newPosition)
{
	_newPosition /= PixelsPerMeter;
	m_body->SetTransform(b2Vec2(_newPosition.x, _newPosition.y), 0.0f);
}

/*
	Displaces the Object's Position

	@author Jamuel Bocacao
	@param Vec2f: Displacement Vector
*/
void Object::AddPosition(Vec2f _displacement)
{
	auto position = m_body->GetTransform().p;
	_displacement /= PixelsPerMeter;
	position += b2Vec2(_displacement.x, _displacement.y);
}

/*
	Gets the Object's Position

	@author Jamuel Bocacao
	@return Vec2f: Position
*/
Vec2f Object::GetPosition()
{
	return m_sprite.getPosition();
}

/*
	Sets The GameObject's Texture

	@author Jamuel Bocacao
	@param string: Texture's File Path
*/
void Object::SetTexture(string _strTexturePath)
{
	// Update Texture and Sprite
	auto texture = TextureManager::GetInstance().GetTexture(_strTexturePath);
	if (texture.expired()) return;	// Prevent missing textures from being used
	m_sprite.setTexture(*texture.lock().get(), true);

	// Update Sprite's origin to its centre
	auto texRect = m_sprite.getLocalBounds();
	m_sprite.setOrigin(texRect.width / 2.0f, texRect.height / 2.0f);
}

/*
	Gets The GameObject's Texture Handle

	@author Jamuel Bocacao
	@return sf::Texture*: SFML Texture Handle
*/
const sf::Texture* Object::GetTexture() const
{
	return m_sprite.getTexture();
}

/*
	Renders Object to Scene Buffer

	@author Jamuel Bocacao
	@param sf::RenderTexture*: Handle to Scene's Render Texture
*/
void Object::Render(sf::RenderTexture* _sceneBuffer)
{
	auto position = m_body->GetTransform().p;
	Vec2f worldPosition = Vec2f(position.x, position.y) * PixelsPerMeter;
	m_sprite.setPosition(worldPosition);

	DrawSprite(_sceneBuffer, m_sprite);
}
