#include "menu_scene.h"
#include "../utils/utils.h"
#include "../utils/pixmap_manager.h"
#include "../utils/font_manager.h"
#include <QKeyEvent>
#include <QApplication>
#include <QGraphicsPixmapItem>

MenuScene::MenuScene(QObject *parent)
    : QGraphicsScene(parent), currentIndex(0)
{
    title           = new QGraphicsPixmapItem();
    title->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::Title));
    title->setPos(30, 30);

    startButton  = new QGraphicsPixmapItem();
    startButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonSelected));
    startButton->setPos(SCREEN::PHYSICAL_SIZE.width()/2-startButton->boundingRect().width()/2, 200);
    addTextToButton(startButton, "Start");

    levelButton    = new QGraphicsPixmapItem();
    levelButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
    levelButton->setPos(SCREEN::PHYSICAL_SIZE.width()/2-levelButton->boundingRect().width()/2, 275);
    addTextToButton(levelButton, "Level");

    exitButton      = new QGraphicsPixmapItem();
    exitButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
    exitButton->setPos(SCREEN::PHYSICAL_SIZE.width()/2-exitButton->boundingRect().width()/2, 350);
    addTextToButton(exitButton, "Exit");

    addItem(title);
    addItem(startButton);
    addItem(levelButton);

    addItem(exitButton);

    setBackgroundBrush(Qt::black);
    setSceneRect(0,0, SCREEN::PHYSICAL_SIZE.width(), SCREEN::PHYSICAL_SIZE.height());
}

void MenuScene::prepareScene()
{
    //default settings
    currentIndex = 0;
    startButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonSelected));
    levelButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
    exitButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
}

void MenuScene::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
    {
        return;
    }
    if(event->key() == Qt::Key_Up || event->key() == Qt::Key_W)
    {
        getActiveButton()->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
        currentIndex--;
        if(currentIndex < 0)
        {
            currentIndex = 2;
        }
        getActiveButton()->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonSelected));
    }
    else if(event->key() == Qt::Key_Down || event->key() == Qt::Key_S)
    {
        getActiveButton()->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
        currentIndex++;
        if(currentIndex > 2)
        {
            currentIndex = 0;
        }
        getActiveButton()->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonSelected));
    }
    else if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Space)
    {
        if(currentIndex == 0)
        {
            emit gameActivated();
        }
        else if(currentIndex == 1)
        {
            emit levelsActivated();
        }
        else if(currentIndex == 2)
        {
            QApplication::instance()->quit();
        }
    }
    QGraphicsScene::keyReleaseEvent(event);
}

void MenuScene::addTextToButton(QGraphicsPixmapItem *button, QString text)
{
    QGraphicsSimpleTextItem* textItem = new QGraphicsSimpleTextItem(button);
    QFont font = FontManager::Instance()->getFont(FontManager::FontID::Main);
    font.setPointSize(20);
    font.setBold(true);
    textItem->setFont(font);
    textItem->setBrush(Qt::white);
    textItem->setText(text);
    textItem->setPos(button->boundingRect().width()/2-textItem->boundingRect().width()/2,
                     button->boundingRect().height()/2-textItem->boundingRect().height()/2);
}

QGraphicsPixmapItem* MenuScene::getActiveButton()
{
    if(currentIndex == 0)
    {
        return startButton;
    }
    else if(currentIndex == 1)
    {
        return levelButton;
    }
    else
    {
        return exitButton;
    }
}
