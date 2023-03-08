#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include "scene/game_scene.h"

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View();

signals:

private:
    GameScene* mGameScene;
};

#endif // VIEW_H
