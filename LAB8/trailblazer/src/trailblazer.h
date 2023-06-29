/*
 * TDDD86 Trailblazer
 * This file declares the functions you will write in this assignment.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * Author: Marty Stepp
 * Slight modifications by Tommy Farnqvist
 */

#ifndef _trailblazer_h
#define _trailblazer_h

#include <vector>
#include "BasicGraph.h"

/*
 * Help function for the search algorithms to extract the paths in the
 * right order by reversing the order.
 */
vector<Node*> extractPath(Vertex* end);

/*
 * Starts at the given root node and explores as far as possible
 * along each branch before backtracking when a dead end is found.
 */
vector<Node*> depthFirstSearch(BasicGraph& graph, Node* start, Node* end);

/*
 * Starts at the given root node and explores all of its neighboring
 * nodes at the current depth before moving down to the level below it.
 */
vector<Node*> breadthFirstSearch(BasicGraph& graph, Node* start, Node* end);

/*
 * Tries to find the shortest path between by initially taking
 * the shortest path between two nodes. Then it looks for the TOTAL
 * shortest path.
 */
vector<Node*> dijkstrasAlgorithm(BasicGraph& graph, Node* start, Node* end);

/*
 * Similar to Dijkstras but adds a heuristic so that the algorithm
 * doesnt waste time exploring directions which seems less promising.
 */
vector<Node*> aStar(BasicGraph& graph, Node* start, Node* end);

#endif
