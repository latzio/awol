#include "LayerTiler.h"

LayerTiler::LayerTiler()
    :_sprite(0)
{

}

void LayerTiler::initialize()
{
    _sprite = SpriteBatch::create("res/background-tiles.png");
}

void LayerTiler::fill(const Rectangle& rect, const Matrix& transformation)
{
    Vector3 origin;
    transformation.transformPoint(&origin);

    Vector2 dst;
    Vector2 offset;
    Vector3 size(16, 16, 1);
    transformation.transformVector(&size);

    printf("Size: %.1f, %.1f\n", size.x, size.y);


    _sprite->start();
    for (offset.x = rect.left(); offset.x < rect.right(); offset.x = offset.x + size.x) {
        for (offset.y = rect.top(); offset.y < rect.bottom(); offset.y = offset.y + size.y) {
            dst = Vector2(origin.x + offset.x, origin.y + offset.y);
            _sprite->draw(Rectangle(dst.x, dst.y, size.x, size.y), Rectangle(2, 2, 16, 16));
        }
    }
    _sprite->finish();
}
