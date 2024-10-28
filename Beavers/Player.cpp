#include "Player.h"
#include "Warehouse.h"
#include "WoodChange.h"
#include "Beaver.h"
#include "Tree.h"
#include <iostream>
#include "Level.h"
#include "PauseManager.h"

/*
	Creates a Player's

	@author Jamuel Bocacao
	@param Vec2f: Start Position
*/
Player::Player(Vec2f _position) : Object(_position, false)
{
	SetDrawRect(sf::IntRect(0, 32, 32, 32));
	AddBoxCollider(Vec2f(0, 12), Vec2f(24, 8), false);	// Collider
	AddCircleCollider(Vec2f(0, 12), 24, true);			// Interaction Range Sensor
	m_attackZoneLeft = AddBoxCollider(Vec2f(-16, 0), Vec2f(16, 32), true); // Left Attack Sensor
	m_attackZoneRight = AddBoxCollider(Vec2f(16, 0), Vec2f(16, 32), true); // Right Attack Sensor

	m_animator = make_unique<Animator>(&m_sprite);
	SetAnimations("Resources/Images/Entities/Idle.png", "Resources/Images/Entities/Run.png", "Resources/Images/Entities/Attack.png");
	/*m_animator->AddState("Running", "Resources/Images/Entities/Run.png", 4, 8);
	m_animator->AddState("Idle", "Resources/Images/Entities/Idle.png", 4, 8);
	m_animator->AddState("Attack", "Resources/Images/Entities/Attack.png", 5, 8, "Idle");*/

	// Initialize the wood amount text
	m_woodAmountText = make_unique<Text>(_position + Vec2f(0.0f, -15.0f), "Wood: 0/100", "Resources/Fonts/AlteHaasGroteskBold.ttf");
	m_woodAmountText->SetSize(15);
	m_woodAmountText->SetColour(sf::Color::White);
}

