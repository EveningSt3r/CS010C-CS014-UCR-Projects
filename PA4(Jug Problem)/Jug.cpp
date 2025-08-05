#include "Jug.h"
#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <utility>
#include <list>

using std::priority_queue;
using std::map;
using std::min;
using std::stringstream;
using std::list;
using std::pair;

struct CompareVertex {
    bool operator()(const Vertex* v1, const Vertex* v2) {
        return v1->distance > v2->distance;  // Min-priority queue based on distance
    }
};

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA)
: capacityA(Ca), capacityB(Cb), goal(N), fillCostA(cfA), fillCostB(cfB), emptyCostA(ceA),
emptyCostB(ceB), pourCostA(cpAB), pourCostB(cpBA) {
    // initialize all members before check
}

Jug::~Jug() {
    for(Vertex* v : graph) {
        delete v;
    }
    graph.clear();
}

bool Jug::parameterCheck() {
    if(fillCostA < 0 || fillCostB < 0 || emptyCostA < 0 || emptyCostB < 0
    || pourCostA < 0 || pourCostB < 0) {
        return false;
    }
    // check if costs are negative

    if(!(capacityA > 0 && capacityA <= capacityB) ||
     !(goal >= 0 && goal <= capacityB && capacityB <= 1000)) {
        return false;
    }
    // check: 0 <= cA <= cB
    // check: N <= cB <= 1000

    return true;
}

int Jug::solve(string &solution) {
    solution = "";
    // set solution to default (none)
    for(Vertex* v : graph) {
        delete v;
    }
    graph.clear();
    // clear all previous attempts
    // check parameters in constructor
    // (done in solve so return values can be simplified)
    if(!parameterCheck()) {
        return -1;
    }

    // initialize pQueue (of all elements)
    // initialize visited Queue (used to rebuild path)
    priority_queue<Vertex*, vector<Vertex*>, CompareVertex> pQueue;
    // Vertex type, holding visited, compare means min-heap
    map<pair<int, int>, Vertex*> visited;  // visited pair (jugA, jugB)
    Vertex* start = new Vertex(0, 0, 0, "start", nullptr);
    graph.push_back(start);
    pQueue.push(start);
    visited[{0, 0}] = start;

    Vertex* final = nullptr;

    while(!pQueue.empty()) {
        // take locations from pQueue
        Vertex* curr = pQueue.top();
        pQueue.pop();
        // remove location from pQueue to signify visited

        // if found a cheaper path to this state, skip it
        if (curr->distance > visited[{curr->jugA, curr->jugB}]->distance) {
            continue;
        }

        // Check if we reached the goal state : curr->jugB = goal or N
        if(curr->jugA == 0 && curr->jugB == goal) {
            final = curr;
            break;  // Found the shortest path to the goal, can stop Dijkstra's
        }

        // option 1: fill A
        if(curr->jugA < capacityA) {
            int newA = capacityA;
            int newB = curr->jugB;
            int newDist = curr->distance + fillCostA;
            string action = "fill A";

            if (visited.find({newA, newB}) == visited.end() || newDist < visited[{newA, newB}]->distance) {
                // If it's a new state OR a cheaper path:
                Vertex* neighbor = new Vertex(newA, newB, newDist, action, curr);  // Create a new Vertex object for this state
                graph.push_back(neighbor);  // Add to our memory cleanup list
                pQueue.push(neighbor);  // Add this new state to the priority queue to be explored later
                visited[{newA, newB}] = neighbor;  // Store/update this state in the map with its new cheapest Vertex
            }
        }

        // Option 2: fill B
        if(curr->jugB < capacityB) {
            int newA = curr->jugA;
            int newB = capacityB;
            int newDist = curr->distance + fillCostB;
            string action = "fill B";
            if (visited.find({newA, newB}) == visited.end() || newDist < visited[{newA, newB}]->distance) {
                Vertex* neighbor = new Vertex(newA, newB, newDist, action, curr);
                graph.push_back(neighbor);
                pQueue.push(neighbor);
                visited[{newA, newB}] = neighbor;
            }
        }

        // Option 3: empty A
        if(curr->jugA > 0) {
            int newA = 0;
            int newB = curr->jugB;
            int newDist = curr->distance + emptyCostA;
            string action = "empty A";
            if (visited.find({newA, newB}) == visited.end() || newDist < visited[{newA, newB}]->distance) {
                Vertex* neighbor = new Vertex(newA, newB, newDist, action, curr);
                graph.push_back(neighbor);
                pQueue.push(neighbor);
                visited[{newA, newB}] = neighbor;
            }
        }

        // Option 4: empty B
        if(curr->jugB > 0) {
            int newA = curr->jugA;
            int newB = 0;
            int newDist = curr->distance + emptyCostB;
            string action = "empty B";
            if (visited.find({newA, newB}) == visited.end() || newDist < visited[{newA, newB}]->distance) {
                Vertex* neighbor = new Vertex(newA, newB, newDist, action, curr);
                graph.push_back(neighbor);
                pQueue.push(neighbor);
                visited[{newA, newB}] = neighbor;
            }
        }
        // Option 5: pour A into B
        if(curr->jugA > 0 && curr->jugB < capacityB) {
            int pourAmount = min(curr->jugA, capacityB - curr->jugB);
            int newA = curr->jugA - pourAmount;
            int newB = curr->jugB + pourAmount;
            int newDist = curr->distance + pourCostA;
            string action = "pour A B";
            if (visited.find({newA, newB}) == visited.end() || newDist < visited[{newA, newB}]->distance) {
                Vertex* neighbor = new Vertex(newA, newB, newDist, action, curr);
                graph.push_back(neighbor);
                pQueue.push(neighbor);
                visited[{newA, newB}] = neighbor;
            }
        }

        // Option 6: pour B into A
        if(curr->jugB > 0 && curr->jugA < capacityA) {
            int pourAmount = min(curr->jugB, capacityA - curr->jugA);
            int newA = curr->jugA + pourAmount;
            int newB = curr->jugB - pourAmount;
            int newDist = curr->distance + pourCostB;
            string action = "pour B A";
            if (visited.find({newA, newB}) == visited.end() || newDist < visited[{newA, newB}]->distance) {
                Vertex* neighbor = new Vertex(newA, newB, newDist, action, curr);
                graph.push_back(neighbor);
                pQueue.push(neighbor);
                visited[{newA, newB}] = neighbor;
            }
        }
    }
    // option 7: Success
    // check to see if final was reached
    // before starting path build
    if(final != nullptr) {
        list<string> path;
        Vertex* temp = final;
        // append all actions until start to path using prev pointer
        while(temp != nullptr && temp->action != "start") {
        path.push_front(temp->action);
        temp = temp->prev;
        }

        // prepare to print with stringstream
        stringstream oSS;
        for(const string& step : path) {
            oSS << step << std::endl;
        }
        oSS << "success " << final->distance;
        solution = oSS.str();
        return 1;
    } else {
        return 0;  // inputs valid but no solution
    }
    return 0;
}
