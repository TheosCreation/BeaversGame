#ifndef BEAVERSPAWNER_H
#define BEAVERSPAWNER_H

#include "Object.h"
#include <memory>
#include <SFML/System/Clock.hpp>
#include "Beaver.h"

class Level;

class BeaverSpawner : public Object {
public:
    BeaverSpawner(Vec2f position, std::weak_ptr<b2World> world, const std::string& texturePath, Level* level);
    void Update(float deltaTime) override;
    void Render(sf::RenderTexture* sceneBuffer) override;

private:
    void SpawnBeaver();
    Vec2f m_position; 
    float m_spawnInterval;
    float m_timeSinceLastSpawn;
    Level* m_level;
};

#endif // BEAVERSPAWNER_H
