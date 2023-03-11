#include "view.h"
#include "utils/utils.h"

View::View()
    : mGameScene(new GameScene(this)),
      mLevelScene(new LevelScene(this)),
      mMenuScene(new MenuScene(this)),
      mTitleScene(new TitleScene(this)),
      mWinScene(new WinScene(this))
{
    setScene(mTitleScene);
    resize(SCREEN::PHYSICAL_SIZE.width()+2, SCREEN::PHYSICAL_SIZE.height()+2);

    connect(mTitleScene, &TitleScene::menuActivated, [this](){
        this->mTitleScene->stopTimer();
        this->setScene(mMenuScene);
    });

    connect(mMenuScene, &MenuScene::levelsActivated, [this](){
        mLevelScene->prepareScene();
        this->setScene(mLevelScene);
    });
    connect(mMenuScene, &MenuScene::gameActivated, [this](){
        mGameScene->startGame(0);
        this->setScene(mGameScene);
    });

    connect(mGameScene, &GameScene::winActivated, [this](){
        mWinScene->setResultText();
        setScene(mWinScene);
    });

    connect(mLevelScene, &LevelScene::menuActivated, [this](){
        mMenuScene->prepareScene();
        this->setScene(mMenuScene);
    });

    connect(mLevelScene, &LevelScene::gameActivated, [this](int level){
        mGameScene->startGame(level);
        this->setScene(mGameScene);
    });

    connect(mGameScene, &GameScene::menuActivated, [this](){
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
