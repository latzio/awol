#include "Event.h"

namespace Awol {

EventTarget::EventTarget()
{
}

EventTarget::~EventTarget()
{
}

Event::Event(EventType type, IntPoint point, int index)
	:m_type(type)
	,m_point(point)
	,m_index(index)
{ }

Event::~Event()
{
}

}