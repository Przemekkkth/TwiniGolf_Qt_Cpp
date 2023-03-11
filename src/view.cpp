#include "view.h"

View::View()
    : mGameScene(new GameScene(this)),
      mLevelScene(new LevelScene(this)),
      mMenuScene(new MenuScene(this)),
      mTitleScene(new TitleScene(this)),
      mWinScene(new WinScene(this))
{
    setScene(mGameScene);
    resize(mGameScene->sceneRect().width()+2, mGameScene->sceneRect().height()+2);

    connect(mTitleScene, &TitleScene::menuActivated, [this](){
        this->mTitleScene->stopTimer();
        this->setScene(mMenuScene);
    });
    connect(mMenuScene, &MenuScene::levelsActivated, [this](){
        mLevelScene->prepareScene();
        this->setScene(mLevelScene);
    });
    connect(mLevelScene, &LevelScene::menuActivated, [this](){
        mMenuScene->prepareScene();
        this->setScene(mMenuScene);
    });

    connect(mWinScene, &WinScene::menuActivated, [this](){
        mMenuScene->prepareScene();
        this->setScene(mMenuScene);
    });

    //setMouseTracking(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
