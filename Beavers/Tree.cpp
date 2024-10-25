#include "Tree.h"
#include "ParticleSystem.h"

/*
	Creates a Tree Object

	@author(s) Jamuel Bocacao
	@param Vec2f: Position of Tree
*/
Tree::Tree(Vec2f _position) : Object(_position, "Resources/Objects/Tree.png", true)
{
	m_sprite.setOrigin(32, 116);
	AddBoxCollider(Vec2f(0, 7), Vec2f(10, 7));
}

void Tree::PlayParticleSystem()
{
	if (m_particleSystemRef)
	{
		m_particleSystemRef->Play();
	}
	else
	{
		Debug::LogWarning("Trees particle system reference hasnt been set or is null");
	}
}

void Tree::SetParticleSystemRef(shared_ptr<ParticleSystem> _particleSystem)
{
	m_particleSystemRef = _particleSystem;
}
