#ifndef WINSCENE_H
#define WINSCENE_H
#include <QGraphicsScene>

class WinScene : public QGraphicsScene
{
public:
    WinScene(QObject* parent = nullptr);
};

#endif // WINSCENE_H
