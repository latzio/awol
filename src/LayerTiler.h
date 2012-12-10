#ifndef LayerTiler_h
#define LayerTiler_h

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
    static LayerTiler* create(const gameplay::Vector2& imageSize,
                              const gameplay::Vector2& tileOrigin,
                              const gameplay::Vector2& tileSize,
                              const gameplay::Vector2& tileStride);

    void setAnimationBehaviour(AnimationBehaviour);
    void setAnimationPeriod(float seconds);

    void addFrameSpritesheet(const std::string& path);

    const gameplay::Vector2& tileSize() const;

    void start(float gameTime);
    void finish();

    void drawTile(int key, const gameplay::Rectangle&);

private:
    LayerTiler(const gameplay::Vector2& imageSize,
               const gameplay::Vector2& tileOrigin,
               const gameplay::Vector2& tileSize,
               const gameplay::Vector2& tileStride);
    virtual ~LayerTiler();

    gameplay::SpriteBatch* spriteForTime(float gameTime);

private:

    AnimationBehaviour m_animationBehaviour;
    float m_animationPeriod;

    std::vector<gameplay::SpriteBatch*> m_sprites;
    gameplay::SpriteBatch* m_activeSprite;

    gameplay::Vector2 m_imageSize;
    gameplay::Vector2 m_tileOrigin;
    gameplay::Vector2 m_tileSize;
    gameplay::Vector2 m_tileStride;

};

}
#endif