/*
	Player's Update Procedure

	@author Jamuel Bocacao
	@param float: Delta Time
*/
void Player::Update(float _fDeltaTime)
{
	if (_fDeltaTime == 0) return;

	m_cooldownClock += _fDeltaTime;
	m_interactClock += _fDeltaTime;

	// Updates Current Animation Frame
	m_animator->Update(_fDeltaTime);

	m_woodAmountText->SetPosition(GetPosition() + Vec2f(0.0f, -25.0f));
	m_woodAmountText->SetText("Wood: " + std::to_string(m_iWoodAmount) + "/" + std::to_string(m_playerStats.m_fCapacity));

	// Handles Player Movement
	sf::Vector2f displacement;
	if (!m_bInteracting)
	{
		if (sf::Keyboard::isKeyPressed(m_controlScheme.Up))
		{
			displacement += Vec2f(0.0f, -1.0f);
			
		}
		if (sf::Keyboard::isKeyPressed(m_controlScheme.Left))
		{
			displacement += Vec2f(-1.0f, 0.0f);
			m_sprite.setScale(-1, 1);
			
		}
		if (sf::Keyboard::isKeyPressed(m_controlScheme.Down))
		{
			displacement += Vec2f(0.0f, 1.0f);
		
		}
		if (sf::Keyboard::isKeyPressed(m_controlScheme.Right))
		{
			displacement += Vec2f(1.0f, 0.0f);
			m_sprite.setScale(1, 1);
		}
		if (displacement != Vector2f(0, 0))
		{
			OnPlayerWalk(true);
		}
		else {
			OnPlayerWalk(false);
		}
		float length = sqrt(powf(displacement.x, 2.0f) + powf(displacement.y, 2.0f));
		if (length > 0)
		{
			m_animator->ChangeState("Running");

			displacement /= length;
			AddPosition(displacement * _fDeltaTime * float(m_playerStats.m_iSpeed));

		}
		else
		{
			m_animator->ChangeState("Idle");
		}
	}
	else
	{
		if (m_interactClock > 0.5f)
		{
			m_interactClock = 0.0f;
			if (m_shopRef)
			{
				std::cout << m_playerStats.m_fDamage << std::endl;
				m_shopRef->ApplyItem(m_playerStats);
			}
			// Atack Action
			else
			{
				// Get Contacting Bodies
				b2ContactEdge* contact = m_body->GetContactList();
				while (contact)
				{
					// Check which side Player is facing
					b2Fixture* attackSide = (m_sprite.getScale().x < 0) ? m_attackZoneLeft : m_attackZoneRight;

					// Check if Attack Fixture is a Contact Point
					if (contact->contact->GetFixtureA() == attackSide)
					{
						// Check if other other Contact Object is an attackable Object
						Object* contactObject = (Object*)contact->contact->GetFixtureB()->GetBody()->GetUserData().pointer;
						Beaver* beaver;
						if (contactObject->IsOfType<Tree>())
						{
							int actualGain = std::min(m_playerStats.m_fDamage, m_playerStats.m_fCapacity - m_iWoodAmount);
							m_iWoodAmount += actualGain;
							ExecuteWoodAmountChangeEvent(actualGain);
							dynamic_cast<Tree*>(contactObject)->PlayParticleSystem();
							break;
						}
						else if (contactObject->IsOfType<Beaver>(&beaver))
						{
							beaver->Damage(m_playerStats.m_fDamage);
						}
					}

					// Continue iterating
					contact = contact->next;
				}
			}
			m_bInteracting = false;
		}
	}
	
	// Interact Action
	if (sf::Keyboard::isKeyPressed(m_controlScheme.Interact))
	{
		if (m_cooldownClock > 1.0f)
		{
			if (!m_bInteracting)
			{
				m_cooldownClock = 0.0f;
				m_interactClock = 0.0f;
				m_bInteracting = true;
				if (!m_shopRef)
				{
					m_animator->ChangeState("Attack");
					OnPlayerSwingAxe();
				}
			}
		}
	}

	bool hintKeyIsPressed = sf::Keyboard::isKeyPressed(m_controlScheme.Hint);
	// Check if the key was just pressed (transition from "not pressed" to "pressed")
	if (hintKeyIsPressed && !hintKeyWasPressed)
	{
		m_bHintVisible = !m_bHintVisible;

		if (m_bHintVisible)
		{
			Debug::Log("Hint visible");
		}
		else
		{
			Debug::Log("Hint hidden");
			m_HintRef->SetText("");
			m_PreviousHint = HintType::None; // Reset when hint is hidden
		}
	}
	// Update the previous state
	hintKeyWasPressed = hintKeyIsPressed;

	// Update the hint content only if the hint is visible
	if (m_bHintVisible)
	{
		UpdateHintSystem();
	}

	bool pauseKeyIsPressed = sf::Keyboard::isKeyPressed(m_controlScheme.Pause);
	// Check if the key was just pressed (transition from "not pressed" to "pressed")
	if (pauseKeyIsPressed && !pauseKeyWasPressed)
	{
		Debug::Log("Input");
		PauseManager::GetInstance().TogglePaused();
	}

	// Update the previous state
	pauseKeyWasPressed = pauseKeyIsPressed;
}

/*
	Sets the Player's Controls

	@author Jamuel Bocacao
	@param ControlScheme: Struct containing Keybinds
*/
void Player::SetControlScheme(ControlScheme _scheme)
{
	m_controlScheme = _scheme;
}

/*
	Sets the Event that spawns a UI indicator when wood amount has changed

	@author Jamuel Bocacao
	@param shared_ptr<Event2P<void, shared_ptr<GameObject>, int>>: Level's AddGameObject() function
*/
void Player::SetWoodAmountChangeEvent(shared_ptr<Event2P<void, shared_ptr<GameObject>, int>> _woodAmountChangeEvent)
{
	m_woodAmountChangeEvent = _woodAmountChangeEvent;
}

/*
	Executes an Event when the amount of Wood a Player if holding changes

	@author Jamuel Bocacao + Kazuo RDA
	@param int: Change in Wood amount
*/
void Player::ExecuteWoodAmountChangeEvent(int _iAmount)
{
	auto woodChange = make_shared<WoodChange>(GetPosition() + Vec2f(15.0f, -15.0f), _iAmount);
	m_woodAmountChangeEvent->execute(woodChange, 100);
}

void Player::OnBeginContact(Object* _other)
{
	if (_other->IsOfType<Tree>())
	{
		m_bNearTree = true;
	}
}

void Player::OnEndContact(Object* _other)
{
	if (_other->IsOfType<Tree>())
	{
		m_bNearTree = false;
	}
}

/*
	Set shop reference Function

	@author George Mitchell
	@param Shop*: Shop reference to store
*/
void Player::SetShopRef(Shop* _shop)
{
	m_shopRef = _shop;
}

