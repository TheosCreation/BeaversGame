#include "Object.h"
#include <memory>
#include <SFML/System/Clock.hpp>
#include "Beaver.h"

class Level;

class BeaverSpawner : public Object {
public:
    BeaverSpawner(Vec2f position, std::weak_ptr<b2World> world, const std::string& texturePath);
    void Update(float deltaTime) override;
    void Render(sf::RenderTexture* _sceneBuffer) override;

    void SetAddGameObjectEvent(shared_ptr<Event2P<void, shared_ptr<GameObject>, int>> _addGameObjectEvent);

private:
    void SpawnBeaver();
    float m_spawnInterval;
    float m_timeSinceLastSpawn;
    shared_ptr<Event2P<void, shared_ptr<GameObject>, int>> m_addGameObjectEvent;
};