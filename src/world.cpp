#include "world.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>
#include "utils/pixmap_manager.h"
#include "utils/font_manager.h"
#include "scene/game_scene.h"
#include "entity/ball.h"
#include "entity/hole.h"
#include "entity/tile.h"

World::World()
{

    balls[0] = {new Ball(0)};
    balls[1] = {new Ball(1)};
    holes = { new Hole(QVector2D(0.0f, 0.0f)), new Hole(QVector2D(0.0f, 0.0f))};

    level = 0;
    tiles = loadTiles(level);
    gameRunning = true;
    mouseDown = false;
    mousePressed = false;

    swingPlayed = false;
    secondSwingPlayed = false;

    loadLevel(level);
}

void World::clearTiles()
{
    for(auto tile: tiles)
    {
        delete tile;
    }
    tiles.clear();
}

World::~World()
{
    clearTiles();

    for(auto hole : holes)
    {
        delete hole;
    }
    holes.clear();

    delete balls[0];
    delete balls[1];
}

void World::initWorld(int level)
{
    this->level = level;
    gameRunning = true;
    mouseDown = false;
    mousePressed = false;

    swingPlayed = false;
    secondSwingPlayed = false;

    loadLevel(level);

}

void World::draw(GameScene& gScene)
{
    QGraphicsPixmapItem* bgItem = new QGraphicsPixmapItem();
    bgItem->setPixmap(QPixmap(":/res/sprite/bg.png"));
    gScene.addItem(bgItem);

    for (Hole* h : holes)
    {
        h->draw(gScene);
    }

    for (Ball* b : balls)
    {
        if (!b->isWin())
        {
            QGraphicsPixmapItem* ballShadow = new QGraphicsPixmapItem();
            ballShadow->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::Ball_Shadow));
            ballShadow->setPos(b->getPos().x(), b->getPos().y()+4);
            ballShadow->setRotation(b->getAngle());
            gScene.addItem(ballShadow);
        }

        (*b).getPoint()->draw(gScene);
        (*b).draw(gScene);
    }

    for (Tile* t : tiles)
    {
        (*t).draw(gScene);
    }
    for(Ball* b : balls)
    {
        (*b).draw(gScene);
        (*b).getPowerBar()->draw(gScene);
    }
    drawUI(gScene);
}

void World::drawUI(GameScene &gScene)
{
    drawBGUI(gScene, QPoint(640/4 - 132/2, 480 - 32));

    drawUIText(gScene, QPoint(180, 466), Qt::black, getLevelText(0));
    drawUIText(gScene, QPoint(180, 462), Qt::white, getLevelText(0));


    drawBGUI(gScene, QPoint(640/2 + 640/4 - 132/2, 480 - 32));

    drawUIText(gScene, QPoint(502, 466), Qt::black, getLevelText(1));
    drawUIText(gScene, QPoint(502, 462), Qt::white, getLevelText(1));

    drawBGUI(gScene, QPoint(640/2 - 196/2, 0));

    drawUIText(gScene, QPoint(320, 16), Qt::black, getStrokeText());
    drawUIText(gScene, QPoint(320, 13), Qt::white, getStrokeText());

}

void World::drawBGUI(GameScene &gScene, QPoint pos)
{
    QGraphicsPixmapItem* bgUI = new QGraphicsPixmapItem();
    bgUI->setPixmap(PixmapManager::Instance()->getPixmap(PixmapManager::TextureID::UI_BG));
    bgUI->setPos(pos);
    gScene.addItem(bgUI);
}

void World::drawUIText(GameScene &gScene, QPoint pos, QColor color, QString text)
{
    QGraphicsSimpleTextItem* tItem = new QGraphicsSimpleTextItem();
    QFont font = FontManager::Instance()->getFont(FontManager::FontID::Main);
    font.setPixelSize(24);
    tItem->setFont(font);
    tItem->setPen(color);
    tItem->setBrush(color);
    tItem->setText(text);
    QTransform tTransform;
    tTransform.translate(pos.x() - tItem->boundingRect().width()/2.0f
                         , pos.y() - tItem->boundingRect().height()/2.0f);
    tItem->setTransform(tTransform);
    gScene.addItem(tItem);
}

void World::update(float elapsedTime)
{
    if (!swingPlayed)
    {
        swingPlayed = true;
    }
    if (!secondSwingPlayed)
    {
        secondSwingPlayed = true;
    }
    for (Ball* b : balls)
    {
        b->update(elapsedTime, mouseDown, mousePressed, tiles, holes);
    }
    if(MouseStatus::mousePressed)
    {
        MouseStatus::mousePressed = false;
    }
    if (balls[0]->getScale().x() < 0.0f && balls[1]->getScale().x() < 0.0f)
    {
        level++;
        loadLevel(level);
    }
}

