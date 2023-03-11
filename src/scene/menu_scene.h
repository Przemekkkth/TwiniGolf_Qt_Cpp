#ifndef MENUSCENE_H
#define MENUSCENE_H
#include <QGraphicsScene>
class QGraphicsPixmapItem;
class MenuScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MenuScene(QObject* parent = nullptr);
    void prepareScene();
signals:
    void gameActivated();
    void levelsActivated();
private:
    QGraphicsPixmapItem* getActiveButton();
    void addTextToButton(QGraphicsPixmapItem* button, QString text);
    QGraphicsPixmapItem *startButton, *levelButton, *exitButton;
    QGraphicsPixmapItem *title;
    int currentIndex;

    // QGraphicsScene interface
protected:
    virtual void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // MENUSCENE_H
