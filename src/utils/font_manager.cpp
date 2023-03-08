#include "font_manager.h"
#include <QFontDatabase>

FontManager::FontManager()
{
//    int id = QFontDatabase::addApplicationFont(":/res/minecraft.ttf");
//    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
//    QFont minecraftFont(family);
//    m_fontMap[FontID::Main] = minecraftFont;
}

FontManager* FontManager::ptr = nullptr;

FontManager *FontManager::Instance()
{
    if(!ptr)
    {
        ptr = new FontManager();
    }
    return ptr;
}

QFont FontManager::getFont(FontID id) const
{
    return m_fontMap[id];
}

