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
    LayerTiler* layer = new LayerTiler(spriteImagePath, imageSize, tileOrigin, tileSize, tileStride);
    return layer;
}

LayerTiler::LayerTiler(const std::string& spriteImagePath,
                      const gameplay::Vector2& imageSize,
                      const gameplay::Vector2& tileOrigin,
                      const gameplay::Vector2& tileSize,
                      const gameplay::Vector2& tileStride)
    :m_imageSize(imageSize)
    ,m_tileOrigin(tileOrigin)
    ,m_tileSize(tileSize)
    ,m_tileStride(tileStride)
    ,m_activeSprite(0)
{
    m_sprites.push_back(SpriteBatch::create(spriteImagePath.c_str()));
    m_sprites.push_back(SpriteBatch::create("res/background-1-2.png"));
    m_sprites.push_back(SpriteBatch::create("res/background-1-3.png"));
}

LayerTiler::~LayerTiler()
{
    std::vector<SpriteBatch*>::iterator it = m_sprites.begin();
    std::vector<SpriteBatch*>::iterator last = m_sprites.end();
    for (; it != last; it++)
        delete *it;
}

const Vector2& LayerTiler::tileSize() const
{
    return m_tileSize;
}

void LayerTiler::start(unsigned frame)
{
    if (!m_sprites.size())
        return;

    int throttledFrame = frame % 60 / 15;

    m_activeSprite = m_sprites[throttledFrame % m_sprites.size()];
    m_activeSprite->start();
}

void LayerTiler::finish()
{
    m_activeSprite->finish();
    m_activeSprite = 0;
}

void LayerTiler::drawTile(TerrainKey key, const Vector3& dst)
{
    if (key < ' ' || !m_activeSprite)
        return;

    static Rectangle dstRect(0, 0, tileSize().x, tileSize().y); 
    static Rectangle srcRect(0, 0, tileSize().x, tileSize().y);

    dstRect.x = dst.x;
    dstRect.y = dst.y;
    
    int index = key - ' ';
    srcRect.x = index * static_cast<int>(m_tileStride.x) % static_cast<int>(m_imageSize.x - m_tileOrigin.x) + m_tileOrigin.x;
    srcRect.y = index / static_cast<int>(m_imageSize.x / m_tileSize.x) * m_tileStride.y + m_tileOrigin.y;

    m_activeSprite->draw(dstRect, srcRect);
}

} // Awol
