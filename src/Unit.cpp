#include "Log.h"
#include "Unit.h"

namespace Awol {

Unit* Unit::create()
{
    Unit* unit = new Unit;
    return unit;
}

Unit::Unit()
    :m_name("John Doe")
    ,m_class("Infantry")
    ,m_objectKey(Melee1)
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
    context.paintObject(m_objectKey, m_location);
}


}
