#ifndef Render_h
#define Render_h

#include "gameplay.h"

namespace Awol {

class LayerTiler;

enum TerrainKey {
    InvalidTerrain = 0,
    Grass1 = ' ',
    Hut = '!',
    WaterNW = '\"',
    WaterSE = '#',
    WaterSW = '$',
    WaterS = '%',
    Grass2 = '&',
    DirtNW = '\'',
    DirtNE = '(',
    DirtS = ')',
    DirtNSW = '*',
    DirtSE = '+',
    DirtW = '\'',
    HillW = '-',
    HillSW = '.',
    Trees3 = '/',
    Grass3 = '0',
    Steppes = '1',
};

enum ObjectKey {
    InvalidObject = 0,
    Melee1,
    Melee2,
    Ranged1,
    Ranged2,
};

class RenderContext {
public:
    RenderContext();

    void activateTerrain(LayerTiler* layer);
    void deactivateTerrain();

    void activateUnits(LayerTiler* layer);
    void deactivateUnits();
    
    const gameplay::Matrix& transform() const;
    void applyTransform(const gameplay::Matrix&);
    void setTransform(const gameplay::Matrix&);

    void paintTerrain(TerrainKey, const gameplay::Vector2&);
    void paintObject(ObjectKey, const gameplay::Vector2&);
    

private:
    LayerTiler* m_terrain;
    LayerTiler* m_units;

    gameplay::Matrix m_transformation;

};

} // Awol

#endif
