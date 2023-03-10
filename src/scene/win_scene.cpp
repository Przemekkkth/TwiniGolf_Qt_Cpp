#include "win_scene.h"
#include "../utils/utils.h"

WinScene::WinScene(QObject *parent)
    : QGraphicsScene(parent)
{
    setBackgroundBrush(Qt::black);
    setSceneRect(0,0, SCREEN::PHYSICAL_SIZE.width(), SCREEN::PHYSICAL_SIZE.height());
}
