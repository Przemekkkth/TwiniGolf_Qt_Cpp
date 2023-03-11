#include "level_scene.h"
#include "../utils/utils.h"
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsSimpleTextItem>
#include "../utils/pixmap_manager.h"
#include "../utils/font_manager.h"
#include <QKeyEvent>

LevelScene::LevelScene(QObject *parent)
    : QGraphicsScene(parent), currentIndex(0)
{

    title           = new QGraphicsPixmapItem();
    title->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::Title));
    title->setPos(30, 30);

    zeroButton = new QGraphicsPixmapItem();
    zeroButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonSelected));
    zeroButton->setPos(13, 200);
    addTextToButton(zeroButton, "0");

    oneButton = new QGraphicsPixmapItem();
    oneButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
    oneButton->setPos(226, 200);
    addTextToButton(oneButton, "1");

    twoButton = new QGraphicsPixmapItem();
    twoButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
    twoButton->setPos(439, 200);
    addTextToButton(twoButton, "2");

    threeButton = new QGraphicsPixmapItem();
    threeButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
    threeButton->setPos(13, 275);
    addTextToButton(threeButton, "3");

    fourButton = new QGraphicsPixmapItem();
    fourButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
    fourButton->setPos(226, 275);
    addTextToButton(fourButton, "4");

    fiveButton = new QGraphicsPixmapItem();
    fiveButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
    fiveButton->setPos(439, 275);
    addTextToButton(fiveButton, "5");

    sixButton = new QGraphicsPixmapItem();
    sixButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
    sixButton->setPos(13, 350);
    addTextToButton(sixButton, "6");

    sevenButton = new QGraphicsPixmapItem();
    sevenButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
    sevenButton->setPos(226, 350);
    addTextToButton(sevenButton, "7");

    eightButton = new QGraphicsPixmapItem();
    eightButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
    eightButton->setPos(439, 350);
    addTextToButton(eightButton, "8");

    menuButton = new QGraphicsPixmapItem();
    menuButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
    menuButton->setPos(439, 425);
    addTextToButton(menuButton, "Menu");

    addItem(title);
    addItem(zeroButton);
    addItem(oneButton);
    addItem(twoButton);
    addItem(threeButton);
    addItem(fourButton);
    addItem(fiveButton);
    addItem(sixButton);
    addItem(sevenButton);
    addItem(eightButton);
    addItem(menuButton);

    setBackgroundBrush(Qt::black);
    setSceneRect(0,0, SCREEN::PHYSICAL_SIZE.width(), SCREEN::PHYSICAL_SIZE.height());
}

void LevelScene::prepareScene()
{
    //default settings
    currentIndex = 0;
    zeroButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonSelected));
    oneButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
    twoButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
    threeButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
    fourButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
    fiveButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
    sixButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
    sevenButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
    eightButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
    menuButton->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
}

QGraphicsPixmapItem *LevelScene::getActiveButton()
{
    if(currentIndex == 0)
    {
        return zeroButton;
    }
    else if(currentIndex == 1)
    {
        return oneButton;
    }
    else if(currentIndex == 2)
    {
        return twoButton;
    }
    else if(currentIndex == 3)
    {
        return threeButton;
    }
    else if(currentIndex == 4)
    {
        return fourButton;
    }
    else if(currentIndex == 5)
    {
        return fiveButton;
    }
    else if(currentIndex == 6)
    {
        return sixButton;
    }
    else if(currentIndex == 7)
    {
        return sevenButton;
    }
    else if(currentIndex == 8)
    {
        return eightButton;
    }
    else
    {
        return menuButton;
    }
}

void LevelScene::addTextToButton(QGraphicsPixmapItem *button, QString text)
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

void LevelScene::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
    {
        return;
    }
    if(event->key() == Qt::Key_Up || event->key() == Qt::Key_W)
    {
        getActiveButton()->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
        currentIndex--;
        if(currentIndex < 0)        {
            currentIndex = 9;
        }
        getActiveButton()->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonSelected));
    }
    else if(event->key() == Qt::Key_Down || event->key() == Qt::Key_S)
    {
        getActiveButton()->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonUnselected));
        currentIndex++;
        if(currentIndex > 9)
        {
            currentIndex = 0;
        }
        getActiveButton()->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::ButtonSelected));
    }
    else if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Space)
    {
        if(currentIndex >= 0
                &&
                currentIndex < 9)
        {
            emit gameActivated(currentIndex);
        }
        else
        {
            emit menuActivated();
        }
    }
    QGraphicsScene::keyReleaseEvent(event);
}
