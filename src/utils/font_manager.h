#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <QFont>
#include <QMap>

class FontManager
{
public:
    enum class FontID{
        Main
    };
    static FontManager* Instance();
    QFont getFont(FontID id) const;
private:
    FontManager();
    FontManager(FontManager& other) = delete;
    void operator=(const FontManager &) = delete;

    QMap<FontID, QFont> m_fontMap;
    static FontManager* ptr;
};


#endif // FONTMANAGER_H
