#include "BeaverSpawner.h"
#include <algorithm> // std::max
#include <iostream>
#include "Level.h"
#include "Beaver.h"

BeaverSpawner::BeaverSpawner(Vec2f position, std::weak_ptr<b2World> world, const std::string& texturePath, Level* level)
    : Object(position, texturePath, true), m_spawnInterval(5.0f), m_timeSinceLastSpawn(0.0f) , m_position(position), m_level(level) {
    // Additional initialization if needed

}

void BeaverSpawner::Update(float deltaTime) {
    m_timeSinceLastSpawn += deltaTime;
   
    if (m_timeSinceLastSpawn >= m_spawnInterval) {
        SpawnBeaver();
        m_timeSinceLastSpawn = 0.0f;
        m_spawnInterval = std::max(0.5f, m_spawnInterval * 0.95f); // Decrease interval, but not below 0.5 seconds
    }
}

void BeaverSpawner::Render(sf::RenderTexture* sceneBuffer) {
    // Maybe river?
}


void BeaverSpawner::SpawnBeaver() {
    // Ensure the world is still valid
    if (auto world = m_world.lock()) {
        // Create a new Beaver object
        auto beaver = std::make_shared<Beaver>(m_position);

        // Add the Beaver to the level
        if (m_level) {
            m_level->AddGameObject(beaver);
        }
        else {
            std::cerr << "BeaverSpawner: Level reference is null." << std::endl;
        }
    }
    else {
        std::cerr << "BeaverSpawner: World reference is expired." << std::endl;
    }
}