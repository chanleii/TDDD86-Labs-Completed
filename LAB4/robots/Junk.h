/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef JUNK_H
#define JUNK_H

#include "Unit.h"
#include "Robot.h"
#include <QGraphicsScene>

class Junk : public Robot {
public:
    Junk();

    // Constructor
    Junk(Robot r);

    // Junk Clone Pointer
    Junk* clone() const ;

    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) override;

    void attacks();

    void moveTowards(const Unit& u) override;

    /*
    * Tells if the unit is junk or not.
    */
    virtual bool isJunk() const override;
};

#endif // JUNK_H
