#include "Battle.h"
#include "LayerTiler.h"
#include "Log.h"
#include "Render.h"

#include "level1.h"

using namespace gameplay;

namespace Awol {

Force::Force()
    :m_tiler(0)
{
    TRACE
    m_tiler = LayerTiler::create(Vector2(397, 397), // PNG Size
                                 Vector2(1, 1),     // Sprite origin
                                 Vector2(32, 32),   // Sprite size
                                 Vector2(33, 33));  // Sprite stride
    m_tiler->addFrameSpritesheet("res/units-1.png");

    m_units.push_back(Unit::create());
}

Force::~Force()
{
    TRACE
    std::vector<Unit*>::iterator it = m_units.begin();
    std::vector<Unit*>::iterator last = m_units.end();
    for (; it != last; it++)
        (*it)->release();
}

void Force::render(RenderContext& context, const Rectangle& rect)
{
    Vector2 offset;
    Vector2 size = m_tiler->tileSize();
    
    context.activateUnits(m_tiler);

    std::vector<Unit*>::iterator it = m_units.begin();
    std::vector<Unit*>::iterator last = m_units.end();
    for (; it != last; it++)
        (*it)->render(context);

    context.deactivateUnits();
}

BattleMap* BattleMap::create(const Vector2& size,
                             const std::string& tileMapPath,
                             const std::string& terrain)
{
    BattleMap* map = new BattleMap(size, terrain);
    map->m_tiler = LayerTiler::create(Vector2(397, 397), // PNG Size
                                      Vector2(1, 1),     // Sprite origin
                                      Vector2(32, 32),   // Sprite size
                                      Vector2(33, 33));  // Sprite stride

    map->m_tiler->setAnimationPeriod(.5);
    map->m_tiler->setAnimationBehaviour(PingPong);
    map->m_tiler->addFrameSpritesheet("res/background-1-1.png");
    map->m_tiler->addFrameSpritesheet("res/background-1-2.png");
    map->m_tiler->addFrameSpritesheet("res/background-1-3.png");
    return map;
}

BattleMap::BattleMap(const Vector2& size, const std::string& terrain)
    :m_size(size)
    ,m_tiler(0)
    ,m_terrain(terrain)
{
    TRACE
    if (m_size.x * m_size.y != terrain.size()) {
        fprintf(stderr, "Error: Map size not equal to mask.\n");
        exit(-1);
    }
}

BattleMap::~BattleMap()
{
    TRACE
    if (m_tiler)
        m_tiler->release();
    m_tiler = 0;
}

void BattleMap::render(RenderContext& context, const Rectangle& rect)
{
    Vector2 offset;
    Vector2 size = m_tiler->tileSize();
    
    context.activateTerrain(m_tiler);
    
    for (offset.x = rect.left(); offset.x < rect.right(); offset.x = offset.x + size.x) {
        for (offset.y = rect.top(); offset.y < rect.bottom(); offset.y = offset.y + size.y) {
            Vector2 coord(offset.x / size.x, offset.y / size.y);
            context.paintTerrain(terrainAtCoord(coord), offset);
        }
    }

    context.deactivateTerrain();
}

TerrainKey BattleMap::terrainAtCoord(const Vector2& point)
{
    // Calculate the 1-dimensional index from coordinates and
    // make sure it's within our range.
    int index = point.y * m_size.x + point.x;
    if (index >= 0 && index < m_terrain.size()) {
        char key = m_terrain[index];
        if (key >= ' ')
            return static_cast<TerrainKey>(key);
    }

    return InvalidTerrain;
}

Battle::Battle(BattleMap *map, const Forces& forces)
    :m_map(map)
    ,m_forces(forces)
{
    TRACE
    m_map->addRef();    

    // Ref all the forces.
    Forces::iterator it = m_forces.begin();
    Forces::iterator last = m_forces.end();
    for (; it != last; ++it)
        (*it)->addRef();
}

Battle::~Battle()
{
    TRACE
    m_map->release();

    Forces::iterator it = m_forces.begin();
    Forces::iterator last = m_forces.end();
    for (; it != last; ++it)
        (*it)->release();
}   

void Battle::update(double elapsedTime)
{
}

RenderingResult Battle::render(RenderContext& context, double elapsedTime)
{
    static const Rectangle screenRect(0, 0, 1280, 768);

    m_map->render(context, screenRect);

    Forces::iterator it = m_forces.begin();
    Forces::iterator last = m_forces.end();
    for (; it != last; it++)
        (*it)->render(context, screenRect);

    return Animating;
}



}
