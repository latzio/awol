#include "Render.h"
#include "LayerTiler.h"

using namespace gameplay;

namespace Awol {

RenderContext::RenderContext()
    :m_layer(0)
    ,m_scale(1)
    ,m_runtime(0)
    ,m_elapsed(0)
    ,m_frameId(0)

{
}

void RenderContext::scaleAboutPoint(const IntPoint& focalPoint, float ratio)
{
    // Untransform the focalPoint, scale, and then adjust the scroll so
    // that the retransformed point is in the same place as it was.
    Vector2 untransformed(focalPoint);
    transformFromScreen(untransformed);

    m_scale *= ratio;

    Vector2 retransformed(untransformed);
    transformToScreen(retransformed);

    m_scroll += retransformed - focalPoint;
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

void RenderContext::paintActive(unsigned key, const Rectangle& dstRect)
{
    if (!m_layer || !key)
        return;

    Rectangle translatedRect(dstRect);
    transformToScreen(translatedRect);

    static const Rectangle screenRect(0, 0, 1280, 768);
    if (screenRect.intersects(translatedRect))
        m_layer->drawTile(key, translatedRect);
}

// Transformations Between Screen Pixels and Logical Game Tile Coordinates //

void RenderContext::transformFromScreen(IntPoint& point)
{
    point.setX((point.x() + m_scroll.x) / m_scale);
    point.setY((point.y() + m_scroll.y) / m_scale);
}

void RenderContext::transformFromScreen(Rectangle& rect)
{
    rect.x += m_scroll.x;
    rect.x /= m_scale;

    rect.y += m_scroll.y;
    rect.y /= m_scale;

    rect.width /= m_scale;
    rect.height /= m_scale;
}

void RenderContext::transformFromScreen(Vector2& point)
{
    point.x = (point.x + m_scroll.x) / m_scale;
    point.y = (point.y + m_scroll.y) / m_scale;
}

void RenderContext::transformToScreen(IntPoint& point)
{
    point.setX(point.x() * m_scale - m_scroll.x);
    point.setY(point.y() * m_scale - m_scroll.y);
}

void RenderContext::transformToScreen(Rectangle& rect)
{
    rect.x *= m_scale;
    rect.x -= m_scroll.x;

    rect.y *= m_scale;
    rect.y -= m_scroll.y;

    rect.width *= m_scale;
    rect.height *= m_scale;
}

void RenderContext::transformToScreen(Vector2& point)
{
    point.x = point.x * m_scale - m_scroll.x;
    point.y = point.y * m_scale - m_scroll.y;
}

}
