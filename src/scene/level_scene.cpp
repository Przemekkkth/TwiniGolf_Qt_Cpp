#include "level_scene.h"
#include "../utils/utils.h"
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsSimpleTextItem>

LevelScene::LevelScene(QObject *parent)
    : QGraphicsScene(parent)
{
    setBackgroundBrush(Qt::black);
    setSceneRect(0,0, SCREEN::PHYSICAL_SIZE.width(), SCREEN::PHYSICAL_SIZE.height());
}

