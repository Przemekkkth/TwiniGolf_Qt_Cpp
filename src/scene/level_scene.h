#ifndef LEVELSCENE_H
#define LEVELSCENE_H
#include <QGraphicsScene>

class QGraphicsPixmapItem;
class LevelScene : public QGraphicsScene
{
    Q_OBJECT
public:
    LevelScene(QObject* parent = nullptr);
    void prepareScene();
signals:
    void gameActivated(int level);
    void menuActivated();
private:
    QGraphicsPixmapItem* getActiveButton();
    void addTextToButton(QGraphicsPixmapItem* button, QString text);
    QGraphicsPixmapItem* title;
    QGraphicsPixmapItem *zeroButton, *oneButton, *twoButton,
    *threeButton, *fourButton, *fiveButton, *sixButton, *sevenButton,
    *eightButton, *menuButton;
    int currentIndex;

    // QGraphicsScene interface
protected:
    virtual void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // LEVELSCENE_H
