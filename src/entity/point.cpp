#include "point.h"
#include "../utils/pixmap_manager.h"

Point::Point()
    : Entity()
{
    setTex(PixmapManager::Point);
    setOrigin(8,0);
}
