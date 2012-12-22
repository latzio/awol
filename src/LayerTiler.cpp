#include "LayerTiler.h"
#include "Log.h"

using namespace gameplay;

namespace Awol {

LayerTiler* LayerTiler::create(const IntSize& imageSize,
                               const IntPoint& tileOrigin,
                               const IntSize& tileSize,
                               const IntSize& tileStride)
{
    LayerTiler* layer = new LayerTiler(imageSize, tileOrigin, tileSize, tileStride);
    return layer;
}

LayerTiler::LayerTiler(const IntSize& imageSize,
                       const IntPoint& tileOrigin,
                       const IntSize& tileSize,
                       const IntSize& tileStride)
    :m_animationBehaviour(Forward)
    ,m_animationPeriod(0)
    ,m_imageSize(imageSize)
    ,m_tileOrigin(tileOrigin)
    ,m_tileSize(tileSize)
    ,m_tileStride(tileStride)
    ,m_activeSprite(0)
{
}

LayerTiler::~LayerTiler()
{
    std::vector<SpriteBatch*>::iterator it = m_sprites.begin();
    std::vector<SpriteBatch*>::iterator last = m_sprites.end();
    for (; it != last; it++)
        delete *it;
}

void LayerTiler::setAnimationBehaviour(AnimationBehaviour behaviour)
{
    m_animationBehaviour = behaviour;
}

void LayerTiler::setAnimationPeriod(float seconds)
{
    m_animationPeriod = seconds;
}

void LayerTiler::addFrameSpritesheet(const std::string& path)
{
    m_sprites.push_back(SpriteBatch::create(path.c_str()));
}

const IntSize& LayerTiler::tileSize() const
{
    return m_tileSize;
}

void LayerTiler::start(float gameTime)
{
    finish();

    m_activeSprite = spriteForTime(gameTime);

    if (m_activeSprite)
        m_activeSprite->start();
}

void LayerTiler::finish()
{
    if (m_activeSprite)
        m_activeSprite->finish();

    m_activeSprite = 0;
}

void LayerTiler::drawTile(int key, const Rectangle& dstRect)
{
    if (key < ' ' || !m_activeSprite)
        return;

    static Rectangle srcRect(0, 0, tileSize().dx() - 2, tileSize().dy() - 2);

    int index = key - ' ';
    srcRect.x = 1 + index * static_cast<int>(m_tileStride.dx()) % static_cast<int>(m_imageSize.dx() - m_tileOrigin.x()) + m_tileOrigin.x();
    srcRect.y = 1 + index / static_cast<int>(m_imageSize.dx() / m_tileSize.dx()) * m_tileStride.dy() + m_tileOrigin.y();

    m_activeSprite->draw(dstRect, srcRect);
}

SpriteBatch* LayerTiler::spriteForTime(float gameTime)
{
    unsigned spriteSize = m_sprites.size();
    if (!spriteSize)
        return 0;

    if (!m_animationPeriod || spriteSize == 1)
        return m_sprites[0];

    // Need to find at what percentage of our period we are at.
    // PingPong animations actually have 2n-2 frames, not just n.
    float percentage = gameTime / m_animationPeriod - floor(gameTime / m_animationPeriod);
    unsigned index = percentage * (m_animationBehaviour == Forward ? spriteSize : spriteSize * 2 - 2);

    if (index >= spriteSize)
        index = spriteSize - (index - spriteSize) - 2;

    return m_sprites[index];
}

} // Awol
