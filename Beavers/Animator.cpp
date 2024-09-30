#include "Animator.h"

Animator::Animator(sf::Sprite* _sprite)
{
	m_sprite = _sprite;
}

Animator::~Animator()
{
	for (auto states : m_animationStates)
	{
		delete states.second;
	}
}

void Animator::ChangeState(string _strNewState)
{
	if (!m_animationStates.contains(_strNewState)) return;
	if (m_animationStates.at(_strNewState) == m_currAnimation) return;

	m_currAnimation = m_animationStates.at(_strNewState);
	m_currAnimation->m_textureRect.left = 0;
	m_sprite->setTexture(*m_currAnimation->m_texture);
	m_sprite->setTextureRect(m_currAnimation->m_textureRect);
}

void Animator::AddState(string _strStateName, string _strTexturePath, int _iFrames, string _strExitState)
{
	m_animationStates.emplace(_strStateName, CreateAnimation(_strTexturePath, _iFrames, 12, _strExitState));
	if (m_currAnimation == nullptr)
	{
		ChangeState(_strStateName);
	}
}

void Animator::AddState(string _strStateName, string _strTexturePath, int _iFrames, int _iFramesPerSecond, string _strExitState)
{
	m_animationStates.emplace(_strStateName, CreateAnimation(_strTexturePath, _iFrames, _iFramesPerSecond, _strExitState));
	if (m_currAnimation == nullptr)
	{
		ChangeState(_strStateName);
	}
}

void Animator::Update()
{
	if (m_animationTimer.getElapsedTime().asSeconds() > (1.0f / float(m_currAnimation->m_iFramesPerSecond)))
	{
		m_animationTimer.restart();

		// Sets Next Frame
		m_iCurrFrame++;
		if (m_iCurrFrame >= m_currAnimation->m_iFrames)
		{
			m_iCurrFrame = 0;
			
			// Checks if Animator should change state
			if (m_animationStates.contains(m_currAnimation->m_strExitState))
			{
				ChangeState(m_currAnimation->m_strExitState);
				return;
			}
		}

		// Updates Texture Rect
		m_currAnimation->m_textureRect.left = m_iCurrFrame * m_currAnimation->m_textureRect.width;
		m_sprite->setTextureRect(m_currAnimation->m_textureRect);
	}
}

Animation* Animator::CreateAnimation(string _strTexturePath, int _iFrames, int _iFramesPerSecond, string _strExitState)
{
	Animation* animation = new Animation();
	
	// Create Animation Sprite
	animation->m_texture = &TextureManager::GetInstance().GetTexture(_strTexturePath);
	auto size = animation->m_texture->getSize();
	animation->m_textureRect = sf::IntRect(0, 0, size.x / _iFrames, size.y);
	
	// Set Animation Properties
	animation->m_iFramesPerSecond = _iFramesPerSecond;
	animation->m_strExitState = _strExitState;
	animation->m_iFrames = _iFrames;

	return animation;
}
