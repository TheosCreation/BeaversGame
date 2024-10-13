#include "BeaverSpawner.h"
#include <algorithm> // std::max
#include <iostream>
#include "Level.h"
#include "Beaver.h"

BeaverSpawner::BeaverSpawner(Vec2f position, std::weak_ptr<b2World> world, const std::string& texturePath)
    : Object(position, texturePath, true), m_spawnInterval(5.0f), m_timeSinceLastSpawn(0.0f)
{
}

void BeaverSpawner::Update(float deltaTime) {
    m_timeSinceLastSpawn += deltaTime;
   
    if (m_timeSinceLastSpawn >= m_spawnInterval) {
        SpawnBeaver();
        m_timeSinceLastSpawn = 0.0f;
        m_spawnInterval = std::max(0.5f, m_spawnInterval * 0.95f); // Decrease interval, but not below 0.5 seconds
    }
}

void BeaverSpawner::Render(sf::RenderTexture* _sceneBuffer) {
    Object::Render(_sceneBuffer);
    // Maybe river?
}

void BeaverSpawner::SetAddGameObjectEvent(shared_ptr<Event2P<void, shared_ptr<GameObject>, int>> _addGameObjectEvent)
{
    m_addGameObjectEvent = _addGameObjectEvent;
}
void BeaverSpawner::SpawnBeaver() 
{
    auto beaver = make_shared<Beaver>(GetPosition());
    m_addGameObjectEvent->execute(beaver, 0);
}