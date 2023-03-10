#include "title_scene.h"
#include "../utils/utils.h"
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "../utils/pixmap_manager.h"
#include "../utils/font_manager.h"

TitleScene::TitleScene(QObject *parent)
    : QGraphicsScene(parent), isShow(true)
{
    titleItem = new QGraphicsPixmapItem();
    titleItem->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::Title));
    titleItem->setPos(30, 30);

    qtLogo    = new QGraphicsPixmapItem();
    qtLogo->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::QtLogo));
    qtLogo->setPos(230, 200);

    pressAnyKeyText = new QGraphicsSimpleTextItem();
    QFont font = FontManager::Instance()->getFont(FontManager::FontID::Main);
    font.setPointSize(20);
    font.setBold(true);
    pressAnyKeyText->setFont(font);
    pressAnyKeyText->setBrush(Qt::white);
    pressAnyKeyText->setText("Press any key to start");
    pressAnyKeyText->setPos(SCREEN::PHYSICAL_SIZE.width()/2-pressAnyKeyText->boundingRect().width()/2,
                            420);


    addItem(titleItem);
    addItem(qtLogo);
    addItem(pressAnyKeyText);

    setBackgroundBrush(Qt::black);
    setSceneRect(0,0, SCREEN::PHYSICAL_SIZE.width(), SCREEN::PHYSICAL_SIZE.height());

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TitleScene::updateText);
    timer->start(1000);
}

void TitleScene::updateText()
{
    isShow = !isShow;
    if(isShow)
    {
        pressAnyKeyText->show();
    }
    else
    {
        pressAnyKeyText->hide();
    }
}

void TitleScene::keyPressEvent(QKeyEvent *event)
{
    emit menuActivated();
    QGraphicsScene::keyPressEvent(event);
}
