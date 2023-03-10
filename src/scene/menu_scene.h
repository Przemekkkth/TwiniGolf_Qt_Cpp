#ifndef MENUSCENE_H
#define MENUSCENE_H
#include <QGraphicsScene>

class MenuScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MenuScene(QObject* parent = nullptr);
};

#endif // MENUSCENE_H
