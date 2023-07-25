#ifndef _JUG_H
#define _JUG_H_
#include <iostream>
#include <vector>
#include <climits>
#include <string>
#include <list>
using namespace std;

struct Vertex
{
public:
    pair<int, int> state;
    pair<int, int> neighbor[6];
    string label;
    int distance;
    string color;
    Vertex *prev;

    Vertex()
    {
        label = "";
        distance = INT_MAX;
        color = "white";
        prev = nullptr;
    }
};

class Jug
{
public:
    Jug(int, int, int, int, int, int, int, int, int);
    ~Jug();

    // solve is used to check input and find the solution if one exists
    // returns -1 if invalid inputs. solution set to empty string.
    // returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
    // returns 1 if solution is found and stores solution steps in solution string.
    int solve(string &solution);

private:
    vector<Vertex> adjList;
    int capacityA, capacityB;
    int goal;
    int costA, costB, costAB, costBA, costEmptyA, costEmptyB;

    // helper functions
    void pourAtoB(Vertex &);
    void pourBtoA(Vertex &);
    void emptyA(Vertex &);
    void emptyB(Vertex &);
    int locateVertex(Vertex &);
    void fillA(Vertex &);
    void fillB(Vertex &);
    void graph(vector<Vertex> &);
    bool solutionFound(Vertex &);
    void solutionPath();
};

#endif