/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "Unit.h"
#include <QGraphicsScene>

class Robot : public Unit {
public:
    Robot();

    // Constructor
    Robot(const Robot &r);

    // Robot clone pointer
    Robot* clone() const ;

    /*
    * Draws this Robot onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) override;

    /*
    * Tells if the unit is junk or not.
    */
    virtual bool isJunk() const;
};

#endif // ROBOT_H
