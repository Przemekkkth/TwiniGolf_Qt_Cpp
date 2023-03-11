#include "power_bar.h"
#include <QGraphicsPixmapItem>
#include "../scene/game_scene.h"

PowerBar::PowerBar()
{
    //BG
    setTex(PixmapManager::TextureID::Powermeter_BG);
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

    QGraphicsRectItem* fgRect = new QGraphicsRectItem();
    fgRect->setRect(0,0,8,56);
    QTransform fgTransform;
    fgTransform.translate(getPos().x(), getPos().y());
    fgTransform.scale(getFGScale().x(), getFGScale().y());
    fgTransform.rotate(getAngle());
    fgRect->setTransform(fgTransform);
    fgRect->moveBy(+4,+4);
    if( getFGScale().y() < 0.25f)
    {
        fgRect->setPen(QPen(Qt::green));
        fgRect->setBrush(Qt::green);
    }
    else if(getFGScale().y() > 0.25f && getFGScale().y() < 0.75f)
    {
        fgRect->setPen(QPen(Qt::yellow));
        fgRect->setBrush(Qt::yellow);
    }
    else
    {
        fgRect->setPen(QPen(Qt::red));
        fgRect->setBrush(Qt::red);
    }
    target.addItem(fgRect);
}
