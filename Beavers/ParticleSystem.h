#include "Utils.h"
#include "GameObject.h"

class ParticleSystem : public sf::Drawable, public sf::Transformable, public GameObject
{
public:

    ParticleSystem(unsigned int count) :
        m_particles(count),
        m_vertices(sf::Quads, count * 4), // Each particle requires 4 vertices
        m_lifetime(sf::seconds(3.f)),
        m_emitterPosition(0.f, 0.f)
    {
    }

    virtual void SetPosition(Vec2f _newPosition) override {};
    virtual void AddPosition(Vec2f _displacement) override {};
    virtual Vec2f GetPosition() override { return Vec2f(); };

    void SetEmitterPosition(sf::Vector2f _newPosition);

    void Render(sf::RenderTexture* _sceneBuffer) override;

    void Update(float _fDeltaTime);

    void SetTexture(sf::Texture* _texture);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // our particles 
        states.texture = m_texture;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

private:

    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lifetime;
    };

    void resetParticle(std::size_t index);

    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::Vector2f m_emitterPosition;
    sf::Texture* m_texture = nullptr; 
    float m_particleSize = 10.f;

};