#include "Battle.h"
#include "LayerTiler.h"
#include "Log.h"
#include "Render.h"

#include "gameplay.h"

using namespace gameplay;

namespace Awol {

Force* Force::create(BattleMap* map)
{
    return new Force(map);
}

Force::Force(BattleMap* map)
    :EventTarget()
    ,m_map(map)
    ,m_tiler(0)
{
    TRACE
    m_tiler = LayerTiler::create(IntSize(397, 397), // PNG Size
                                 IntPoint(1, 1),    // Sprite origin
                                 IntSize(32, 32),   // Sprite size
                                 IntSize(33, 33));  // Sprite stride
    m_tiler->addFrameSpritesheet("res/units-1.png");

    m_units.push_back(Unit::create());

    static int demo = 4;
    m_units[0]->setTile(m_map->getTile(demo++, demo++));
}

Force::~Force()
{
    TRACE
    std::vector<Unit*>::iterator it = m_units.begin();
    std::vector<Unit*>::iterator last = m_units.end();
    for (; it != last; it++)
        (*it)->release();
}

void Force::render(RenderContext& context, const gameplay::Rectangle& rect)
{
    context.activateLayer(m_tiler);

    std::vector<Unit*>::iterator it = m_units.begin();
    std::vector<Unit*>::iterator last = m_units.end();
    for (; it != last; it++)
        (*it)->render(context);

    context.deactivateLayer();
}

bool Force::handleTouchEvent(const Event& event)
{

    return false;
}

BattleMap* BattleMap::create(const IntSize& size,
                             const std::string& tileMapPath,
                             const std::string& terrainPath)
{
    BattleMap* map = new BattleMap(size, terrainPath);
    map->m_tiler = LayerTiler::create(IntSize(397, 397), // PNG Size
                                      IntPoint(1, 1),    // Sprite origin
                                      IntSize(32, 32),   // Sprite size
                                      IntSize(33, 33));  // Sprite stride

    map->m_tiler->setAnimationPeriod(.5);
    map->m_tiler->setAnimationBehaviour(PingPong);
    map->m_tiler->addFrameSpritesheet("res/background-1-1.png");
    map->m_tiler->addFrameSpritesheet("res/background-1-2.png");
    map->m_tiler->addFrameSpritesheet("res/background-1-3.png");
    return map;
}

BattleMap::BattleMap(const IntSize& size, const std::string& terrainPath)
    :m_size(size)
    ,m_tiler(0)
{
    TRACE
    loadTerrainGrid(terrainPath);

    if (m_size.area() != m_battleField.size() * m_battleField[0].size()) {
        fprintf(stderr, "Error: Map size not equal to terrain mask.\n");
        exit(-1);
    }
}

BattleMap::~BattleMap()
{
    TRACE
    if (m_tiler)
        m_tiler->release();
    m_tiler = 0;
}

void BattleMap::render(RenderContext& context, const gameplay::Rectangle& rect)
{
    context.activateLayer(m_tiler);

    for (unsigned row = 0; row < m_battleField.size(); row++) {
        for (unsigned col = 0; col < m_battleField[0].size(); col++) {
            getTile(row, col)->render(context);
        }
    }

    context.deactivateLayer();
}

BattleTile* BattleMap::getTileAt(const IntPoint& point) const
{
    if (point.x() < 0 || point.y() < 0)
        return 0;

    return getTile(point.y() / BattleTile::tileSize().dy(), point.x() / BattleTile::tileSize().dx());
}

BattleTile* BattleMap::getTile(unsigned row, unsigned col) const
{
    if (row >= m_battleField.size() || col >= m_battleField[0].size())
        return 0;

    return m_battleField[row][col];
}

void BattleMap::loadTerrainGrid(const std::string& path)
{
    FILE *f = fopen(path.c_str(), "rb");
    fseek(f, 0, SEEK_END);
    unsigned rawSize = ftell(f);
    fseek(f, 0, SEEK_SET);

    std::string rawTerrain;
	rawTerrain.reserve(rawSize);

    fread(&rawTerrain[0], rawSize, 1, f);
    fclose(f);

    unsigned count = 0;
    IntPoint location;

    while(m_battleField.size() < static_cast<unsigned>(m_size.dy())) {
        m_battleField.push_back(BattleTileRow());
        while (char key = rawTerrain[count++]) {
            if (key >= ' ' && key < '~') {
                m_battleField.back().push_back(BattleTile::create(static_cast<TerrainKey>(key), location, BattleTile::tileSize()));
                location.setX(location.x() + BattleTile::tileSize().dx());
            } else if (key == '~') {
                location.setX(0);
                location.setY(location.y() + BattleTile::tileSize().dy());
                if (m_battleField.back().size() != m_size.dx()) {
                    fprintf(stderr, "Row %ld incorrect size. Fail.\n", m_battleField.size());
                    exit(-1);
                }
                break;
            }
        }
    }
}

Battle::Battle(BattleMap *map)
    :m_map(map)
{
    TRACE
    m_map->addRef();

    // Ref all the forces.
    Forces::iterator it = m_forces.begin();
    Forces::iterator last = m_forces.end();
    for (; it != last; ++it)
        (*it)->addRef();
}

Battle::~Battle()
{
    TRACE
    m_map->release();

    Forces::iterator it = m_forces.begin();
    Forces::iterator last = m_forces.end();
    for (; it != last; ++it)
        (*it)->release();
}

void Battle::addForce(Force* force)
{
    if (force) {
        force->addRef();
        m_forces.push_back(force);
    }
}

static Unit* s_focus = 0;

bool Battle::handleTouchEvent(const Event& event)
{
    BattleTile* tile = m_map->getTileAt(event.point());
    Unit* unit = tile ? tile->unit() : 0;

    switch(event.getType()) {
    case TouchStart: {
        // Set the focus to the unit, if any. Otherwise clear it.
        s_focus = unit;
        break;
    }
    case TouchMove: {
        break;
    }
    case TouchEnd: {
        if (s_focus && tile)
            s_focus->setTile(tile);
    }
    }

    return s_focus;
}

void Battle::update(double elapsedTime)
{
}

RenderingResult Battle::render(RenderContext& context, double elapsedTime)
{
    static const gameplay::Rectangle screenRect(0, 0, 1280, 768);

    m_map->render(context, screenRect);

    Forces::iterator it = m_forces.begin();
    Forces::iterator last = m_forces.end();
    for (; it != last; it++)
        (*it)->render(context, screenRect);

    return Animating;
}



}
