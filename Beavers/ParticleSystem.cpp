#include "ParticleSystem.h"

void ParticleSystem::SetEmitterPosition(sf::Vector2f _newPosition)
{
    m_emitterPosition = _newPosition;
}

void ParticleSystem::Render(sf::RenderTexture* _sceneBuffer)
{
    // Draw the particle system to the given render texture
    _sceneBuffer->draw(*this);
    _sceneBuffer->display();
}

void ParticleSystem::Update(float _fDeltaTime)
{
    if (m_isPaused) return; // Don't update if paused

    m_elapsedTime += _fDeltaTime;

    // Stop emitting if play time is over
    bool emitParticles = m_elapsedTime < m_playLength;

    for (std::size_t i = 0; i < m_particles.size(); ++i)
    {
        Particle& p = m_particles[i];

        // Update the particle lifetime
        p.lifetime -= sf::seconds(_fDeltaTime);

        // Check if the particle is dead
        if (p.lifetime <= sf::Time::Zero)
        {
            // If the particle is dead, don't update its position anymore
            if (emitParticles)
            {
                resetParticle(i); // Respawn it if still emitting
            }
            else
            {
                // Optionally set the particle's velocity to zero or any other behavior
                p.velocity = sf::Vector2f(0.f, 0.f);
                continue; // Skip further processing for dead particles
            }
        }

        // Update the position of the corresponding vertex
        // Only update position if the particle is still alive
        for (int j = 0; j < 4; ++j)
        {
            m_vertices[i * 4 + j].position += p.velocity * _fDeltaTime;
        }

        // Update the alpha (transparency) of the particle according to its lifetime
        float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
        sf::Uint8 alpha = static_cast<sf::Uint8>(ratio * 255);
        for (int j = 0; j < 4; ++j)
        {
            m_vertices[i * 4 + j].color.a = alpha;
        }
    }
}

void ParticleSystem::SetTexture(sf::Texture* _texture)
{
    m_texture = _texture;
}

void ParticleSystem::resetParticle(std::size_t index)
{
    // Give a random velocity and lifetime to the particle
    float angle = (std::rand() % 360) * 3.14f / 180.f;
    float speed = (std::rand() % 50) + 50.f;
    m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
    m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

    // Reset the position of the corresponding quad vertices
    sf::Vector2f position = m_emitterPosition;
    float halfSize = m_particleSize / 2.f;

    // Calculate the indices for the 4 vertices of the quad
    std::size_t vertexIndex = index * 4;

    // Set the quad vertices based on the particle's size
    m_vertices[vertexIndex + 0].position = position + sf::Vector2f(-halfSize, -halfSize);
    m_vertices[vertexIndex + 1].position = position + sf::Vector2f(halfSize, -halfSize);
    m_vertices[vertexIndex + 2].position = position + sf::Vector2f(halfSize, halfSize);
    m_vertices[vertexIndex + 3].position = position + sf::Vector2f(-halfSize, halfSize);

    // Optionally set texture coordinates if using a texture atlas
    // Example assuming the entire texture is used:
    m_vertices[vertexIndex + 0].texCoords = sf::Vector2f(0.f, 0.f);
    m_vertices[vertexIndex + 1].texCoords = sf::Vector2f(m_texture->getSize().x, 0.f);
    m_vertices[vertexIndex + 2].texCoords = sf::Vector2f(m_texture->getSize().x, m_texture->getSize().y);
    m_vertices[vertexIndex + 3].texCoords = sf::Vector2f(0.f, m_texture->getSize().y);
}

void ParticleSystem::Play()
{
    m_isPaused = false;
    m_elapsedTime = 0.f;
}

void ParticleSystem::SetPlayTime(float playTime)
{
    m_playLength = playTime;
}

void ParticleSystem::Pause()
{
    m_isPaused = true;
}

void ParticleSystem::Stop()
{
    m_isPaused = true;
    m_elapsedTime = m_playLength;
}