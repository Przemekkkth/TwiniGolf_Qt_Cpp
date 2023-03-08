#include "hole.h"

Hole::Hole(QVector2D p_pos)
    : Entity(p_pos)
{
    setTex(PixmapManager::TextureID::Hole);
    setPos(p_pos.x(), p_pos.y());
}