/*
	Warehouse Deposit Function

	@author Jamuel Bocacao
	@return int: Wood Amount to deposit into Warehouse
*/
int Player::Deposit()
{
	// Spawns a Minus Item Element
	if (m_iWoodAmount != 0)
	{
		ExecuteWoodAmountChangeEvent(-m_iWoodAmount);
	}

	int iDepositAmount = m_iWoodAmount;
	m_iWoodAmount = 0;
	return iDepositAmount;
}

/*
	Updates the hint system

	@author Theo Morris and Nick
*/
void Player::UpdateHintSystem()
{
	m_HintRef->SetPosition(GetPosition() + Vec2f(0, 75));
	// Determine the current location
	if (m_bNearTree)
	{
		m_CurrentHint = HintType::Forest;
	}
	else if (m_shopRef)
	{
		m_CurrentHint = HintType::Shop;
	}
	else
	{
		m_CurrentHint = HintType::None;
	}

	// Display the hint only if the player moves to a new location
	if (m_CurrentHint != m_PreviousHint)
	{
		m_PreviousHint = m_CurrentHint;

		if (m_CurrentHint == HintType::Forest)
		{
			m_HintRef->SetText("Press F near to gather wood\nDeposit it in the warehouse\n below to use on upgrades");
			//m_HintRef->SetText("Press F near to gather wood");
		}
		else if (m_CurrentHint == HintType::Shop)
		{
			if (m_shopRef->GetShopType() == Type_Speed)
			{
				m_HintRef->SetText("Press F near to buy upgrades\nUpgrade 1: Increases movement speed\nCurrent cost is above the shop");
			}
			
			else if (m_shopRef->GetShopType() == Type_Weapon)
			{
				m_HintRef->SetText("Press F near to buy upgrades\nUpgrade 2: Increases damage\nCurrent cost is above the shop");
			}


			else if (m_shopRef->GetShopType() == Type_Bag)
			{
				m_HintRef->SetText("Press F near to buy upgrades\nUpgrade 3: Increases carrying capacity\nCurrent cost is above the shop");
			}

			
			//m_HintRef->SetText("Press F near to buy upgrades\nUpgrade 1 - Increases movement speed\nUpgrade 2 - Increases Swing speed\nUpgrade 3 - Increases carrying capacity\n Current cost is above the shop");
		}
		else
		{
			//std::cout << "No hints available" << std::endl;
			m_HintRef->SetText(""); //Hides the hint
		}
	}
}

/*
	Event function when the player uses their axe

	@author Theo Morris and Kazuo RDA
*/
void Player::OnPlayerSwingAxe()
{
	AudioManager::GetInstance().PlaySound(swingSound, sf::Vector3f(), sf::seconds(0), 1.0f,1.2f);
}

/*
	Event function when the player moves

	@author Theo Morris and Kazuo RDA
	@param bool: Is player walking?
*/
void Player::OnPlayerWalk(bool _active)
{
	// make this work with two players walking maybe if needed
	auto& audioManager = AudioManager::GetInstance();
	if (_active) {
		if (!audioManager.IsSoundPlaying(walkSound))
		{
			audioManager.PlaySound(walkSound, sf::Vector3f(), sf::seconds(0), 1.0f, 1.5f);
		}
	}
	//else //dont need this
	//{
	//	audioManager.StopSound(walkSound);
	//}
}

/*
	Sets the reference to the hint attached to the player

	@author Theo Morris and Nick
	@param Hint*: Hint reference
*/
void Player::SetHintRef(Hint* _hint)
{
	m_HintRef = _hint;
}

/*
	Renders Player to Scene View Buffer and the wood text above the player

	@author Jamuel Bocacao, Theo Morris and George
	@param sf::RenderTexture*: Scene View Buffer
*/
void Player::Render(sf::RenderTexture* _sceneBuffer)
{
	// Render the player's sprite
	Object::Render(_sceneBuffer);

	// Render the wood amount text
	if (m_woodAmountText)
	{
		m_woodAmountText->Render(_sceneBuffer);
	}
}

void Player::SetAnimations(std::string _idle, std::string _run, std::string _attack)
{
	m_animator->AddState("Idle", _idle, 4, 8);
	m_animator->AddState("Running", _run, 4, 8);
	m_animator->AddState("Attack", _attack, 5, 8, "Idle");
}
