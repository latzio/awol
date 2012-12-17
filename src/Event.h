#ifndef AwolEvent_h
#define AwolEvent_h

#include "Primitives.h"

namespace Awol {

class Event;

enum EventType {
	TouchStart,
	TouchMove,
	TouchEnd,
};

class EventTarget {
public:
	virtual ~EventTarget();

	virtual bool handleTouchEvent(const Event&) = 0;

protected:
    EventTarget();
};

class Event {
public:
	Event(EventType type, IntPoint, int index);
	~Event();
	
	EventType getType() const { return m_type; }
    const IntPoint& point() const { return m_point; }

private:
	EventType m_type;
	IntPoint m_point; // Game coordinates. Unscrolled, unzoomed coordinates.
	int m_index;
};

}

#endif