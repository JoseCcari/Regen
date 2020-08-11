#include <vector>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#define wx 800
#define wy 800
#define tamPat 30
#define patt 5

struct Transform
{
    // Posicion
    float px;
    float py;

    // Rotacion
    float r;

    // Escala
    float sx;
    float sy;
};

struct Collider
{
    float rx;
    float ry;
};

struct Sprite
{
    sf::RectangleShape rs;
    sf::Texture txt;
};

struct Animation
{
    int state;
    std::vector<Sprite*> sprites;
};

struct Stats
{
    float damage;
    float velocity;
};

/**/

class Entidad
{
public:
    int id;
    Transform* transform;
};

class Potato : public Entidad
{
public:
    Collider* collider;
    Sprite* sprite;
    Stats* stats;
};

/**/

class BufferManager
{
public:
    // ComponentBuffers
    static std::vector<Transform> cTransformBuffer;
    static std::vector<Collider> cColliderBuffer;
    static std::vector<Sprite> cSpriteBuffer;
    static std::vector<Animation> cAnimationBuffer;
    static std::vector<Stats> cStatsBuffer;

    // Entities
    static std::vector<Potato> ePotatoBuffer;

private:
    BufferManager() {}
};

std::vector<Transform> BufferManager::cTransformBuffer {};
std::vector<Collider> BufferManager::cColliderBuffer {};
std::vector<Sprite> BufferManager::cSpriteBuffer {};
std::vector<Animation> BufferManager::cAnimationBuffer {};
std::vector<Stats> BufferManager::cStatsBuffer {};

std::vector<Potato> BufferManager::ePotatoBuffer {};

class PotatoCreator
{
public:
    //retorna el id para hallar la patata creada
    static int createPatata(float x, float y, float r = 0.0f, float sx = 1.0f, float sy = 1.0f, float damage = 1.0f, float velocity = 0.4f)
    {
        int cTransformNextIndex = BufferManager::cTransformBuffer.size();
        BufferManager::cTransformBuffer.push_back(Transform {x, y, r, sx, sy});

        int cColliderNextIndex = BufferManager::cColliderBuffer.size();
        BufferManager::cColliderBuffer.push_back(Collider {30, 30});

        int cSpriteNextIndex = BufferManager::cSpriteBuffer.size();
        BufferManager::cSpriteBuffer.push_back(Sprite {sf::RectangleShape {}, sf::Texture {}});

        sf::Texture& txt = BufferManager::cSpriteBuffer[cSpriteNextIndex].txt;
        txt.loadFromFile("papa.png");

        sf::RectangleShape& rs = BufferManager::cSpriteBuffer[cSpriteNextIndex].rs;
        rs.setSize(sf::Vector2f {30.0f, 30.0f});
        rs.setPosition(sf::Vector2f {x, y});
        rs.setTexture(&txt, true);

        int cStatsNextIndex = BufferManager::cStatsBuffer.size();
        BufferManager::cStatsBuffer.push_back(Stats {damage, velocity});

        Potato p;
        p.transform = &BufferManager::cTransformBuffer[cTransformNextIndex]; // para hallar los componentes de la patata en la ultima posicion del buffer :v 
        p.collider  = &BufferManager::cColliderBuffer[cColliderNextIndex];
        p.sprite    = &BufferManager::cSpriteBuffer[cSpriteNextIndex];
        p.stats     = &BufferManager::cStatsBuffer[cStatsNextIndex];
        BufferManager::ePotatoBuffer.push_back(p);

        return BufferManager::ePotatoBuffer.size() - 1;
    }

private:
    PotatoCreator() {}
};

class PotatoController
{
public:
    static void move(int id)
    {
        Potato& p = BufferManager::ePotatoBuffer[id];
        float& px = p.transform->px;
        float& py = p.transform->py;
        sf::RectangleShape& rs = p.sprite->rs;

        float tamx = 2.0f * p.collider->rx;
        float tamy = 2.0f * p.collider->ry;
        float dam = p.stats->damage;        
        float vel = p.stats->velocity;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && px < wx - tamx)
        {
            px += vel;
            rs.setPosition(sf::Vector2f {px, py});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && px > 0)
        {
            px -= vel;
            rs.setPosition(sf::Vector2f {px, py});
        }
    }

private:
    PotatoController() {};
};

class RenderingSystem
{
public:
    static void draw(sf::RenderWindow& window)
    {
        for(const Sprite& s : BufferManager::cSpriteBuffer)
        {
            window.draw(s.rs);
        }
    }

private:
    RenderingSystem() {};
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(wx, wy), "Potato masheed");
    sf::RectangleShape fondo(sf::Vector2f(wx, wy));

    int miPatata1 = PotatoCreator::createPatata(wx / 2 - tamPat / 2, wy / 2 - tamPat / 2);

    while(window.isOpen())
    {
        window.clear();
        PotatoController::move(miPatata1);
        RenderingSystem::draw(window);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.display();
    }

    return 0;
}
