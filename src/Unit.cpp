#include "BattleTile.h"
#include "Log.h"
#include "Unit.h"

#include "gameplay.h"

using namespace gameplay;

namespace Awol {

Unit* Unit::create()
{
    Unit* unit = new Unit;
    return unit;
}

Unit::Unit()
    :m_name("John Doe")
    ,m_job("Infantry")
    ,m_objectKey(Melee1)
    ,m_tile(0)
    ,m_health(100)
    ,m_fuel(0)
{
    TRACE
}

Unit::~Unit()
{
    TRACE
}

void Unit::render(RenderContext& context)
{
    if (m_tile)
        context.paintActive(m_objectKey, m_tile->rect());
}

bool Unit::setTile(BattleTile* tile)
{
    // Cannot move over another unit.
    if (tile && !tile->setUnit(this))
        return false;

    // If we're successfully moved, remove us from the old tile.
    if (m_tile)
        m_tile->setUnit(0);

    m_tile = tile;
    return true;
}


}
