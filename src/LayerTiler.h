#ifndef LayerTiler_h
#define LayerTiler_h

#include "gameplay.h"

using namespace gameplay;

namespace Awol {

/**
 * Main game class.
 */
class LayerTiler
{
public:

    LayerTiler();

    void initialize();

    void fill(const Rectangle&, const Matrix&);

private:

    SpriteBatch* _sprite;

};

}
#endif
