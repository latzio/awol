#ifndef Unit_h
#define Unit_h

#include "Render.h"

#include "gameplay.h"

#include <string>

namespace Awol {

class BattleTile;

class Unit : public gameplay::Ref {
public:
    static Unit* create();

    void render(RenderContext&);

    const std::string& job() { return m_job; }
    const std::string& name() { return m_name; }

    BattleTile* tile() const { return m_tile; }
    bool setTile(BattleTile* tile);

private:
    Unit();
    virtual ~Unit();

private:
    std::string m_name;
    std::string m_job;

    ObjectKey m_objectKey;

    BattleTile* m_tile;
    
    int m_health;
    int m_fuel;

};

}

#endif
