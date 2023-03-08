#ifndef HOLE_H
#define HOLE_H
#include "entity.h"

class Hole : public Entity
{
public:
    Hole(QVector2D p_pos);
    virtual ~Hole(){}
};

#endif // HOLE_H
