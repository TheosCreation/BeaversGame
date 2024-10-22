#pragma once
#include "Object.h"
#include "ControlScheme.h"
#include "Event.h"
#include "Shop.h"
#include "PlayerStats.h"
#include "Animator.h"
#include "Hint.h"
#include "Text.h"
#include "Sound.h"
#include "AudioManager.h"
class Sound;
class Player : public Object
{
public:
	Player(Vec2f _position);
	
	void Update(float _fDeltaTime) override;
	void SetControlScheme(ControlScheme _scheme);

	// Wood Amount Methods
	void SetWoodAmountChangeEvent(shared_ptr<Event2P<void, shared_ptr<GameObject>, int>> _woodAmountChangeEvent);
	void ExecuteWoodAmountChangeEvent(int _iAmount);

	void OnBeginContact(Object* _other) override;
	void OnEndContact(Object* _other) override;

	void SetShopRef(Shop* _shop);

	int Deposit();

	void UpdateHintSystem();

	void OnPlayerSwingAxe();
	void OnPlayerWalk(bool _active);

	void SetHintRef(Hint* _hint);

	void Render(sf::RenderTexture* _sceneBuffer) override;

private:
	static PlayerStats m_playerStats;
	std::string walkSound = "Resources/Audio/footStep.mp3";
	std::string swingSound = "Resources/Audio/slash.mp3";

	b2Fixture* m_attackZoneLeft = nullptr;
	b2Fixture* m_attackZoneRight = nullptr;

	unique_ptr<Animator> m_animator;
	sf::Clock m_interactClock;
	sf::Clock m_cooldownClock;
	int m_iAnimationFrame = 0;
	float m_fSpeed = 50.0f;

	int m_iWoodAmount = 50;

	ControlScheme m_controlScheme;

	bool m_bNearTree = false;
	bool m_bInteracting = false;
	bool m_bHintVisible = true;

	bool m_bHintOnce = false;

	bool hintKeyWasPressed = false;
	bool pauseKeyWasPressed = false; // Used for toggle key press for the pause key

	shared_ptr<Event2P<void, shared_ptr<GameObject>, int>> m_woodAmountChangeEvent;

	Shop* m_shopRef = nullptr;

	Hint* m_HintRef = nullptr;

	unique_ptr<Text> m_woodAmountText; 

	// Variable to track the last hint displayed
	HintType m_PreviousHint = HintType::None;
	HintType m_CurrentHint = HintType::None;
};

inline PlayerStats Player::m_playerStats;