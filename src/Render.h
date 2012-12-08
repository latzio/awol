#ifndef Render_h
#define Render_h

#include "gameplay.h"

namespace Awol {

class LayerTiler;

enum TerrainKey {
    Grass1,
    Grass2,
    Cover1,
    Cover2,
};

enum ObjectKey {
    Melee1,
    Melee2,
    Ranged1,
    Ranged2,
};

class RenderContext {
public:
    RenderContext();

    void setTerrain(LayerTiler* layer) { m_terrain = layer; }
    void setObjects(LayerTiler* layer) { m_objects = layer; }
    
    const gameplay::Matrix& transform() const;
    void applyTransform(const gameplay::Matrix&);
    void setTransform(const gameplay::Matrix&);

    void paintTerrain(TerrainKey, const gameplay::Vector2&);
    void paintObject(ObjectKey, const gameplay::Vector2&);
    

private:
    LayerTiler* m_terrain;
    LayerTiler* m_objects;

    gameplay::Matrix m_transformation;

};

} // Awol

#endif
