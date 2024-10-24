#pragma once
#include "Object.h"
#include <memory>
#include <SFML/System/Clock.hpp>
#include "Beaver.h"

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
    void IncreaseSpawnBudget(float deltaTime);

    Warehouse* m_warehouse;

    int m_currentRarityMilestone = 100;
    int m_maxSpawnBudget = 2;
    int m_currentSpawnBudget;
    float m_spawnInterval;
    float m_timeSinceLastSpawn;
    float m_timeSinceLastBudgetIncrease = 0.0f;
    float m_maxRarity = 1;
    int m
    float m_budgetIncreaseRate = 10.0f; // Time between i
    int m_budgetIncreaseAmount = 5; // Increase per 
    shared_ptr<Event2P<void, shared_ptr<GameObject>, int>> m_addGameObjectEvent;
};