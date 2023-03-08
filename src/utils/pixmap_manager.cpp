#include "pixmap_manager.h"

PixmapManager* PixmapManager::ptr = nullptr;

PixmapManager *PixmapManager::Instance()
{
    if(!ptr)
    {
        ptr = new PixmapManager();
    }
    return ptr;
}

QPixmap& PixmapManager::getPixmap(TextureID id)
{
    return m_textures.get(id);
}

PixmapManager::PixmapManager()
{
    m_textures.load(TextureID::Ball, ":/res/sprite/ball.png");
    m_textures.load(TextureID::Ball_Shadow, ":/res/sprite/ball_shadow.png");
    m_textures.load(TextureID::BG, ":/res/sprite/bg.png");
    m_textures.load(TextureID::Buttons, ":/res/sprite/buttons.png");
    m_textures.load(TextureID::Hole, ":/res/sprite/hole.png");
    m_textures.load(TextureID::LevelText, ":/res/sprite/levelText_bg.png");
    m_textures.load(TextureID::Point, ":/res/sprite/point.png");
    m_textures.load(TextureID::Powermeter_BG, ":/res/sprite/powermeter_bg.png");
    m_textures.load(TextureID::Powermeter_FG, ":/res/sprite/powermeter_fg.png");
    m_textures.load(TextureID::Powermeter_Overlay, ":/res/sprite/powermeter_overlay.png");

    m_textures.load(TextureID::Tile_Dark32, ":/res/sprite/tile32_dark.png");
    m_textures.load(TextureID::Tile_Dark64, ":/res/sprite/tile64_dark.png");
    m_textures.load(TextureID::Tile_Light32, ":/res/sprite/tile32_light.png");
    m_textures.load(TextureID::Tile_Light64, ":/res/sprite/tile64_light.png");

    m_textures.load(TextureID::UI_BG, ":/res/sprite/UI_bg.png");
//    m_textures.load(TextureID::Blocks, ":/res/blocks.png");
//    m_textures.load(TextureID::Title, ":/res/title.png");
//    m_textures.load(TextureID::Buttons, ":/res/buttons.png");
//    m_textures.load(TextureID::QtLogo, ":/res/Qt_logo.png");

//    std::unique_ptr<QPixmap> ButtonUnselected(new QPixmap(getPixmap(TextureID::Buttons).copy(0,0,200,50)));
//    m_textures.insertResource(TextureID::ButtonUnselected, std::move(ButtonUnselected));

//    std::unique_ptr<QPixmap> ButtonSelected(new QPixmap(getPixmap(TextureID::Buttons).copy(0,50,200,50)));
//    m_textures.insertResource(TextureID::ButtonSelected, std::move(ButtonSelected));
}
