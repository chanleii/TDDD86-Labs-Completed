#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour()
{
    firstNode = nullptr;
}

Tour::Tour(Point a, Point b, Point c, Point d) {
    firstNode = new Node(a, new Node(b, new Node(c, new Node(d, nullptr))));

    Node* currentNode = firstNode;

    while(currentNode->next != nullptr) {
        currentNode = currentNode->next;
    }

    currentNode->next = firstNode;

}

Tour::~Tour()
{
    Node* currentNode = firstNode->next;
    Node* nextNode = currentNode->next;

    do {
        delete currentNode;
        currentNode = nextNode;
        nextNode = currentNode->next;
    } while (currentNode != firstNode);
    delete firstNode;
}

void Tour::show()
{
    Node* currentNode = firstNode;

    do {
        cout << currentNode->point.toString() << endl;
        currentNode = currentNode -> next;
    } while(currentNode != firstNode);
}

void Tour::draw(QGraphicsScene *scene)
{
    Node* currentNode = firstNode;
    do {
        currentNode->point.drawTo(currentNode->next->point, scene);
        currentNode = currentNode -> next;
    } while(currentNode != firstNode);
}

int Tour::size()
{
    int size = 0;
    Node* currentNode = firstNode;
    do {
        size++;
        currentNode = currentNode -> next;
    } while(currentNode != firstNode);

    return size;
}

double Tour::distance()
{
    double dist = 0;

    Node* currentNode = firstNode;
    do {
        dist += currentNode->point.distanceTo(currentNode->next->point);
        currentNode = currentNode -> next;
    } while(currentNode != firstNode);

    return dist;
}

void Tour::insertNearest(Point p)
{
    if(firstNode == nullptr) {
        firstNode = new Node(p, nullptr);
        firstNode->next = firstNode;
        return;
    }

    Node* currentNode = firstNode;
    Node* closestNode = firstNode;
    double closestDistance = currentNode->point.distanceTo(p);

    do {
        if(currentNode->point.distanceTo(p) < closestDistance) {
            closestNode = currentNode;
            closestDistance = currentNode->point.distanceTo(p);
        }
        currentNode = currentNode->next;
    } while(currentNode != firstNode);

    closestNode->next = new Node(p, closestNode->next);

}

void Tour::insertSmallest(Point p)
{

    if(firstNode == nullptr) {
        firstNode = new Node(p, nullptr);
        firstNode->next = firstNode;
        return;
    }

    Node* currentNode = firstNode;
    Node* closestNode = firstNode;
    double closestDist = currentNode->point.distanceTo(p) + p.distanceTo(currentNode->next->point) - currentNode->point.distanceTo(currentNode->next->point);

    do {
        double addedDist = currentNode->point.distanceTo(p) + p.distanceTo(currentNode->next->point) - currentNode->point.distanceTo(currentNode->next->point);
        if(addedDist < closestDist) {
            closestNode = currentNode;
            closestDist = addedDist;
        }
        currentNode = currentNode->next;
    } while(currentNode != firstNode);
    closestNode->next = new Node(p, closestNode->next);


}
