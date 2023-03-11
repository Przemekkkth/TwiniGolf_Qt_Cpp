#include "win_scene.h"
#include "../utils/pixmap_manager.h"
#include "../utils/font_manager.h"
#include "../utils/utils.h"
#include <QTimer>

WinScene::WinScene(QObject *parent)
    : QGraphicsScene(parent), isShow(true)
{
    titleItem = new QGraphicsPixmapItem();
    titleItem->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::Title));
    titleItem->setPos(30, 30);

    infoText = new QGraphicsSimpleTextItem();
    QFont infoFont = FontManager::Instance()->getFont(FontManager::FontID::Main);
    infoFont.setPointSize(32);
    infoFont.setBold(true);
    infoText->setFont(infoFont);
    infoText->setBrush(Qt::white);
    infoText->setText("          Congratulation !!! \n"
                      "You are master of Twini-Golf");
    infoText->setPos(320 - infoText->boundingRect().width()/2.0f,
                     240 - infoText->boundingRect().height()/2.0f);

    resultText = new QGraphicsSimpleTextItem();
    QFont resultFont = FontManager::Instance()->getFont(FontManager::FontID::Main);
    resultFont.setPointSize(24);
    resultFont.setBold(true);
    resultText->setFont(resultFont);
    resultText->setBrush(Qt::white);
    resultText->setText("Result: " + QString("0000").right(5));
    resultText->setPos(320 - resultText->boundingRect().width()/2.0f,
                       350 - resultText->boundingRect().height()/2.0f);

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
    addItem(infoText);
    addItem(resultText);
    addItem(pressAnyKeyText);

    setBackgroundBrush(Qt::black);
    setSceneRect(0,0, SCREEN::PHYSICAL_SIZE.width(), SCREEN::PHYSICAL_SIZE.height());

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &WinScene::updateText);
    timer->start(1000);
}

void WinScene::updateText()
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

void WinScene::keyReleaseEvent(QKeyEvent *event)
{
    emit menuActivated();
    QGraphicsScene::keyPressEvent(event);
}
