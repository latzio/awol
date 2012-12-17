#ifndef Battle_h
#define Battle_h

#include "BattleTile.h"
#include "Event.h"
#include "Render.h"
#include "Unit.h"

#include "gameplay.h"

#include <vector>

namespace Awol {

class BattleMap;
class Event;
class LayerTiler;
class RenderContext;

class Force : public gameplay::Ref,
              public EventTarget {
public:
    static Force* create(BattleMap*);

    void render(RenderContext&, const gameplay::Rectangle&);

    // Event Target
    virtual bool handleTouchEvent(const Event& event);

private:
    Force(BattleMap*);
    virtual ~Force();

    BattleMap* m_map;
    std::vector<Unit*> m_units;

    LayerTiler* m_tiler;

};

class BattleMap : public gameplay::Ref {
public:
    static BattleMap* create(const IntSize& size,
                             const std::string& tileMapPath,
                             const std::string& terrainPath);

    void render(RenderContext&, const gameplay::Rectangle&);

    // Unscaled, unzoomed game coordinates.
    BattleTile* getTileAt(const IntPoint& point) const;

    // BattleField vector elements
    BattleTile* getTile(unsigned row, unsigned col) const;

private:
    BattleMap(const IntSize& size, const std::string& terrain);
    virtual ~BattleMap();

    void loadTerrainGrid(const std::string& path);

    IntSize m_size;
    LayerTiler* m_tiler;
    BattleField m_battleField;

};


enum RenderingResult {
    Complete,
    Animating,
};

typedef std::vector<Force*> Forces;

class Battle : public gameplay::Ref {
public:
    // A battle is constructed with a BattleMap upon which the battle occurs,
    // and a set of forces who oppose
    // A LevelMap to contain the grid information, and two object
    Battle(BattleMap*);

    void addForce(Force*);

    bool handleTouchEvent(const Event&);

    void update(double elapsedTime);

    RenderingResult render(RenderContext&, double elapsedTime);


private:
    virtual ~Battle();


    BattleMap* m_map;
    Forces m_forces;


};

} // Awol

#endif
