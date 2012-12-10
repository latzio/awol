#include "Render.h"
#include "LayerTiler.h"

using namespace gameplay;

namespace Awol {

RenderContext::RenderContext()
    :m_terrain(0)
    ,m_units(0)
    ,m_runtime(0)
    ,m_elapsed(0)
    ,m_frameId(0)
{
}

void RenderContext::activateTerrain(LayerTiler* layer)
{
    deactivateTerrain();
    m_terrain = layer;
    m_terrain->start(m_runtime);
}

void RenderContext::deactivateTerrain()
{
    if (m_terrain)
        m_terrain->finish();

    m_terrain = 0;
}

void RenderContext::activateUnits(LayerTiler* layer)
{
    deactivateUnits();
    m_units = layer;
    m_units->start(m_runtime);
}

void RenderContext::deactivateUnits()
{
    if (m_units)
        m_units->finish();

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
    Vector3 transformedSize(1, 1, 1);

    m_transformation.transformPoint(Vector3(dst.x, dst.y, 1), &transformedPoint);
    m_transformation.transformVector(&transformedSize);

    Rectangle dstRect(transformedPoint.x, 
                      transformedPoint.y, 
                      m_terrain->tileSize().x * transformedSize.x,
                      m_terrain->tileSize().y * transformedSize.y);

    m_terrain->drawTile(key, dstRect);
}

void RenderContext::paintObject(ObjectKey key, const Vector2& dst)
{
    if (!m_units)
        return;

    Vector3 transformedPoint;
    Vector3 transformedSize(1, 1, 1);

    m_transformation.transformPoint(Vector3(dst.x, dst.y, 1), &transformedPoint);
    m_transformation.transformVector(&transformedSize);

    Rectangle dstRect(transformedPoint.x, 
                      transformedPoint.y, 
                      m_units->tileSize().x * transformedSize.x,
                      m_units->tileSize().y * transformedSize.y);


    m_units->drawTile(key, dstRect);
}

}
