#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include "scene/game_scene.h"
#include "scene/level_scene.h"
#include "scene/menu_scene.h"
#include "scene/title_scene.h"
#include "scene/win_scene.h"

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View();
signals:

private:
    GameScene* mGameScene;
    LevelScene* mLevelScene;
    MenuScene* mMenuScene;
    TitleScene* mTitleScene;
    WinScene* mWinScene;

    // QWidget interface
protected:
    virtual void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // VIEW_H
