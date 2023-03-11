#ifndef WORLD_H
#define WORLD_H
#include <QVector>
#include <QPoint>
#include <QColor>
class Ball;
class Hole;
class Tile;

class GameScene;
class World
{
public:
    World();
    ~World();
    void initWorld(int level);
    void draw(GameScene& gScene);
    void drawUI(GameScene& gScene);
    void drawBGUI(GameScene& gScene, QPoint pos);
    void drawUIText(GameScene& gScene, QPoint pos, QColor color, QString text);
    void update(float elapsedTime);
private:
    Ball *balls[2];
    QVector<Hole*> holes;
    QVector<Tile*> tiles;
    QVector<Tile*> loadTiles(int level);
    bool gameRunning, mouseDown, mousePressed, swingPlayed, secondSwingPlayed;
    int level;
    int state;
    void loadLevel(int level);
    QString getStrokeText();
    QString getLevelText(int side);
    void clearTiles();
};

#endif // WORLD_H
