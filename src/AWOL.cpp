#include "AWOL.h"

// Declare our game instance
AWOL game;

AWOL::AWOL()
{
}

void AWOL::initialize()
{
    _layer.initialize();
}

void AWOL::finalize()
{
}

void AWOL::update(float elapsedTime)
{
    Matrix::createTranslation(_pendingMove, &_projection);
}

void AWOL::render(float elapsedTime)
{
    // Clear the color and depth buffers
    clear(CLEAR_COLOR_DEPTH, Vector4::zero(), 1.0f, 0);

    // Draw your sprites (we will only draw one now
    _layer.fill(Rectangle(0, 0, getWidth(), getHeight()), _projection);
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
        _pendingMove.add(touchPoint - s_lastTouchPoint);
        s_lastTouchPoint = touchPoint;
        break;
    };
}
