#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <QGraphicsScene>
#include <QTimer>
#include <QElapsedTimer>
#include "../world.h"

struct KeyStatus
{
    bool m_pressed = false;
    bool m_held = false;
    bool m_released = false;
};

struct MouseStatus
{
    static float m_x;
    static float m_y;
    static bool m_released;
    static bool m_pressed;
    static bool mouseDown;
    static bool mousePressed;
};


class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene(QObject* parent = nullptr);
    ~GameScene();
    void startGame(int level);
    void stopGame();
private slots:
    void loop();
private:
    void updateScene(float elapsedTime);
    void draw();

    World *mWorld;

    void resetStatus();
    KeyStatus* m_keys[256];
    MouseStatus* m_mouse;

    const int FPS = 60;
    QTimer m_timer;
    QElapsedTimer m_elapsedTimer;
    float m_deltaTime = 0.0f, m_loopTime = 0.0f;
    const float m_loopSpeed = int(1000.0f/FPS);

    // QGraphicsScene interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // GAMESCENE_H
