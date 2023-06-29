#include "TileList.h"

TileList::TileList()
{
}

TileList::~TileList()
{
    delete[] tiles;
}

void TileList::addTile(Tile tile)
{
    expandArray();
    tiles[tilesSize] = tile;
    tilesSize++;
}

void TileList::drawAll(QGraphicsScene* scene)
{
    for(int i = 0; i < tilesSize; i++) {
        tiles[i].draw(scene);
    }
}

int TileList::indexOfTopTile(int x, int y)
{
    for(int i = tilesSize-1; i > -1; i--) {
        if(tiles[i].contains(x, y)) {
            return i;
        }
    }

    return -1;
}

void TileList::raise(int x, int y)
{
    const int topIndex = indexOfTopTile(x, y);

    if(topIndex != -1) {
        const Tile moveToTop = tiles[topIndex];

        for(int i = topIndex; i < tilesSize-1; i++) {
            tiles[i] = tiles[i+1];
        }

        tiles[tilesSize-1] = moveToTop;
    }
}

void TileList::lower(int x, int y)
{
    const int topIndex = indexOfTopTile(x, y);

    if(topIndex != -1) {
        const Tile moveToBottom = tiles[topIndex];

        for(int i = topIndex; i > 0; i--) {
            tiles[i] = tiles[i-1];
        }

        tiles[0] = moveToBottom;
    }
}

void TileList::remove(int x, int y)
{
    const int topIndex = indexOfTopTile(x, y);

    if(topIndex != -1) {

        for(int i = topIndex; i < tilesSize; i++) {
            tiles[i] = tiles[i+1];
        }
        tilesSize--;
    }
}

void TileList::removeAll(int x, int y)
{
    while(indexOfTopTile(x, y) != -1) {
        remove(x, y);
    }
}

void TileList::expandArray()
{
    if(tilesSize == tileCapacity) {
        Tile* new_tileList = new Tile[tileCapacity*2];

        for(int i = 0; i < tileCapacity; i++) {
            new_tileList[i] = tiles[i];
        }
        delete[] tiles;

        tiles = new_tileList;
        tileCapacity = tileCapacity*2;

    }
}
