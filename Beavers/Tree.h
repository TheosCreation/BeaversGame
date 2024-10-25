#pragma once
#include "Object.h"

class ParticleSystem;

class Tree : public Object
{
public:
	Tree(Vec2f _position);

	void PlayParticleSystem();

	void SetParticleSystemRef(shared_ptr<ParticleSystem> _particleSystem);

private:
	shared_ptr<ParticleSystem> m_particleSystemRef = nullptr;
};

