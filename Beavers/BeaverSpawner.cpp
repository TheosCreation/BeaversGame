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
    if (m_timeSinceLastBudgetIncrease >= m_budgetIncreaseInterval) {
        m_timeSinceLastBudgetIncrease = 0;
        IncreaseSpawnBudget();
    }
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
    if (m_warehouse && m_warehouse->GetWoodAmount() >= m_currentRarityMilestone) {
        m_currentRarityMilestone *= 10;
        m_maxRarity++;

        m_warningMessage->SetSize(20);
        AudioManager::GetInstance().PlaySound("Resources/Audio/BeaverAngrySound.mp3", sf::Vector3f(0, 0, 0), sf::Time(), 1.0, 1.0);
    }
}

void BeaverSpawner::SpawnBeaver() {
    if (m_currentSpawnBudget <= 0) return;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<std::function<shared_ptr<Beaver>()>> beaverFactories = {
        [this]() { return make_shared<Beaver>(GetPosition()); },
        [this]() { return make_shared<BossBeaver>(GetPosition()); },
        [this]() { return make_shared<ArmoredBeaver>(GetPosition()); },
        [this]() { return make_shared<BeavzerkerBeaver>(GetPosition()); }
    };

    while (m_currentSpawnBudget > 0) {
        std::vector<shared_ptr<Beaver>> eligibleBeavers;
        for (auto& factory : beaverFactories) {
            auto beaver = factory();
            if (beaver && beaver->GetRarity() <= m_maxRarity && beaver->GetCost() <= m_currentSpawnBudget) {
                eligibleBeavers.push_back(beaver);
            }
        }

        if (eligibleBeavers.empty()) {
            for (auto& factory : beaverFactories) {
                eligibleBeavers.push_back(factory());
            }
        }

        std::uniform_real_distribution<float> offsetDist(-spawnRadius, spawnRadius);
        auto currentPosition = GetPosition();
        float offsetX = offsetDist(gen);
        float offsetY = offsetDist(gen);
        Vec2f newPosition(currentPosition.x + offsetX, currentPosition.y + offsetY);

        std::uniform_int_distribution<> dis(0, eligibleBeavers.size() - 1);
        auto selectedBeaver = eligibleBeavers[dis(gen)];

        if (m_addGameObjectEvent) {
            m_addGameObjectEvent->execute(selectedBeaver, 0);
        }
        selectedBeaver->m_spawnerRef = this;
        selectedBeaver->SetPosition(newPosition);
        m_currentSpawnBudget -= selectedBeaver->GetCost();
    }
}