# Regen
Juego regen --- utilizamos el motor de juegos HCGIL
nuestro código esta implementado bajo el patrón de arquitectura ECS (Entity Component System)

Metodologías usadas: Principio abierto / cerrado (OCP) para extender el comportamiento de una clase,
a través de herencia , interfaz y composición , pero sin permitir que la apertura de esta clase haga modificaciones menores.
ejemplo:





Estilo things:
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
