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

    context.activateLayer(m_tiler);

    std::vector<Unit*>::iterator it = m_units.begin();
    std::vector<Unit*>::iterator last = m_units.end();
    for (; it != last; it++)
        (*it)->render(context);

    context.deactivateLayer();
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
    context.activateLayer(m_tiler);

    Vector2 coord;
    for (coord.x = 0; coord.x < m_size.x; coord.x++)
        for (coord.y = 0; coord.y < m_size.y; coord.y++)
            context.paintLayer(terrainAtCoord(coord), coord);

    context.deactivateLayer();
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

    Matrix scale;
    // Matrix::createScale(Vector3(32, 32, 1), &scale);
    context.applyTransform(scale);

    Forces::iterator it = m_forces.begin();
    Forces::iterator last = m_forces.end();
    for (; it != last; it++)
        (*it)->render(context, screenRect);

    return Animating;
}



}
