#include "Battle.h"
#include "LayerTiler.h"
#include "Log.h"
#include "Render.h"

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
                             const std::string& terrainMask,
                             const std::string& renderMask)
{
    BattleMap* map = new BattleMap(size);
    map->m_tiler = new LayerTiler();
    map->m_tiler->initialize();
    return map;
}

BattleMap::BattleMap(const Vector2& size)
    :m_size(size)
    ,m_tiler(0)
{
    TRACE
}

BattleMap::~BattleMap()
{
    TRACE
}

void BattleMap::render(RenderContext& context)
{
    m_tiler->fill(Rectangle(0,0, 1280, 768), context.transform());
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
    m_map->render(context);

    return Animating;
}



}
