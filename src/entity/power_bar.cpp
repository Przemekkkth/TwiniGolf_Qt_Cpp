#include "power_bar.h"
#include <QGraphicsPixmapItem>
#include "../scene/game_scene.h"

PowerBar::PowerBar()
{
    //BG
    setTex(PixmapManager::TextureID::Powermeter_BG);
    //FG
    foregroundTex = PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::Powermeter_FG);
    //Overlay
    overlayTex = PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::Powermeter_Overlay);
}

void PowerBar::setFGScale(float x, float y)
{
    fgScale.setX(x);
    fgScale.setY(y);
}

QVector2D PowerBar::getFGScale() const
{
    return fgScale;
}

void PowerBar::draw(GameScene &target) const
{
    QGraphicsPixmapItem* bgItem = new QGraphicsPixmapItem();
    bgItem->setPixmap(tex);
    bgItem->setTransformOriginPoint(getOrigin().x(), getOrigin().y());
    QTransform bgTransform;
    bgTransform.translate(getPos().x(), getPos().y());
    bgTransform.scale(getScale().x(), getScale().y());
    bgTransform.rotate(getAngle());
    bgItem->setTransform(bgTransform);
    target.addItem(bgItem);

    QGraphicsPixmapItem* overlayItem = new QGraphicsPixmapItem();
    overlayItem->setPixmap(overlayTex);
    overlayItem->setTransformOriginPoint(getOrigin().x(), getOrigin().y());
    QTransform overlayTransform;
    overlayTransform.translate(getPos().x(), getPos().y());
    overlayTransform.scale(getScale().x(), getScale().y());
    overlayTransform.rotate(getAngle());
    overlayItem->setTransform(overlayTransform);
    target.addItem(overlayItem);

    QGraphicsPixmapItem* fgItem = new QGraphicsPixmapItem();
    fgItem->setPixmap(foregroundTex);
    fgItem->setTransformOriginPoint(getOrigin().x(), getOrigin().y());
    QTransform fgTransform;
    fgTransform.translate(getPos().x(), getPos().y());
    fgTransform.scale(getFGScale().x(), getFGScale().y());
    fgTransform.rotate(getAngle());
    fgItem->setTransform(fgTransform);
    target.addItem(fgItem);

//    sf::Sprite fgSprite;
//    fgSprite.setTexture(foregroundTex);
//    fgSprite.setOrigin(getOrigin());
//    fgSprite.setPosition(getPos().x+4, getPos().y+4+32-32*getFGScale().y);
//    if( getFGScale().y < 0.25f)
//    {
//        fgSprite.setColor(sf::Color::Green);
//    }
//    else if( getFGScale().y > 0.25 && getFGScale().y < 0.75)
//    {

//        fgSprite.setColor(sf::Color::Yellow);
//    }
//    else
//    {
//        fgSprite.setColor(sf::Color::Red);
//    }

//    fgSprite.setScale(getFGScale());
//    fgSprite.setRotation(getAngle());
//    target.draw(fgSprite, states);


}
