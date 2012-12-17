#include "AWOL.h"
#include "Battle.h"
#include "Event.h"
#include "Log.h"
#include "Primitives.h"
#include "Render.h"

// Declare our game instance
Awol::AWOL game;

namespace Awol {

AWOL::AWOL()
    :m_battle(0)
    ,m_pendingZoom(1)
{

}

void AWOL::initialize()
{
    BattleTile::setTileSize(IntSize(32, 32));

    BattleMap* map = BattleMap::create(IntSize(100, 40),
                                       "res/background-1-1.png",
                                       "res/level1.dat");
    m_pendingZoom = 1;

    Force* force1 = Force::create(map);
    Force* force2 = Force::create(map);

    m_battle = new Battle(map);
    m_battle->addForce(force1);
    m_battle->addForce(force2);

    map->release();
    force1->release();
    force2->release();
}

void AWOL::finalize()
{
}

void AWOL::update(float elapsedTime)
{
    m_battle->update(elapsedTime);
}

void AWOL::render(float elapsedTime)
{
    static unsigned frameCount = 0;
    frameCount++;

    static unsigned frames = 0;
    static float seconds = 0;
    if (++frames && (seconds += elapsedTime / 1000.) > 5) {
        printf("%d frames rendered in 5 seconds. [%.1f fps]\n", frames, frames / seconds);
        frames = seconds = 0;
    }

    if (getState() == PAUSED)
        return;

    // Clear the color and depth buffers
    clear(CLEAR_COLOR_DEPTH, Vector4(0, 0.25f, 0.1f, 1), 1.0f, 0);

    // Draw your sprites (we will only draw one now
    m_context.setRuntime(getGameTime() / 1000.0);
    m_context.setElapsed(elapsedTime);
    m_context.setFrameId(frameCount);

    m_context.setScroll(m_pendingMove);
    m_context.setScale(m_pendingZoom);

    m_battle->render(m_context, elapsedTime);
}

void AWOL::keyEvent(Keyboard::KeyEvent evt, int key)
{
    if (evt == Keyboard::KEY_PRESS)
    {
        switch (key)
        {
        case Keyboard::KEY_SPACE:
            if (getState() == RUNNING)
                pause();
            else
                resume();
            break;
        case Keyboard::KEY_ESCAPE:
            exit();
            break;
        }
    }
}

bool AWOL::mouseEvent(Mouse::MouseEvent evt, int x, int y, int wheelDelta)
{
    if (wheelDelta > 0) {
        m_pendingZoom = m_pendingZoom * 1.1f;
    } else if (wheelDelta < 0) {
        m_pendingZoom = m_pendingZoom * 0.9f;
    }

    return false;
}

void AWOL::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex)
{
    static IntPoint s_lastTouchPoint;
    IntPoint touchPoint(x, y);

    IntPoint untransformedPoint(touchPoint);
    m_context.transformFromScreen(untransformedPoint);

	Event event(evt == Touch::TOUCH_PRESS ? TouchStart : 
		        evt == Touch::TOUCH_MOVE ? TouchMove : TouchEnd, 
				untransformedPoint,
                contactIndex);

    if (m_battle->handleTouchEvent(event))
        return;

    switch (evt)
    {
    case Touch::TOUCH_PRESS:
        if (!contactIndex)
            s_lastTouchPoint = touchPoint;
        break;
    case Touch::TOUCH_RELEASE:
        break;
    case Touch::TOUCH_MOVE:
        if (!contactIndex) {
            m_pendingMove = m_pendingMove + (s_lastTouchPoint - touchPoint);
            s_lastTouchPoint = touchPoint;
        }
        break;
    };
}

}
