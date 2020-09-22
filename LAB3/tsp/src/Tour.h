#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {
public:
    /*Default constructor.*/
    Tour();

    /*Constructor which takes 4 points for testing*/
    Tour(Point a, Point b, Point c, Point d);

    /*Destructor.*/
    ~Tour();

    /*.*/
    void show();

    /*.*/
    void draw(QGraphicsScene* scene);

    /*.*/
    int size();

    /*.*/
    double distance();

    /*.*/
    void insertNearest(Point p);

    /*.*/
    void insertSmallest(Point p);

private:
    Node* firstNode;

};

#endif // TOUR_H
