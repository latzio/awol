#include "AWOL.h"
#include "Battle.h"
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
    BattleMap* map = BattleMap::create(Vector2(100, 40),
                                       "res/background-tiles.png",
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

    m_battle->update(elapsedTime);
}

void AWOL::render(float elapsedTime)
{
    // Clear the color and depth buffers
    clear(CLEAR_COLOR_DEPTH, Vector4::zero(), 1.0f, 0);

    // Draw your sprites (we will only draw one now
    RenderContext context;
    context.setTransform(m_projection);

    m_battle->render(context, elapsedTime);
}

void AWOL::keyEvent(Keyboard::KeyEvent evt, int key)
{
    if (evt == Keyboard::KEY_PRESS)
    {
        switch (key)
        {
        case Keyboard::KEY_ESCAPE:
            exit();
            break;
        }
    }
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
