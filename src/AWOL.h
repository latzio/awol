#ifndef TEMPLATEGAME_H_
#define TEMPLATEGAME_H_

#include "LayerTiler.h"
#include "Render.h"

#include "gameplay.h"

using namespace gameplay;

namespace Awol {

class Battle;

/**
 * Main game class.
 */
class AWOL: public Game
{
public:

    /**
     * Constructor.
     */
    AWOL();

    /**
     * @see Game::keyEvent
     */
	void keyEvent(Keyboard::KeyEvent evt, int key);
	
    /**
     * @see Game::touchEvent
     */
    void touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);
    bool mouseEvent(Mouse::MouseEvent evt, int x, int y, int wheelDelta);

protected:

    /**
     * @see Game::initialize
     */
    void initialize();

    /**
     * @see Game::finalize
     */
    void finalize();

    /**
     * @see Game::update
     */
    void update(float elapsedTime);

    /**
     * @see Game::render
     */
    void render(float elapsedTime);

private:

    RenderContext m_context;

    IntSize m_pendingMove;
    float m_pendingZoom;

    Battle* m_battle;
};

} // Awol

#endif
