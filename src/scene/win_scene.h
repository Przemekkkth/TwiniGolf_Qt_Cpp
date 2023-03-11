#ifndef WINSCENE_H
#define WINSCENE_H
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>

class WinScene : public QGraphicsScene
{
    Q_OBJECT
public:
    WinScene(QObject* parent = nullptr);
signals:
    void menuActivated();

private slots:
    void updateText();
private:
    QGraphicsPixmapItem *titleItem;
    QGraphicsSimpleTextItem* infoText, *resultText;
    QGraphicsSimpleTextItem* pressAnyKeyText;
    QTimer* timer;
    bool isShow;

protected:
    virtual void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // WINSCENE_H
