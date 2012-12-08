#include "Render.h"
#include "LayerTiler.h"

using namespace gameplay;

namespace Awol {

RenderContext::RenderContext()
    :m_terrain(0)
    ,m_units(0)
{
}

void RenderContext::activateTerrain(LayerTiler* layer)
{
    deactivateTerrain();
    m_terrain = layer;
    m_terrain->startBatch();
}

void RenderContext::deactivateTerrain()
{
    if (m_terrain)
        m_terrain->endBatch();

    m_terrain = 0;
}

void RenderContext::activateUnits(LayerTiler* layer)
{
    deactivateUnits();
    m_units = layer;
    m_units->startBatch();
}

void RenderContext::deactivateUnits()
{
    if (m_units)
        m_units->endBatch();

    m_units = 0;
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
    if (!m_terrain || !key)
        return;
    
    Vector3 transformedPoint;
    m_transformation.transformPoint(Vector3(dst.x, dst.y, 1), &transformedPoint);
    m_terrain->drawTile(key, transformedPoint);
}

void RenderContext::paintObject(ObjectKey key, const Vector2& dst)
{
    if (!m_units)
        return;

}

}
