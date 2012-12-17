#include "BattleTile.h"
#include "LayerTiler.h"
#include "Log.h"
#include "Render.h"

#include "gameplay.h"

using namespace gameplay;

namespace Awol {

static IntSize s_tileSize;

Terrain::Terrain(TerrainKey key)
    :m_key(key)
{
}

Terrain::~Terrain()
{
}

BattleTile* BattleTile::create(TerrainKey key, const IntPoint& location, const IntSize& size)
{
    return new BattleTile(key, location, size);
}

BattleTile::BattleTile(TerrainKey key, const IntPoint& location, const IntSize& size)
    :m_terrain(new Terrain(key))
    ,m_location(location)
    ,m_unit(0)
{
}

BattleTile::~BattleTile()
{
    setTerrain(0);
    setUnit(0);
}

const IntSize& BattleTile::tileSize()
{
    return s_tileSize;
}

void BattleTile::setTileSize(const IntSize& size)
{
    s_tileSize = size;
}

void BattleTile::render(RenderContext& context)
{
    context.paintActive(m_terrain->key(), rect());
}

void BattleTile::setTerrain(Terrain* terrain)
{
    if (m_terrain)
        m_terrain->release();

    m_terrain = terrain;
    if (m_terrain)
        m_terrain->addRef();
}

bool BattleTile::setUnit(Unit* unit)
{
    // If we have a unit, the only thing we can set is 0.
    if (m_unit && unit)
        return false;

    // Fail to overwrite with existing unit for simplicity's sake.
    if (m_unit == unit)
        return false;
    
    if (m_unit)
        m_unit->release();

    m_unit = unit;
    if (m_unit)
        m_unit->addRef();

    return true;
}

Rectangle BattleTile::rect() const
{
    return Rectangle(m_location.x(), m_location.y(), s_tileSize.dx(), s_tileSize.dy()); 
}

}