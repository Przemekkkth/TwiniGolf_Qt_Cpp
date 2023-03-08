#ifndef TILE_H
#define TILE_H
#include "entity.h"

class Tile : public Entity
{
public:    
    enum Type{ Dark32, Dark64, Light32, Light64};
    Tile(QVector2D point, Type type);
    virtual ~Tile(){}
};

#endif // TILE_H
