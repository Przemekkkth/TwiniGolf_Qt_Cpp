#ifndef POWERBAR_H
#define POWERBAR_H
#include "entity.h"

class PowerBar : public Entity
{
public:
    PowerBar();

    // Drawable interface
    QPixmap overlayTex, foregroundTex;
    void setFGScale(float x, float y);
    QVector2D getFGScale() const;

private:
    QVector2D fgScale = QVector2D(1, 1);

    // Entity interface
public:
    virtual void draw(GameScene &target) const override;
};

#endif // POWERBAR_H
