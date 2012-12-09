#ifndef LayerTiler_h
#define LayerTiler_h

#include "Render.h"

#include "gameplay.h"

namespace Awol {

class LayerTiler : public gameplay::Ref
{
public:
    static LayerTiler* create(const std::string& spriteImagePath,
                              const gameplay::Vector2& imageSize,
                              const gameplay::Vector2& tileOrigin,
                              const gameplay::Vector2& tileSize,
                              const gameplay::Vector2& tileStride);

    const gameplay::Vector2& tileSize() const;

    void start(unsigned frame);
    void finish();
    void drawTile(TerrainKey, const gameplay::Vector3&);

private:
    LayerTiler(const std::string& spriteImagePath,
               const gameplay::Vector2& imageSize,
               const gameplay::Vector2& tileOrigin,
               const gameplay::Vector2& tileSize,
               const gameplay::Vector2& tileStride);
    virtual ~LayerTiler();

    std::vector<gameplay::SpriteBatch*> m_sprites;
    gameplay::SpriteBatch* m_activeSprite;

    gameplay::Vector2 m_imageSize;
    gameplay::Vector2 m_tileOrigin;
    gameplay::Vector2 m_tileSize;
    gameplay::Vector2 m_tileStride;

};

}
#endif
