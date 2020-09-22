/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * Maintains the game state:  Location of all robots, junk and hero.
 * Method isSafe() is used to keep Hero from moving stupidly.
 */

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <vector>
#include <QGraphicsScene>
#include "Unit.h"
#include "Robot.h"
#include "Junk.h"
#include "Hero.h"

class GameState {
public:
    GameState();

    // Constructor
    GameState(const int &numberOfRobots);

    // Destructor
    ~GameState();

    // Copy constructor
    GameState(const GameState &other);

    // Copy assign operator
    GameState& operator=(const GameState &other);

    /*
    * Clear and redraw entire playing field
    */
    void draw(QGraphicsScene* scene) const;

    /*
    * Teleport hero to random location
    */
    void teleportHero();

    /*
    * Move robots one step towards hero
    */
    void moveRobots();

    /* Count colliding robots
    * Also converts robots to junk while
    * checking collisions
    */
    int countCollisions ();

    /*
    * Check if any robots are left on playing field
    */
    bool anyRobotsLeft () const;

    /*
    * Is hero in same place as robot or junk?
    */
    bool heroDead() const;

    /*
    * Can unit safely reside here?
    */
    bool isSafe (const Unit& unit) const; // Can unit safely reside here?

    /*
    * Move hero towards dir
    */
    void moveHeroTowards (const Unit& dir);

    /*
    * Copy a GameState
    */
    void copyState(const GameState &other);

    /*
    * Return hero
    */
    Hero getHero () const;



private:
    // The Robots
    std::vector<Robot*> robots;

    // The Hero
    Hero hero;

    /*
    * Free of robots and junk only
    */
    bool isEmpty(const Unit& unit) const;

    /*
    * How many robots are there at unit?
    */
    int countRobotsAt(const Unit& unit) const;

};

#endif // GAMESTATE_H
