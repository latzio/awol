#ifndef Battle_h
#define Battle_h

#include "Event.h"
#include "Render.h"
#include "Unit.h"

#include "gameplay.h"

#include <vector>

namespace Awol {

class Event;
class LayerTiler;
class RenderContext;

class Force : public gameplay::Ref {
public:
    Force();

    void render(RenderContext&, const gameplay::Rectangle&);

private:
    virtual ~Force();

    std::vector<Unit*> m_units;

    LayerTiler* m_tiler;

};

class Terrain {
public:
    Terrain(TerrainKey key)
        :m_key(key)
    { };

    TerrainKey key() const { return m_key; }

private:
    TerrainKey m_key;
};

typedef std::vector<Terrain> TerrainRow;
typedef std::vector<TerrainRow> TerrainGrid;

class BattleMap : public gameplay::Ref {
public:
    static BattleMap* create(const gameplay::Vector2& size,
                             const std::string& tileMapPath,
                             const std::string& terrainPath);

    void render(RenderContext&, const gameplay::Rectangle&);

private:
    BattleMap(const gameplay::Vector2& size, const std::string& terrain);
    virtual ~BattleMap();

    void loadTerrainGrid(const std::string& path);

    // Game coordinates, not pixels.
    TerrainKey terrainAtCoord(const gameplay::Vector2& point);

    gameplay::Vector2 m_size;
    LayerTiler* m_tiler;
    TerrainGrid m_terrain;

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
    Battle(BattleMap*, const Forces&);

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