QVector<Tile *> World::loadTiles(int level)
{
    QVector<Tile*> temp = {};
    switch(level)
    {
    case 0:break;
        case 1:
            temp.push_back(new Tile(QVector2D(64*3, 64*3), Tile::Type::Dark64));
            temp.push_back(new Tile(QVector2D(64*4, 64*3), Tile::Type::Dark64));

            temp.push_back(new Tile(QVector2D(64*0, 64*3), Tile::Type::Dark64));
            temp.push_back(new Tile(QVector2D(64*1, 64*3), Tile::Type::Dark64));

            temp.push_back(new Tile(QVector2D(64*3 + 64*5, 64*3), Tile::Type::Light64));
            temp.push_back(new Tile(QVector2D(64*4 + 64*5, 64*3), Tile::Type::Light64));

            temp.push_back(new Tile(QVector2D(64*0 + 64*5, 64*3), Tile::Type::Light64));
            temp.push_back(new Tile(QVector2D(64*1 + 64*5, 64*3), Tile::Type::Light64));
        break;
        case 2:
            temp.push_back(new Tile(QVector2D(64*2, 64*3), Tile::Type::Dark64));

            temp.push_back(new Tile(QVector2D(64*4 + 64*5, 64*3), Tile::Type::Light64));
        break;
        case 3:
            temp.push_back(new Tile(QVector2D(32*1 + 32*10 + 16, 32*5), Tile::Type::Light32));
        break;
        case 4:
            temp.push_back(new Tile(QVector2D(32*4, 32*7), Tile::Type::Dark64));
            temp.push_back(new Tile(QVector2D(32*3, 32*5), Tile::Type::Dark32));
            temp.push_back(new Tile(QVector2D(32*6, 32*3), Tile::Type::Dark32));

            temp.push_back(new Tile(QVector2D(32*4 + 64*5, 32*2), Tile::Type::Light64));
            temp.push_back(new Tile(QVector2D(32*3 + 32*10, 32*6), Tile::Type::Light32));
            temp.push_back(new Tile(QVector2D(32*6 + 32*10, 32*9), Tile::Type::Light32));
        break;
        case 5:
            temp.push_back(new Tile(QVector2D(32*3, 32*1), Tile::Type::Dark32));
            temp.push_back(new Tile(QVector2D(32*1, 32*3), Tile::Type::Dark32));
            temp.push_back(new Tile(QVector2D(32*5, 32*3), Tile::Type::Dark32));
            temp.push_back(new Tile(QVector2D(32*3, 32*5), Tile::Type::Dark32));
            temp.push_back(new Tile(QVector2D(32*7, 32*5), Tile::Type::Dark32));
            temp.push_back(new Tile(QVector2D(32*7, 32*10), Tile::Type::Dark32));
            temp.push_back(new Tile(QVector2D(32*3, 32*10), Tile::Type::Dark32));
            temp.push_back(new Tile(QVector2D(32*5, 32*12), Tile::Type::Dark32));
            temp.push_back(new Tile(QVector2D(32*7, 32*10), Tile::Type::Dark32));

            temp.push_back(new Tile(QVector2D(32*8, 32*7), Tile::Type::Dark64));

            temp.push_back(new Tile(QVector2D(32*2 + 32*10, 32*2), Tile::Type::Light32));
            temp.push_back(new Tile(QVector2D(32*5 + 32*10, 32*11), Tile::Type::Light32));

            temp.push_back(new Tile(QVector2D(32*3 + 32*10, 32*1), Tile::Type::Light64));
            temp.push_back(new Tile(QVector2D(32*8 + 32*10, 32*6), Tile::Type::Light64));
            temp.push_back(new Tile(QVector2D(32*3 + 32*10, 32*11), Tile::Type::Light64));
        break;
    case 6:
        //Left
        temp.push_back(new Tile(QVector2D(32*0, 32*3), Tile::Type::Dark32));
        temp.push_back(new Tile(QVector2D(32*1, 32*3), Tile::Type::Dark32));
        temp.push_back(new Tile(QVector2D(32*2, 32*3), Tile::Type::Dark32));
        temp.push_back(new Tile(QVector2D(32*3, 32*3), Tile::Type::Dark32));
        temp.push_back(new Tile(QVector2D(32*4, 32*3), Tile::Type::Dark32));
        temp.push_back(new Tile(QVector2D(32*5, 32*3), Tile::Type::Dark32));
        temp.push_back(new Tile(QVector2D(32*6, 32*3), Tile::Type::Dark32));

        temp.push_back(new Tile(QVector2D(32*3, 32*6), Tile::Type::Dark32));
        temp.push_back(new Tile(QVector2D(32*4, 32*6), Tile::Type::Dark32));
        temp.push_back(new Tile(QVector2D(32*5, 32*6), Tile::Type::Dark32));
        temp.push_back(new Tile(QVector2D(32*6, 32*6), Tile::Type::Dark32));
        temp.push_back(new Tile(QVector2D(32*7, 32*6), Tile::Type::Dark32));
        temp.push_back(new Tile(QVector2D(32*8, 32*6), Tile::Type::Dark32));
        temp.push_back(new Tile(QVector2D(32*9, 32*6), Tile::Type::Dark32));

        temp.push_back(new Tile(QVector2D(32*0, 32*10), Tile::Type::Dark32));
        temp.push_back(new Tile(QVector2D(32*1, 32*10), Tile::Type::Dark32));
        temp.push_back(new Tile(QVector2D(32*2, 32*10), Tile::Type::Dark32));
        temp.push_back(new Tile(QVector2D(32*6, 32*10), Tile::Type::Dark32));
        temp.push_back(new Tile(QVector2D(32*7, 32*10), Tile::Type::Dark32));
        temp.push_back(new Tile(QVector2D(32*8, 32*10), Tile::Type::Dark32));
        temp.push_back(new Tile(QVector2D(32*9, 32*10), Tile::Type::Dark32));

        //Right
        temp.push_back(new Tile(QVector2D(32*0 + 32*10, 32*3), Tile::Type::Light32));
        temp.push_back(new Tile(QVector2D(32*1 + 32*10, 32*3), Tile::Type::Light32));
        temp.push_back(new Tile(QVector2D(32*2 + 32*10, 32*3), Tile::Type::Light32));
        temp.push_back(new Tile(QVector2D(32*3 + 32*10, 32*3), Tile::Type::Light32));
        temp.push_back(new Tile(QVector2D(32*4 + 32*10, 32*3), Tile::Type::Light32));
        temp.push_back(new Tile(QVector2D(32*5 + 32*10, 32*3), Tile::Type::Light32));
        temp.push_back(new Tile(QVector2D(32*6 + 32*10, 32*3), Tile::Type::Light32));

        temp.push_back(new Tile(QVector2D(32*3 + 32*10, 32*6), Tile::Type::Light32));
        temp.push_back(new Tile(QVector2D(32*4 + 32*10, 32*6), Tile::Type::Light32));
        temp.push_back(new Tile(QVector2D(32*5 + 32*10, 32*6), Tile::Type::Light32));
        temp.push_back(new Tile(QVector2D(32*6 + 32*10, 32*6), Tile::Type::Light32));
        temp.push_back(new Tile(QVector2D(32*7 + 32*10, 32*6), Tile::Type::Light32));
        temp.push_back(new Tile(QVector2D(32*8 + 32*10, 32*6), Tile::Type::Light32));
        temp.push_back(new Tile(QVector2D(32*9 + 32*10, 32*6), Tile::Type::Light32));

        temp.push_back(new Tile(QVector2D(32*0 + 32*10, 32*10), Tile::Type::Light32));
        temp.push_back(new Tile(QVector2D(32*1 + 32*10, 32*10), Tile::Type::Light32));
        temp.push_back(new Tile(QVector2D(32*2 + 32*10, 32*10), Tile::Type::Light32));
        temp.push_back(new Tile(QVector2D(32*6 + 32*10, 32*10), Tile::Type::Light32));
        temp.push_back(new Tile(QVector2D(32*7 + 32*10, 32*10), Tile::Type::Light32));
        temp.push_back(new Tile(QVector2D(32*8 + 32*10, 32*10), Tile::Type::Light32));
        temp.push_back(new Tile(QVector2D(32*9 + 32*10, 32*10), Tile::Type::Light32));
        break;
     case 7:
        //Left
        temp.push_back(new Tile(QVector2D(32*4, 32*6), Tile::Type::Dark64));
        temp.push_back(new Tile(QVector2D(32*2, 32*4), Tile::Type::Dark32));
        temp.push_back(new Tile(QVector2D(32*7, 32*9), Tile::Type::Dark32));
        //Right
        temp.push_back(new Tile(QVector2D(32*4 + 32*10, 32*6), Tile::Type::Light64));
        temp.push_back(new Tile(QVector2D(32*2 + 32*10, 32*4), Tile::Type::Light32));
        temp.push_back(new Tile(QVector2D(32*7 + 32*10, 32*9), Tile::Type::Light32));

        break;
    case 8:
        //Left
        temp.push_back(new Tile(QVector2D(32*4, 32*4), Tile::Type::Dark32));
        temp.push_back(new Tile(QVector2D(32*3, 32*2), Tile::Type::Dark64));
        temp.push_back(new Tile(QVector2D(32*2, 32*2), Tile::Type::Dark32));
        temp.push_back(new Tile(QVector2D(32*5, 32*3), Tile::Type::Dark32));
        temp.push_back(new Tile(QVector2D(32*6, 32*2), Tile::Type::Dark32));
        //Right
        temp.push_back(new Tile(QVector2D(32*4+32*10, 32*2), Tile::Type::Light32));
        temp.push_back(new Tile(QVector2D(32*3+32*10, 32*4), Tile::Type::Light64));
        temp.push_back(new Tile(QVector2D(32*2+32*10, 32*4), Tile::Type::Light32));
        temp.push_back(new Tile(QVector2D(32*5+32*10, 32*3), Tile::Type::Light32));
        temp.push_back(new Tile(QVector2D(32*6+32*10, 32*4), Tile::Type::Light32));
        break;
    }
    return temp;
}

