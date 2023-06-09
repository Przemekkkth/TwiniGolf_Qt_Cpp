#include "game_scene.h"
#include "../utils/utils.h"
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

float MouseStatus::m_x = 0.0f;
float MouseStatus::m_y = 0.0f;
bool MouseStatus::m_pressed = false;
bool MouseStatus::m_released = false;
bool MouseStatus::mouseDown = false;
bool MouseStatus::mousePressed = false;

int GameScene::result = 0;

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent)
{
    mWorld = new World();

    setBackgroundBrush(Qt::white);
    for(int i = 0; i < 256; ++i)
    {
        m_keys[i] = new KeyStatus();
    }
    m_mouse = new MouseStatus();
    setSceneRect(0,0, SCREEN::PHYSICAL_SIZE.width(), SCREEN::PHYSICAL_SIZE.height());
    connect(&m_timer, &QTimer::timeout, this, &GameScene::loop);
    m_timer.start(int(1000.0f/FPS));
    m_elapsedTimer.start();
}

GameScene::~GameScene()
{
    delete mWorld;
}

void GameScene::startGame(int level)
{
    m_timer.start(int(1000.0f/FPS));
    m_elapsedTimer.start();
    result = 0;
    mWorld->initWorld(level);
}

void GameScene::stopGame()
{
    m_timer.stop();
}

void GameScene::resetStatus()
{
    for(int i = 0; i < 256; ++i)
    {
        m_keys[i]->m_released = false;
    }
    for(int i = 0; i < 256; ++i)
    {
        m_keys[i]->m_pressed = false;
    }
    m_mouse->m_released = false;
    MouseStatus::m_pressed = false;
}

void GameScene::loop()
{
    m_deltaTime = m_elapsedTimer.elapsed();
    m_elapsedTimer.restart();

    m_loopTime += m_deltaTime;
    while( m_loopTime > m_loopSpeed)
    {
        m_loopTime -= m_loopSpeed;
        handlePlayerInput();
        updateScene(m_loopSpeed);
        draw();

        resetStatus();
    }
}

void GameScene::handlePlayerInput()
{
    if(m_keys[KEYBOARD::KEY_BACKSPACE]->m_released)
    {
        stopGame();
        emit menuActivated();
    }
}

void GameScene::updateScene(float elapsedTime)
{
    mWorld->update(elapsedTime);
    if(mWorld->isWinActivated())
    {
        GameScene::result = mWorld->getResult();
        stopGame();
        emit winActivated();

    }
}

void GameScene::draw()
{
    clear();
    mWorld->draw(*this);
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    if(KEYBOARD::KeysMapper.contains(event->key()))
    {
        if(event->isAutoRepeat())
        {
            m_keys[KEYBOARD::KeysMapper[event->key()]]->m_held = true;
            m_keys[KEYBOARD::KeysMapper[event->key()]]->m_pressed = false;
        }
        else
        {
            m_keys[KEYBOARD::KeysMapper[event->key()]]->m_pressed = true;
            m_keys[KEYBOARD::KeysMapper[event->key()]]->m_held    = false;
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    if(KEYBOARD::KeysMapper.contains(event->key()))
    {
        if(!event->isAutoRepeat())
        {
            m_keys[KEYBOARD::KeysMapper[event->key()]]->m_held = false;
            m_keys[KEYBOARD::KeysMapper[event->key()]]->m_pressed = false;
            m_keys[KEYBOARD::KeysMapper[event->key()]]->m_released = true;
        }

    }
    QGraphicsScene::keyReleaseEvent(event);
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_mouse->m_x = event->scenePos().x();
    m_mouse->m_y = event->scenePos().y();
    m_mouse->m_pressed = true;

    if(event->button() == Qt::MouseButton::LeftButton)
    {
        MouseStatus::mouseDown = true;
        MouseStatus::mousePressed = true;
    }
    QGraphicsScene::mousePressEvent(event);
}

void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    m_mouse->m_x = event->scenePos().x();
    m_mouse->m_y = event->scenePos().y();
    QGraphicsScene::mouseMoveEvent(event);
}

void GameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_mouse->m_x = event->scenePos().x();
    m_mouse->m_y = event->scenePos().y();
    m_mouse->m_pressed = false;
    m_mouse->m_released = true;
    if(event->button() == Qt::MouseButton::LeftButton)
    {
        MouseStatus::mouseDown = false;
        MouseStatus::mousePressed = false;
    }

    QGraphicsScene::mouseReleaseEvent(event);
}
