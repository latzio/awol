#ifndef BattleTile_h
#define BattleTile_h

#include "Event.h"
#include "Render.h"
#include "Unit.h"

#include "gameplay.h"

#include <vector>

namespace Awol {

class Terrain : public gameplay::Ref {
public:
    Terrain(TerrainKey key);
    virtual ~Terrain();

    TerrainKey key() const { return m_key; }

private:
    TerrainKey m_key;
};

class BattleTile : public gameplay::Ref {
public:
    static BattleTile* create(TerrainKey, const IntPoint&, const IntSize&);  
    virtual ~BattleTile();

    static void setTileSize(const IntSize&);
    static const IntSize& tileSize();

    void render(RenderContext&);

    Terrain* terrain() const { return m_terrain; }
    void setTerrain(Terrain* terrain);

    Unit* unit() const { return m_unit; }
    bool setUnit(Unit* unit);

    gameplay::Rectangle rect() const;

private:
    BattleTile(TerrainKey, const IntPoint&, const IntSize&);

    IntPoint m_location; // In unscaled, unscrolled battle coordinates.

    Terrain* m_terrain;
    Unit* m_unit;
};

typedef std::vector<BattleTile*> BattleTileRow;
typedef std::vector<BattleTileRow> BattleField;

} // Awol

#endif
