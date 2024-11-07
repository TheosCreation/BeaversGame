 #pragma once
#include "Warehouse.h"
#include "Animator.h"
#include "BeaverSpawner.h"

class BeaverSpawner;
class ParticleSystem;

class Beaver : public Object
{
public:
    Beaver(Vec2f _position);
   ~Beaver();

   BeaverSpawner* m_spawnerRef;


    void Render(sf::RenderTexture* _sceneBuffer) override;
    void OnBeginContact(Object* _otherObject) override;
    void OnEndContact(Object* _otherObject) override;
    int GetCost() const;
    int GetRarity() const;
    virtual void Damage(int _iDamage);
    virtual void Update(float _fDeltaTime) override;


protected:
    int m_iCost = 1;
    Vec2f m_fVelocity;
    int m_iHealth = 20;
    int m_iDamage = 1;
    float m_fSpeed = 1;
    int m_iRarity = 1;
    Warehouse* m_warehouse = nullptr;
    unique_ptr<Animator> m_animator;
    float m_woodClock = 0.0f;
    shared_ptr<ParticleSystem> m_bloodParticleSystem = nullptr;
};

// Just doing everything here to save time 

class BossBeaver : public Beaver {
public: 
    BossBeaver(Vec2f _position) : Beaver(_position) {
        m_sprite.setColor(sf::Color::Red);
        m_sprite.setScale(0.30f, 0.30f);
        m_iHealth = 200; // Boss has more health
        m_iDamage = 10; // Boss deals more damage
        m_fSpeed = 0.5f; // Boss moves slower
        m_iCost = 15;  // Cost spawning system
        m_iRarity = 4;
    }

    void Update(float _fDeltaTime) override {
        Beaver::Update(_fDeltaTime);
    }
};

class ArmoredBeaver : public Beaver {
public:
    ArmoredBeaver(Vec2f _position) : Beaver(_position) {
        m_sprite.setColor(sf::Color::Blue);
        m_sprite.setScale(0.15f, 0.15f);
        m_iHealth = 50; 
        m_iDamage = 3;
        m_fSpeed = 0.8f;
        m_iCost = 5;
        m_iRarity = 3;
    }
};

class BeavzerkerBeaver : public Beaver {
public:
    BeavzerkerBeaver(Vec2f _position) : Beaver(_position) {
        m_sprite.setColor(sf::Color::Green);
        m_sprite.setScale(0.08f, 0.08f);
        m_iHealth = 20; 
        m_iDamage = 2;  
        m_fSpeed = 1.5f; 
        m_iCost = 1;
        m_iRarity = 2;
  
    }

    void Update(float _fDeltaTime) override {
        Beaver::Update(_fDeltaTime);
    }
};
