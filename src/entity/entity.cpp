#include "entity.h"
#include "../scene/game_scene.h"
#include <QGraphicsPixmapItem>

Entity::Entity(QVector2D p_pos)
    : pos(p_pos)
{
    currentFrame = QRect(0,0, 32, 32);
}

Entity::Entity()
{
    pos = QVector2D(0,0);
    currentFrame = QRect(0,0, 32,32);
}

QVector2D Entity::getPos() const
{
    return pos;
}

float Entity::getAngle() const
{
    return angle;
}

QVector2D Entity::getScale() const
{
    return scale;
}

QPixmap Entity::getTex() const
{
    return tex;
}

QVector2D Entity::getOrigin() const
{
    return origin;
}

void Entity::setPos(float x, float y)
{
    pos.setX(x);
    pos.setY(y);
}

void Entity::setScale(float w, float h)
{
    scale.setX(w);
    scale.setY(h);
}

void Entity::setAngle(float angle)
{
    this->angle = angle;
}

void Entity::setTex(PixmapManager::TextureID id)
{
    tex = PixmapManager::Instance()->getPixmap(id);
    currentFrame = QRect(0,0,tex.size().width(), tex.height());
}

void Entity::setOrigin(float x, float y)
{
    origin.setX(x);
    origin.setY(y);
}

void Entity::update(float time)
{

}

QRect Entity::getCurrentFrame()
{
    return currentFrame;
}

void Entity::draw(GameScene &target) const
{
    QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem();
    pItem->setPixmap(tex);
    QTransform transform;
    transform.translate(pos.x(), pos.y());
    transform.scale(scale.x(), scale.y());
    transform.rotate(angle);

    pItem->setTransformOriginPoint(origin.x(), origin.y());
    pItem->setTransform(transform);

    target.addItem(pItem);
}
