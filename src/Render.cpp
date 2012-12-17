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

void RenderContext::transformToScreen(IntPoint& point)
{
    point = point + m_scroll;
}

void RenderContext::transformToScreen(Rectangle& rect)
{
    rect.x *= m_scale;
    rect.x -= m_scroll.dx();

    rect.y *= m_scale;
    rect.y -= m_scroll.dy();

    rect.width *= m_scale;
    rect.height *= m_scale;
}

void RenderContext::transformPointToScreen(Vector2& point)
{
    point.add(m_scroll);
}

void RenderContext::transformSizeToScreen(Vector2& size)
{
    size.scale(m_scale);
}

void RenderContext::transformFromScreen(IntPoint& point)
{
    point.setX((point.x() + m_scroll.dx()) / m_scale);
    point.setY((point.y() + m_scroll.dy()) / m_scale);
}

}
