#ifndef ENTITY_H
#define ENTITY_H
#include <QVector2D>
#include <QPixmap>
#include <QRect>
#include "../utils/pixmap_manager.h"

class GameScene;
class Entity
{
public:
    Entity(QVector2D p_pos);
    Entity();
    virtual ~Entity(){}
    QVector2D getPos() const;
    float getAngle() const;
    QVector2D getScale() const;
    QPixmap getTex() const;
    QVector2D getOrigin() const;

    void setPos(float x, float y);
    void setScale(float w, float h);
    void setAngle(float angle);
    void setTex(PixmapManager::TextureID _tex);
    void setOrigin(float x, float y);

    void update(float time);
    QRect getCurrentFrame();
    float getAngle();
    QPixmap tex;
private:
    QVector2D pos;
    float angle = 0;
    QVector2D origin = QVector2D(0, 0);
    QVector2D scale =  QVector2D(1, 1);
    QRect currentFrame;


    // Drawable interface
public:
    virtual void draw(GameScene &target) const;
};

#endif // ENTITY_H
