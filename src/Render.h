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

    // paintActive operates in unscrolled, unscaled game coordinates.
    void paintActive(unsigned key, const gameplay::Rectangle&);

    const IntSize& scroll() const { return m_scroll; }
    void scrollBy(const IntSize& delta) { m_scroll = m_scroll + delta; }
    void setScroll(const IntSize& scroll) { m_scroll = scroll; }

    float scale() const { return m_scale; }
    void scaleBy(float scale) { m_scale = m_scale * scale; }
    void setScale(float scale) { m_scale = scale; }

    float runtime() const { return m_runtime; }
    void setRuntime(float runtime) { m_runtime = runtime; }

    float elapsed() const { return m_elapsed; }
    void setElapsed(float elapsed) { m_elapsed = elapsed; }

    unsigned frameId() const { return m_frameId; }
    void setFrameId(unsigned frameId) { m_frameId = frameId; }

    void transformFromScreen(IntPoint&);

    void transformToScreen(IntPoint&);
    void transformToScreen(gameplay::Rectangle&);
    void transformPointToScreen(gameplay::Vector2&);
    void transformSizeToScreen(gameplay::Vector2&);

private:
    LayerTiler* m_layer;

    // These combine to form the view transformation, basically.
    IntSize m_scroll; // Essentially Scroll Position
    float m_scale; // Linear zoom on XY plane.

    float m_runtime;
    float m_elapsed;
    unsigned m_frameId;

};

} // Awol

#endif
