#pragma once
#include "Object.h"
#include <memory>
#include <SFML/System/Clock.hpp>
#include "Beaver.h"
#include "Text.h"

class Level;

class BeaverSpawner : public Object {
public:
    BeaverSpawner(Vec2f position, std::weak_ptr<b2World> world, const std::string& texturePath, Warehouse* warehouse);
    void Update(float deltaTime) override;
    void Render(sf::RenderTexture* _sceneBuffer) override;
    void AddBudget(int _budget);
    void SetAddGameObjectEvent(shared_ptr<Event2P<void, shared_ptr<GameObject>, int>> _addGameObjectEvent);

private:
    void SpawnBeaver();
    void IncreaseSpawnBudget();

    Warehouse* m_warehouse;
    const float spawnRadius = 200.0f;
    int m_currentRarityMilestone = 500;
    int m_maxSpawnBudget = 20;
    int m_currentSpawnBudget = 15;
    float m_spawnInterval = 15.0f;
    float m_timeSinceLastSpawn = 0;
    float m_timeSinceLastBudgetIncrease = 0.0f;
    float m_maxRarity = 1;
    float m_budgetIncreaseInterval = 30.0f; // Time between increases
    int m_budgetIncreaseAmount = 1; // budget increases every 30 seconds, takes about 900 seconds to get to boss beavers spawning right now 
    shared_ptr<Event2P<void, shared_ptr<GameObject>, int>> m_addGameObjectEvent;
    unique_ptr<Text> m_warningMessage = make_unique<Text>(Vec2f(0, 0), "The Beavers are getting angry...", "Resources/Fonts/AlteHaasGroteskBold.ttf");
};