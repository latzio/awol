#include "Battle.h"
#include "LayerTiler.h"
#include "Log.h"
#include "Render.h"

#include "gameplay.h"

using namespace gameplay;

namespace Awol {

Force::Force()
    :m_tiler(0)
{
    TRACE
    m_tiler = LayerTiler::create(Vector2(397, 397), // PNG Size
                                 Vector2(1, 1),     // Sprite origin
                                 Vector2(32, 32),   // Sprite size
                                 Vector2(33, 33));  // Sprite stride
    m_tiler->addFrameSpritesheet("res/units-1.png");

    m_units.push_back(Unit::create());
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
    Vector2 offset;
    Vector2 size = m_tiler->tileSize();

    context.activateLayer(m_tiler);

    std::vector<Unit*>::iterator it = m_units.begin();
    std::vector<Unit*>::iterator last = m_units.end();
    for (; it != last; it++)
        (*it)->render(context);

    context.deactivateLayer();
}

BattleMap* BattleMap::create(const Vector2& size,
                             const std::string& tileMapPath,
                             const std::string& terrainPath)
{
    BattleMap* map = new BattleMap(size, terrainPath);
    map->m_tiler = LayerTiler::create(Vector2(397, 397), // PNG Size
                                      Vector2(1, 1),     // Sprite origin
                                      Vector2(32, 32),   // Sprite size
                                      Vector2(33, 33));  // Sprite stride

    map->m_tiler->setAnimationPeriod(.5);
    map->m_tiler->setAnimationBehaviour(PingPong);
    map->m_tiler->addFrameSpritesheet("res/background-1-1.png");
    map->m_tiler->addFrameSpritesheet("res/background-1-2.png");
    map->m_tiler->addFrameSpritesheet("res/background-1-3.png");
    return map;
}

BattleMap::BattleMap(const Vector2& size, const std::string& terrainPath)
    :m_size(size)
    ,m_tiler(0)
{
    TRACE
    loadTerrainGrid(terrainPath);

    if (m_size.x * m_size.y != m_terrain.size() * m_terrain[0].size()) {
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

    Vector2 coord;
    for (coord.x = 0; coord.x < m_size.x; coord.x++)
        for (coord.y = 0; coord.y < m_size.y; coord.y++)
            context.paintLayer(terrainAtCoord(coord), coord);

    context.deactivateLayer();
}

TerrainKey BattleMap::terrainAtCoord(const Vector2& point)
{
    // The terrain array is actually in column major order so
    // this convenience method gets the the keys we expect from
    // the visual representation.
    if (point.y >= m_terrain.size() || point.x >= m_terrain[0].size())
        return InvalidTerrain;

    return m_terrain[point.y][point.x].key();
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
    while(m_terrain.size() < m_size.y) {
        m_terrain.push_back(TerrainRow());
        while (char key = rawTerrain[count++]) {
            if (key >= ' ' && key < '~') {
                m_terrain.back().push_back(Terrain(static_cast<TerrainKey>(key)));
            } else if (key == '~') {
                if (m_terrain.back().size() != m_size.x) {
                    fprintf(stderr, "Row %ld incorrect size. Fail.\n", m_terrain.size());
                    exit(-1);
                }
                break;
            }
        }
    }
}

Battle::Battle(BattleMap *map, const Forces& forces)
    :m_map(map)
    ,m_forces(forces)
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

bool Battle::handleTouchEvent(const Event& event)
{
	bool consumed = false;

	return consumed;
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
