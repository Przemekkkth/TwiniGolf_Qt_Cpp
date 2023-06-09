#ifndef TITLESCENE_H
#define TITLESCENE_H
#include <QGraphicsScene>

class QGraphicsPixmapItem;
class QTimer;
class QGraphicsSimpleTextItem;

class TitleScene : public QGraphicsScene
{
    Q_OBJECT
public:
    TitleScene(QObject *parent = nullptr);
    void stopTimer();
signals:
    void menuActivated();

private slots:
    void updateText();
private:
    QGraphicsPixmapItem* qtLogo, *titleItem;
    QGraphicsSimpleTextItem* pressAnyKeyText;
    QTimer* timer;
    bool isShow;

protected:
    virtual void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // TITLESCENE_H
