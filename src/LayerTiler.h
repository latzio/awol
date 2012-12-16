#ifndef LayerTiler_h
#define LayerTiler_h

#include "Primitives.h"
#include "Render.h"

#include "gameplay.h"

namespace Awol {

enum AnimationBehaviour {
    Forward,
    PingPong,
};

class LayerTiler : public gameplay::Ref
{
public:
    static LayerTiler* create(const IntSize& imageSize,
                              const IntPoint& tileOrigin,
                              const IntSize& tileSize,
                              const IntSize& tileStride);

    void setAnimationBehaviour(AnimationBehaviour);
    void setAnimationPeriod(float seconds);

    void addFrameSpritesheet(const std::string& path);

    const IntSize& tileSize() const;

    void start(float gameTime);
    void finish();

    void drawTile(int key, const gameplay::Rectangle&);

private:
    LayerTiler(const IntSize& imageSize,
               const IntPoint& tileOrigin,
               const IntSize& tileSize,
               const IntSize& tileStride);
    virtual ~LayerTiler();

    gameplay::SpriteBatch* spriteForTime(float gameTime);

private:

    AnimationBehaviour m_animationBehaviour;
    float m_animationPeriod;

    std::vector<gameplay::SpriteBatch*> m_sprites;
    gameplay::SpriteBatch* m_activeSprite;

    IntSize m_imageSize;
    IntPoint m_tileOrigin;
    IntSize m_tileSize;
    IntSize m_tileStride;

};

}
#endif
