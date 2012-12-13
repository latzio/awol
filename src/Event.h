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
	EventTarget();
	virtual ~EventTarget();

	virtual bool handleTouchEvent(const Event&) = 0;

};

class Event {
public:
	Event(EventType type, IntPoint, int index);
	~Event();
	
	EventType getType() const { return m_type; }
    const IntPoint& point() const { return m_point; }

private:
	EventType m_type;
	IntPoint m_point;
	int m_index;
};

}

#endif