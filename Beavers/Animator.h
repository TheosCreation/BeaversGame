#pragma once
#include "TextureManager.h"

struct Animation
{
	sf::Texture* m_texture = nullptr;
	sf::IntRect m_textureRect;

	int m_iFrames = 1;
	int m_iFramesPerSecond = 12;

	string m_strExitState;
};

class Animator
{
public:
	Animator(sf::Sprite* _sprite);
	~Animator();

	void ChangeState(string _strNewState);
	void AddState(string _strStateName, string _strTexturePath, int _iFrames, string _strExitState = "");
	void AddState(string _strStateName, string _strTexturePath, int _iFrames, int _iFramesPerSecond, string _strExitState = "");

	void Update();

private:
	Animation* CreateAnimation(string _strTexturePath, int _iFrames, int _iFramesPerSecond, string _strExitState = "");

private:
	map<string, Animation*> m_animationStates;
	int m_iCurrFrame = 0;
	sf::Clock m_animationTimer;
	Animation* m_currAnimation = nullptr;
	sf::Sprite* m_sprite;
};

