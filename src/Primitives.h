#ifndef AwolPrimitives_h
#define AwolPrimitives_h

#include "gameplay.h"

namespace Awol {

class IntSize;

class IntPoint {
public:
	IntPoint()
        :m_x(0)
        ,m_y(0)
    { }
	IntPoint(int x, int y)
        :m_x(x)
        ,m_y(y)
    { }
    explicit IntPoint(const gameplay::Vector2& vector)
        :m_x(vector.x)
        ,m_y(vector.y)
    { }
	
	int x() const { return m_x; }
	int y() const { return m_y; }

    void setX(int x) { m_x = x; }
    void setY(int y) { m_y = y; }

    const IntPoint operator+(const IntSize& size) const;
    const IntPoint operator-(const IntSize& size) const;

    operator gameplay::Vector2() const { return gameplay::Vector2(m_x, m_y); }
    
private:
	int m_x;
	int m_y;
};

class IntSize {
public:
	IntSize()
        :m_dx(0)
        ,m_dy(0)
    { }
	IntSize(int dx, int dy)
        :m_dx(dx)
        ,m_dy(dy)
    { }
    explicit IntSize(const gameplay::Vector2& vector)
        :m_dx(vector.x)
        ,m_dy(vector.y)
    { }
	
	int dx() const { return m_dx; }
	int dy() const { return m_dy; }

    void setDX(int dx) { m_dx = dx; }
    void setDY(int dy) { m_dy = dy; }

    const IntSize operator+(const IntSize& size) const;
    const IntSize operator-(const IntSize& size) const;

    operator gameplay::Vector2() const { return gameplay::Vector2(m_dx, m_dy); }

private:
	int m_dx;
	int m_dy;
};

inline const IntSize operator-(const IntPoint& lhs, const IntPoint& rhs) { return IntSize(lhs.x() - rhs.x(), lhs.y() - rhs.y()); }
inline const IntPoint operator+(const IntSize& lhs, const IntPoint& rhs) { return IntPoint(lhs.dx() + rhs.x(), lhs.dy() + rhs.y()); }

}

#endif