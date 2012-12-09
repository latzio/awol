#include "Battle.h"
#include "LayerTiler.h"
#include "Log.h"
#include "Render.h"

#include "level1.h"

using namespace gameplay;

namespace Awol {

Force::Force()
{
}

Force::~Force()
{
}

BattleMap* BattleMap::create(const Vector2& size,
                             const std::string& tileMapPath,
                             const std::string& terrain)
{
    BattleMap* map = new BattleMap(size, terrain);
    map->m_tiler = LayerTiler::create(tileMapPath,
                                      Vector2(397, 397), // PNG Size
                                      Vector2(1, 1),     // Sprite origin
                                      Vector2(32, 32),   // Sprite size
                                      Vector2(33, 33));  // Sprite stride
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
    m_map->render(context, Rectangle(0, 0, 1280, 768));

    return Animating;
}



}
