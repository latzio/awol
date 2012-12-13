#include "Primitives.h"

namespace Awol {

const IntPoint IntPoint::operator+(const IntSize& size) const 
{ 
    return IntPoint(m_x + size.dx(), m_y + size.dy()); 
}

const IntPoint IntPoint::operator-(const IntSize& size) const 
{ 
    return IntPoint(m_x - size.dx(), m_y - size.dy()); 
}
    
const IntSize IntSize::operator+(const IntSize& size) const 
{ 
    return IntSize(m_dx + size.dx(), m_dy + size.dy()); 
}

const IntSize IntSize::operator-(const IntSize& size) const 
{ 
    return IntSize(m_dx - size.dx(), m_dy - size.dy()); 
}
    

}

