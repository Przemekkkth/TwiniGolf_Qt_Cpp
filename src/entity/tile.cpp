#include "tile.h"
#include "../utils/pixmap_manager.h"

Tile::Tile(QVector2D point, Type type)
{
    if(type == Dark32)
    {
        setTex(PixmapManager::TextureID::Tile_Dark32);
    }
    else if(type == Dark64)
    {
        setTex(PixmapManager::TextureID::Tile_Dark64);
    }
    else if(type == Light32)
    {
        setTex(PixmapManager::TextureID::Tile_Light32);
    }
    else if(type == Light64)
    {
        setTex(PixmapManager::TextureID::Tile_Light64);
    }
    setPos(point.x(), point.y());
}
