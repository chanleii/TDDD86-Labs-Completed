#include "costs.h"
#include "trailblazer.h"
using namespace std;
#include <queue>
#include <algorithm>
#include "pqueue.h"

vector<Node *> extractPath(Vertex* end) {
    vector<Node *> path;
    do {
        path.push_back(end);
        end = end->previous;
    } while(end != nullptr);

    reverse(path.begin(), path.end());

    return path;
}

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    graph.resetData();
    Stack<Node *> S;
    start->visited = true;
    S.push(start);

    while(!S.isEmpty()) {
        bool deadEnd = true;
        Node* V = S.pop();
        V->setColor(GREEN);

        for(Node* n: graph.getNeighbors(V)) {
            if(!n->visited) {
                if(n == end) {
                    n->previous = V;
                    n->setColor(GREEN);
                    return extractPath(end);
                }
                S.push(n);
                n->previous = V;
                n->setColor(YELLOW);
                V->visited = true;
                deadEnd = false;
            }
        }
        if (deadEnd) {
            V->setColor(GRAY);
        }
    }
    return extractPath(end);
}



vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    queue<Vertex*> Q;
    graph.resetData();
    start->visited = true;
    Q.push(start);

    while(!Q.empty()) {
        Vertex* v = Q.front();
        Q.pop();
        v->setColor(GREEN);

        if (v == end) {
            break;
        }

        for(Vertex* vert: graph.getNeighbors(v)) {
            if(!vert->visited) {
                vert->setColor(YELLOW);
                vert->visited = true;
                vert->previous = v;
                Q.push(vert);

            }
        }
    }
    path = extractPath(end);
    cout << path.size();
    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    PriorityQueue<Vertex*> Q;

    graph.resetData();

    for(Node* node: graph.getNodeSet()) {
        node->cost = INFINITY;
    }

    start->cost = 0;
    Q.enqueue(start, 0);
    while(!Q.isEmpty()) {
        Node* currentShortest = Q.dequeue();
        currentShortest->visited = true;
        currentShortest->setColor(GREEN);


        if(currentShortest == end) {
            break;
        }

        for(Node* neighbor: graph.getNeighbors(currentShortest)) {
            double cost = currentShortest->cost + graph.getArc(currentShortest, neighbor)->cost;

            if (cost < neighbor->cost) {
                if(neighbor->cost == INFINITY) {
                    Q.enqueue(neighbor, cost);
                } else {
                    Q.changePriority(neighbor, cost);
                }
                neighbor->cost = cost;
                neighbor->previous = currentShortest;
                neighbor->setColor(YELLOW);

            }
        }
    }

    path = extractPath(end);


    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    PriorityQueue<Vertex*> openSet;
    graph.resetData();

    for(Node* n: graph.getNodeSet()) {
        n->cost = INFINITY;
    }

    start->cost = 0;
    openSet.enqueue(start, start->cost);

    while(!openSet.isEmpty()) {

        Vertex* current = openSet.dequeue();
        current->setColor(GREEN);
        current->visited = true;

        if(current == end) {
            break;
        }

        for(Vertex* neighbour: graph.getNeighbors(current)) {
            if(!neighbour->visited) {
            double cost = current->cost + graph.getArc(current, neighbour)->cost;
            if(cost < neighbour->cost) {
                neighbour->cost = cost;
                neighbour->previous = current;
                neighbour->setColor(YELLOW);
                openSet.enqueue(neighbour, cost + neighbour->heuristic(end));
            }
            }
        }

    }



    return extractPath(end);
}
