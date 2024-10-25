#include "BeaverSpawner.h"
#include <algorithm> // std::max
#include <iostream>
#include "Level.h"
#include "Beaver.h"

BeaverSpawner::BeaverSpawner(Vec2f position, std::weak_ptr<b2World> world, const std::string& texturePath, Warehouse* warehouse)
    : Object(position, texturePath, true), m_spawnInterval(10.0f), m_timeSinceLastSpawn(0.0f), m_currentSpawnBudget(m_maxSpawnBudget), m_warehouse(warehouse), m_budgetIncreaseInterval(30.0f)
{
}

void BeaverSpawner::Update(float deltaTime) {
    m_timeSinceLastSpawn += deltaTime;
    m_timeSinceLastBudgetIncrease += deltaTime;

    if (m_timeSinceLastSpawn >= m_spawnInterval) {
        SpawnBeaver();
        m_timeSinceLastSpawn = 0.0f;
        m_spawnInterval = std::max(0.5f, m_spawnInterval * 0.95f);
    }
    if (m_timeSinceLastSpawn >= m_budgetIncreaseInterval) {
        IncreaseSpawnBudget();
    }
  //  Debug::Log(m_currentSpawnBudget);
    
}

void BeaverSpawner::Render(sf::RenderTexture* _sceneBuffer) {
    Object::Render(_sceneBuffer);
    // Maybe river?
}

void BeaverSpawner::AddBudget(int _budget)
{
    m_currentSpawnBudget += _budget;
}


void BeaverSpawner::SetAddGameObjectEvent(shared_ptr<Event2P<void, shared_ptr<GameObject>, int>> _addGameObjectEvent)
{
    m_addGameObjectEvent = _addGameObjectEvent;
}
void BeaverSpawner::IncreaseSpawnBudget() {
    AddBudget(m_budgetIncreaseAmount);
     if (m_currentRarityMilestone > m_warehouse->GetWoodAmount()) {
         m_currentRarityMilestone *= 10;
         m_maxRarity++;

         Debug::Log("This thing workin");

         m_warningMessage->SetSize(20);
         AudioManager::GetInstance().PlaySound("Resources/Audio/BeaverAngrySound", sf::Vector3f(0, 0, 0), sf::Time(), 1.0, 1.0);
     }

}

void BeaverSpawner::SpawnBeaver() {
    if (m_currentSpawnBudget <= 0) return;
    Debug::Log(m_maxRarity);
    std::random_device rd;
    std::mt19937 gen(rd());

    // List of potential beaver types
    std::vector<std::function<shared_ptr<Beaver>()>> beaverFactories = {
       [this]() { return make_shared<Beaver>(GetPosition()); },
       [this]() { return make_shared<BossBeaver>(GetPosition()); },
       [this]() { return make_shared<ArmoredBeaver>(GetPosition()); },
       [this]() { return make_shared<BeavzerkerBeaver>(GetPosition()); }
    };


    // Filter beavers by rarity
    std::vector<shared_ptr<Beaver>> eligibleBeavers;
    for (auto& factory : beaverFactories) {
        auto beaver = factory();
        if (beaver->GetRarity() <= m_maxRarity && beaver->GetCost() <= m_currentSpawnBudget){
            eligibleBeavers.push_back(beaver);
        }
    }

    // If no eligible beavers, use all beavers
    if (eligibleBeavers.empty()) {
        Debug::Log("empty");
        for (auto& factory : beaverFactories) {
            eligibleBeavers.push_back(factory());
        }
    }

    // Randomly select a beaver from the eligible list
    std::uniform_int_distribution<> dis(0, eligibleBeavers.size() - 1);
    auto selectedBeaver = eligibleBeavers[dis(gen)];

    
    m_addGameObjectEvent->execute(selectedBeaver, 0);
    selectedBeaver->m_spawnerRef = this;
    m_currentSpawnBudget -= selectedBeaver->GetCost();
    
}
