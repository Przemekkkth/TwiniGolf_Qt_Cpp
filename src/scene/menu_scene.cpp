#include "menu_scene.h"
#include "../utils/utils.h"

MenuScene::MenuScene(QObject *parent)
    : QGraphicsScene(parent)
{
    setBackgroundBrush(Qt::black);
    setSceneRect(0,0, SCREEN::PHYSICAL_SIZE.width(), SCREEN::PHYSICAL_SIZE.height());
}
