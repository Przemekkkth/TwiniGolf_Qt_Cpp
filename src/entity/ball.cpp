#include "ball.h"
#include "point.h"
#include "power_bar.h"
#include "../utils/pixmap_manager.h"
#include "../utils/utils.h"
#include "hole.h"
#include "tile.h"
#include "../scene/game_scene.h"
#include <vector>
#include <cmath>
#include <iostream>

Ball::Ball(int _index)
{
    setTex(PixmapManager::TextureID::Ball);
    index = _index;
    point = new Point();
    powerBar = new PowerBar();
}

Ball::~Ball()
{
    delete point;
    delete powerBar;
}

void Ball::setVelocity(float x, float y)
{
    velocity.setX(x);
    velocity.setY(y);
}

void Ball::setLaunchedVelocity(float x, float y)
{
    launchedVelocity.setX(x);
    launchedVelocity.setY(y);
}

void Ball::setInitialMousePos(float x, float y)
{
    initialMousePos.setX(x);
    initialMousePos.setY(y);
}

void Ball::setWin(bool p_win)
{
    win = p_win;
}

void Ball::update(float deltaTime, bool mouseDown, bool mousePressed, QVector<Tile*> tiles, QVector<Hole*> holes)
{
    mouseDown    = MouseStatus::mouseDown;
    mousePressed = MouseStatus::mousePressed;
    //constant(speed)
    deltaTime /= 3.0f;
    if (win)
    {
        if (getPos().x() < target.x())
        {
            setPos(getPos().x() + 0.1*speed, getPos().y());
        }
        else if (getPos().x() > target.x())
        {
            setPos(getPos().x() - 0.1*speed, getPos().y());
        }
        if (getPos().y() < target.y())
        {
            setPos(getPos().x(), getPos().y() + 0.1*speed);
        }
        else if (getPos().y() > target.y())
        {
            setPos(getPos().x(), getPos().y() - 0.1*speed);
        }
        setScale(getScale().x() - 0.001*speed, getScale().y() - 0.001*speed);
        if(getScale().x() < 0.001f)
        {
            setScale(-0.001f, getScale().y());
        }
        if(getScale().y() < 0.001f)
        {
            setScale(getScale().x(), -0.001f);
        }

        return;
    }

    for (Hole* h : holes)
    {
        if (getPos().x() + 4 > h->getPos().x() && getPos().x() + 16 < h->getPos().x() + 20 && getPos().y() + 4 > h->getPos().y() && getPos().y() + 16 < h->getPos().y() + 20)
        {
            setWin(true);
            target.setX(h->getPos().x());
            target.setY(h->getPos().y() + 3);
        }
    }

    if (mousePressed && canMove)
    {
        playedSwingFx = false;
        int mouseX = 0;
        int mouseY = 0;
        mouseX = MouseStatus::m_x;
        mouseY = MouseStatus::m_y;
        setInitialMousePos(mouseX, mouseY);
    }
    if (mouseDown && canMove)
    {
        int mouseX = 0;
        int mouseY = 0;
        mouseX = MouseStatus::m_x;
        mouseY = MouseStatus::m_y;
        setVelocity((mouseX - getInitialMousePos().x())/-150, (mouseY - getInitialMousePos().y())/-150);
        setLaunchedVelocity((mouseX - getInitialMousePos().x())/-150, (mouseY - getInitialMousePos().y())/-150);
        velocity1D = std::sqrt(std::pow(std::abs(getVelocity().x()), 2) + std::pow(std::abs(getVelocity().y()), 2));
        launchedVelocity1D = velocity1D;

        int radiusOfBall = 8;
        point->setPos(getPos().x()+radiusOfBall, getPos().y() + radiusOfBall);
        point->setOrigin(getPos().x()+radiusOfBall, getPos().y()+radiusOfBall);
        point->setAngle(std::atan2(velocity.y(), velocity.x())*(RAD_TO_DEGREE) + 90);
        point->setPos(point->getPos().x() - radiusOfBall*cosf(point->getAngle()*(DEGREE_TO_RAD)),
                      point->getPos().y() - radiusOfBall*sinf(point->getAngle()*(DEGREE_TO_RAD)));

        dirX = velocity.x()/std::abs(velocity.x());
        dirY = velocity.y()/std::abs(velocity.y());

        powerBar->setPos(getPos().x() + 32 +  8, getPos().y() - 32);
        if (velocity1D > 1)
        {
            velocity1D = 1;
            launchedVelocity1D = 1;
        }
        powerBar->setFGScale(1, velocity1D/1);
    }
    else
    {
        if (!playedSwingFx)
        {
            playedSwingFx = true;
            strokes++;
        }
        point->setPos(-64, -64);
        powerBar->setPos(-64, -64);

        canMove = false;
        setPos(getPos().x() + getVelocity().x()*deltaTime, getPos().y() + getVelocity().y()*deltaTime);
        if (getVelocity().x() > 0.0001 || getVelocity().x() < -0.0001 || getVelocity().y() > 0.0001 || getVelocity().y() < -0.0001)
        {
            if (velocity1D > 0)
            {
                velocity1D -= friction*deltaTime;
            }
            else
            {
                velocity1D = 0;
            }
            velocity.setX( (velocity1D/launchedVelocity1D)*std::abs(launchedVelocity.x())*dirX );
            velocity.setY( (velocity1D/launchedVelocity1D)*std::abs(launchedVelocity.y())*dirY );


        }
        else
        {
            setVelocity(0,0);
            int mouseX = 0;
            int mouseY = 0;
            mouseX = MouseStatus::m_x;
            mouseY = MouseStatus::m_y;
            setInitialMousePos(mouseX, mouseY);
            canMove = true;
        }

        if (getPos().x() + getCurrentFrame().width() > 640/(2 - index))
        {
            setVelocity(-std::abs(getVelocity().x()), getVelocity().y());
            dirX = -1;
        }
        else if (getPos().x() < 0 + (index*320))
        {
            setVelocity(std::abs(getVelocity().x()), getVelocity().y());
            dirX = 1;
        }
        else if (getPos().y() + getCurrentFrame().height() > 480)
        {
            setVelocity(getVelocity().x(), -std::abs(getVelocity().y()));
            dirY = -1;
        }
        else if (getPos().y() < 0)
        {
            setVelocity(getVelocity().x(), std::abs(getVelocity().y()));
            dirY = 1;
        }

        for (Tile* t : tiles)
        {
            float newX = getPos().x() + getVelocity().x()*deltaTime;
            float newY = getPos().y();
            if (newX + 16 > t->getPos().x() && newX < t->getPos().x() + t->getCurrentFrame().width() && newY + 16 > t->getPos().y() && newY < t->getPos().y() + t->getCurrentFrame().height() - 3)
            {
                setVelocity(getVelocity().x()*-1, getVelocity().y());
                dirX *= -1;
            }

            newX = getPos().x();
            newY = getPos().y() + getVelocity().y()*deltaTime;
            if (newX + 16 > t->getPos().x() && newX < t->getPos().x() + t->getCurrentFrame().width() && newY + 16 > t->getPos().y() && newY < t->getPos().y() + t->getCurrentFrame().height() - 3)
            {
                setVelocity(getVelocity().x(), getVelocity().y()*-1);
                dirY *= -1;
            }
        }
    }

}

void Ball::setStrokes(int val)
{
    strokes = val;
}
