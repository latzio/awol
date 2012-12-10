#ifndef Unit_h
#define Unit_h

#include "Render.h"

#include "gameplay.h"

#include <string>

namespace Awol {

class Unit : public gameplay::Ref {
public:
    static Unit* create();

    void render(RenderContext&);

private:
    Unit();
    virtual ~Unit();

private:
    std::string m_name;
    std::string m_class;

    ObjectKey m_objectKey;
    gameplay::Vector2 m_location;
    
    int m_health;
    int m_fuel;

};

}

#endif