void World::loadLevel(int level)
{
    if (level > 8)
    {
        state = 2;
        return;
    }
    balls[0]->setVelocity(0, 0);
    balls[1]->setVelocity(0,0);
    balls[0]->setScale(1, 1);
    balls[1]->setScale(1, 1);
    balls[0]->setWin(false);
    balls[1]->setWin(false);

    clearTiles();
    tiles = loadTiles(level);

    switch (level)
    {
    case 0:
        balls[0]->setPos(8 + 32*4, 8 + 32*8);
        balls[1]->setPos(8 + 32*4 + 32*10, 8 + 32*8);

        holes.at(0)->setPos(8 + 32*4, 8 + 32*2);
        holes.at(1)->setPos(8 + 32*4 + 32*10, 8 + 32*2);
        break;
    case 1:
        balls[0]->setPos(24 + 32*4, 24 + 32*11);
        balls[1]->setPos(24 + 32*4 + 32*10, 24 + 32*11);

        holes.at(0)->setPos(24 + 32*4, 22 + 32*2);
        holes.at(1)->setPos(24 + 32*4 + 32*10, 22 + 32*2);
        break;
    case 2:
        balls[0]->setPos(24 + 32*4, 24 + 32*11);
        balls[1]->setPos(24 + 32*4 + 32*10, 24 + 32*11);

        holes.at(0)->setPos(24 + 32*4, 22 + 32*2);
        holes.at(1)->setPos(24 + 32*4 + 32*10, 22 + 32*2);
        break;
    case 3:
        balls[0]->setPos(8 + 32*7, 8 + 32*10);
        balls[1]->setPos(8 + 32*7 + 32*10, 8 + 32*10);

        holes.at(0)->setPos(8 + 32*2, 6 + 32*5);
        holes.at(1)->setPos(8 + 32*4 + 32*10, 6 + 32*3);
        break;
    case 4:
        balls[0]->setPos(24 + 32*4, 24 + 32*5);
        balls[1]->setPos(24 + 32*4 + 32*10, 24 + 32*4);

        holes.at(0)->setPos(24 + 32*4, 22 + 32*1);
        holes.at(1)->setPos(24 + 32*4 + 32*10, 22 + 32*11);
        break;
    case 5:
        balls[0]->setPos(24 + 32*2, 24 + 32*12);
        balls[1]->setPos(24 + 32*0 + 32*10, 24 + 32*5);

        holes.at(0)->setPos(24 + 32*1, 22 + 32*1);
        holes.at(1)->setPos(24 + 32*0 + 32*10, 22 + 32*7);
        break;
    case 6:
        balls[0]->setPos(24 + 32*8, 24 + 32*12);
        holes.at(0)->setPos(24 + 32*1, 22 + 32*1);

        holes.at(1)->setPos(24 + 32*8 + 32*10, 24 + 32*12);
        balls[1]->setPos(24 + 32*0 + 32*10, 22 + 32*1);

        break;
    case 7:
        balls[0]->setPos(32*2+8, 32*9+8);
        holes.at(0)->setPos(32*7+8, 32*4+8);

        balls[1]->setPos(32*7+8 + 32*10, 32*4+8);
        holes.at(1)->setPos(32*2+8+32*10, 32*9+8);
        break;
    case 8:
        balls[0]->setPos(32*4+8, 32*9+8);
        holes.at(0)->setPos(32*5+8, 32*2+8);
        balls[1]->setPos(32*4+8+32*10, 32*9+8);
        holes.at(1)->setPos(32*4+8+32*10, 32*3+8);
        break;
    }
}

QString World::getStrokeText()
{
    int biggestStroke = 0;
    if (balls[1]->getStrokes() > balls[0]->getStrokes())
    {
        biggestStroke = balls[1]->getStrokes();
    }
    else
    {
        biggestStroke = balls[0]->getStrokes();
    }
    QString retVal = QString("STROKES: ") + QString::number(biggestStroke);
    return retVal;
}

QString World::getLevelText(int side)
{
    int tempLevel = (level + 1)*2 - 1;
    if (side == 1)
    {
        tempLevel++;
    }
    QString retVal = QString("HOLE: ") + QString::number(tempLevel);
    return retVal;
}
