#include "LayerTiler.h"
#include "Log.h"

using namespace gameplay;

namespace Awol {

LayerTiler* LayerTiler::create(const std::string& spriteImagePath,
                               const gameplay::Vector2& imageSize,
                               const gameplay::Vector2& tileOrigin,
                               const gameplay::Vector2& tileSize,
                               const gameplay::Vector2& tileStride)
{
    LayerTiler* layer = new LayerTiler;
    layer->m_sprite = SpriteBatch::create(spriteImagePath.c_str());
    layer->m_imageSize = imageSize;
    layer->m_tileOrigin = tileOrigin;
    layer->m_tileSize = tileSize;
    layer->m_tileStride = tileStride;
    return layer;
}

LayerTiler::LayerTiler()
    :m_sprite(0)
{

}

LayerTiler::~LayerTiler()
{
    delete m_sprite;
    m_sprite = 0;
}

const Vector2& LayerTiler::tileSize() const
{
    return m_tileSize;
}

void LayerTiler::startBatch()
{
    m_sprite->start();
}

void LayerTiler::endBatch()
{
    m_sprite->finish();
}

void LayerTiler::drawTile(TerrainKey key, const Vector3& dst)
{
    if (key < ' ')
        return;

    static Rectangle dstRect(0, 0, tileSize().x, tileSize().y); 
    static Rectangle srcRect(0, 0, tileSize().x, tileSize().y);

    dstRect.x = dst.x;
    dstRect.y = dst.y;
    
    int index = key - ' ';
    srcRect.x = index * static_cast<int>(m_tileStride.x) % static_cast<int>(m_imageSize.x) + m_tileOrigin.x;
    srcRect.y = index * static_cast<int>(m_tileStride.y) / static_cast<int>(m_imageSize.x) + m_tileOrigin.y;

    m_sprite->draw(dstRect, srcRect);
}

} // Awol
