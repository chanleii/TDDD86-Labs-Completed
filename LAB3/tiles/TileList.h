#ifndef TILELIST_H
#define TILELIST_H

#include <QGraphicsScene>
#include "Tile.h"

class TileList {
public:
    /*Constructor.*/
    TileList();

    /*Destructor.*/
    ~TileList();

    /*Checks if tiles needs to be expanded and creates a new tile and puts it on top of the array.*/
    void addTile(Tile tile);

    /*Iterates through tiles and draws every single tile on screen.*/
    void drawAll(QGraphicsScene* scene);

    /*Returns the index of the tile on top of the array at a given position, if none is found -1 is returned.*/
    int indexOfTopTile(int x, int y);

    /*Takes the tile on top of the given position and put its at the top the array.*/
    void raise(int x, int y);

    /*Same as raise() but instead puts the tile at the bottom of the array.*/
    void lower(int x, int y);

    /*Deletes the top tile at a given position and reduces the tileSize of tiles.*/
    void remove(int x, int y);

    /*Uses remove() on all the tiles that covers a given position.*/
    void removeAll(int x, int y);

private:
    /*Creates a new tileArray of size 10.*/
    Tile* tiles = new Tile[10];

    /*Sets the initial tileSize to 0 and is used to determine the last used spot in tiles, not to be confused with tileCapacity.*/
    int tilesSize = 0;

    /*The capacity of tiles which can be modified by other functions*/
    int tileCapacity = 10;

    /*If tiles has reached its capacity, double the size of it.*/
    void expandArray();

};

#endif // TILELIST_H
