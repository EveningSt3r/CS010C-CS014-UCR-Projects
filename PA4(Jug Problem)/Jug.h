#pragma once

#include <iostream>
#include <string>
#include <list>
#include <vector>

using std::string;
using std::pair;
using std::vector;
using std::list;



struct Vertex {
    int jugA;
    int jugB;
    int distance;
    string action;
    Vertex* prev;
    // d serves as infinite value as default in Djikstra
    // previous vertex allows us to rebuild path
    Vertex(int a = 0, int b = 0, int d = 9999, string act = "", Vertex* p = nullptr)
    : jugA(a), jugB(b), distance(d), action(act), prev(p) {}
    
    // ~Vertex(); Jug class handles destruction
};

class Jug {
    public:
        Jug(int,int,int,int,int,int,int,int,int);
        ~Jug();
        Jug(const Jug&) = delete;
        Jug& operator=(const Jug&) = delete;

        //solve is used to check input and find the solution if one exists
        //returns -1 if invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string &solution);
    private:
        int capacityA;
        int capacityB;
        int goal;
        int fillCostA;
        int fillCostB;
        int emptyCostA;
        int emptyCostB;
        int pourCostA;
        int pourCostB;
        bool parameterCheck();
        list<Vertex*> graph;

};