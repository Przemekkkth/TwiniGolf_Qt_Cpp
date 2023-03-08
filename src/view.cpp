#include "view.h"

View::View()
    : mGameScene(new GameScene(this))
{
    setScene(mGameScene);
    resize(mGameScene->sceneRect().width()+2, mGameScene->sceneRect().height()+2);

    //setMouseTracking(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
