#include "Render.h"
#include "LayerTiler.h"

using namespace gameplay;

namespace Awol {

RenderContext::RenderContext()
    :m_layer(0)
    ,m_runtime(0)
    ,m_elapsed(0)
    ,m_frameId(0)
{
}

void RenderContext::activateLayer(LayerTiler* layer)
{
    deactivateLayer();
    m_layer = layer;
    m_layer->start(m_runtime);
}

void RenderContext::deactivateLayer()
{
    if (m_layer)
        m_layer->finish();

    m_layer = 0;
}

void RenderContext::paintLayer(unsigned key, const Vector2& dst)
{
    if (!m_layer || !key)
        return;

    Vector2 layerCoords = m_layer->tileSize();
    layerCoords.scale(dst);

    Vector3 transformedPoint;
    Vector3 transformedSize(1, 1, 1);

    m_transformation.transformPoint(Vector3(layerCoords.x, layerCoords.y, 1), &transformedPoint);
    m_transformation.transformVector(&transformedSize);

    Rectangle dstRect(transformedPoint.x,
                      transformedPoint.y,
                      m_layer->tileSize().x * transformedSize.x,
                      m_layer->tileSize().y * transformedSize.y);

    m_layer->drawTile(key, dstRect);
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

}
