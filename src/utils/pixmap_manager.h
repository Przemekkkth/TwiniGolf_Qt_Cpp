#ifndef PIXMAPMANAGER_H
#define PIXMAPMANAGER_H

#include "resource_holder.h"
#include <QPixmap>

class PixmapManager
{
public:
    enum TextureID
    {
        Ball, Hole, Point, Tile_Dark32, Tile_Dark64, Tile_Light32, Tile_Light64,
        Ball_Shadow, BG,  LevelText, Powermeter_FG, Powermeter_BG, Powermeter_Overlay,
        Title, UI_BG,
        Buttons, ButtonUnselected, ButtonSelected,
        QtLogo
    };
    static PixmapManager* Instance();
    QPixmap& getPixmap(TextureID id);
private:
    PixmapManager();
    PixmapManager(PixmapManager& other) = delete;
    void operator=(const PixmapManager &) = delete;

    ResourceHolder<QPixmap, TextureID> m_textures;
    static PixmapManager* ptr;
};
#endif // PIXMAPMANAGER_H
