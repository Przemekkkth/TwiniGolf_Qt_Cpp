#include "view.h"

View::View()
    : mGameScene(new GameScene(this)),
      mLevelScene(new LevelScene(this)),
      mMenuScene(new MenuScene(this)),
      mTitleScene(new TitleScene(this)),
      mWinScene(new WinScene(this))
{
    setScene(mTitleScene);
    resize(mGameScene->sceneRect().width()+2, mGameScene->sceneRect().height()+2);

    //setMouseTracking(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
