#ifndef Render_h
#define Render_h

#include "Primitives.h"

#include "gameplay.h"

namespace Awol {

class LayerTiler;

enum TerrainKey {
    InvalidTerrain = 0,
    Basic = ' ',
    Cover = '!',
    WaterNW = '\"',
    WaterSE = '#',
    WaterSW = '$',
    WaterS = '%',
    Grass2 = '&',
    DirtNW = '\'',
    DirtNE = '(',
    DirtS = ')',
    DirtNSW = '*',
    Cover2 = '+',
    Cover3 = '\'',
    HillW = '-',
    HillSW = '.',
    Trees3 = '/',
    Grass3 = '0',
    Steppes = '1',
};

enum ObjectKey {
    InvalidObject = 0,
    Melee1 = ' ',
    Melee2,
    Ranged1,
    Ranged2,
};

class RenderContext {
public:
    RenderContext();

    void activateLayer(LayerTiler* layer);
    void deactivateLayer();

    void paintActive(unsigned key, const gameplay::Rectangle& untransformed);

    const gameplay::Vector2& scroll() const { return m_scroll; }
    void scrollBy(const gameplay::Vector2& delta) { m_scroll = m_scroll + delta; }
    void setScroll(const gameplay::Vector2& scroll) { m_scroll = scroll; }

    float scale() const { return m_scale; }
    void scaleBy(float scale) { m_scale = m_scale * scale; }
    void scaleAboutPoint(const IntPoint& transformed, float);
    void setScale(float scale) { m_scale = scale; }

    float runtime() const { return m_runtime; }
    void setRuntime(float runtime) { m_runtime = runtime; }

    float elapsed() const { return m_elapsed; }
    void setElapsed(float elapsed) { m_elapsed = elapsed; }

    unsigned frameId() const { return m_frameId; }
    void setFrameId(unsigned frameId) { m_frameId = frameId; }

    // The following methods can be used to convert between coordinate systems:
    // Screen a.k.a. Transformed: Physical pixels on the screen. (0, 0) is the top left corner of the screen.
    // Game a.k.a. Untransformed: Pixels in the battle. Each tile is always BattleTile::tileSize(), (0, 0) is
    //                            the top left corner of the top left tile in the battle field.

    void transformFromScreen(IntPoint&);
    void transformFromScreen(gameplay::Rectangle&);
    void transformFromScreen(gameplay::Vector2&);

    void transformToScreen(IntPoint&);
    void transformToScreen(gameplay::Rectangle&);
    void transformToScreen(gameplay::Vector2&);

private:
    LayerTiler* m_layer;

    // We keep the View transform in floating point to reduce rounding when zooming.
    gameplay::Vector2 m_scroll;
    float m_scale;

    float m_runtime;
    float m_elapsed;
    unsigned m_frameId;

};

} // Awol

#endif
