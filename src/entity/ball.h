#ifndef BALL_H
#define BALL_H
#include "entity.h"
#include "point.h"
#include "power_bar.h"
#include <QVector>
class Tile;
class Hole;
class Ball : public Entity
{
public:
    Ball(int _index);
    ~Ball();
    QVector2D getVelocity()
    {
        return velocity;
    }
    QVector2D getInitialMousePos()
    {
        return initialMousePos;
    }
    Point* getPoint()
    {
        return point;
    }
    PowerBar* getPowerBar() const
    {
        return powerBar;
    }

    int getStrokes()
    {
        return strokes;
    }
    bool isWin()
    {
        return win;
    }
    void setWin(bool p_win);
    void setInitialMousePos(float x, float y);
    void setVelocity(float x, float y);
    void setLaunchedVelocity(float x, float y);
    void update(float deltaTime, bool mouseDown, bool mousePressed, QVector<Tile *> tiles, QVector<Hole *> holes);
    void setStrokes(int val);
private:
    QVector2D velocity;
    QVector2D target;
    QVector2D launchedVelocity;
    float velocity1D;
    float launchedVelocity1D;
    QVector2D initialMousePos;
    bool canMove = true;
    bool playedSwingFx = true;
    int index;
    int strokes = 0;
    int dirX = 1;
    int dirY = 1;
    bool win = false;
    float friction = 0.001;
    const float speed = 5.0f;
    Point* point;
    PowerBar* powerBar;
};

#endif // BALL_H
