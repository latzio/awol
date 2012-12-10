#include "AWOL.h"
#include "Battle.h"
#include "Log.h"
#include "Render.h"


#include "level1.h"


// Declare our game instance
Awol::AWOL game;

namespace Awol {

AWOL::AWOL()
{

}

void AWOL::initialize()
{
    m_pendingZoom = Vector3::one();

    BattleMap* map = BattleMap::create(Vector2(100, 40),
                                       "res/background-1-1.png",
                                       level1Terrain);
    
    
    Force* force1 = new Force();
    Force* force2 = new Force();
    Forces forces;
    forces.push_back(force1);
    forces.push_back(force2);
    
    m_battle = new Battle(map, forces);

    map->release();
    force1->release();
    force2->release();
}

void AWOL::finalize()
{
}

void AWOL::update(float elapsedTime)
{
    Matrix::createTranslation(m_pendingMove, &m_projection);
    m_projection.scale(m_pendingZoom.x, m_pendingZoom.y, 1);

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
    

    // Clear the color and depth buffers
    clear(CLEAR_COLOR_DEPTH, Vector4::zero(), 1.0f, 0);

    // Draw your sprites (we will only draw one now
    RenderContext context;
    context.setRuntime(getGameTime() / 1000.0);
    context.setElapsed(elapsedTime);
    context.setFrameId(frameCount);
    context.setTransform(m_projection);

    m_battle->render(context, elapsedTime);
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
        m_pendingZoom.scale(1.1);
    } else if (wheelDelta < 0) {
        m_pendingZoom.scale(0.9);
    }

    return false;
}

void AWOL::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex)
{
    static Vector3 s_lastTouchPoint;
    Vector3 touchPoint(x, y, 0);

    switch (evt)
    {
    case Touch::TOUCH_PRESS:
        s_lastTouchPoint = touchPoint;
        break;
    case Touch::TOUCH_RELEASE:
        break;
    case Touch::TOUCH_MOVE:
        m_pendingMove.add(touchPoint - s_lastTouchPoint);
        s_lastTouchPoint = touchPoint;
        break;
    };
}

}
