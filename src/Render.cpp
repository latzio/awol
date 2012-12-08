#include "Render.h"
#include "LayerTiler.h"

using namespace gameplay;

namespace Awol {

RenderContext::RenderContext()
    :m_terrain(0)
    ,m_objects(0)
{
}

const Matrix& RenderContext::transform() const
{
    return m_transformation;
}

void RenderContext::applyTransform(const Matrix& matrix)
{
    m_transformation = m_transformation * matrix;
}

void RenderContext::setTransform(const Matrix& matrix)
{
    m_transformation = matrix;
}

void RenderContext::paintTerrain(TerrainKey key, const Vector2& dst)
{
    if (!m_terrain)
        return;
    
}

void RenderContext::paintObject(ObjectKey key, const Vector2& dst)
{
    if (!m_objects)
        return;

}

}
