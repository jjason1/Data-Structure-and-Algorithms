#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <queue>
#include <stack>

#include "Jug.h"
using namespace std;

Jug::Jug(int Ca, int Cb, int N, int cFA, int cFB, int cEA, int cEB, int cAB, int cBA)
{
    capacityA = Ca;
    capacityB = Cb;
    goal = N;
    costA = cFA;
    costB = cFB;
    costEmptyA = cEA;
    costEmptyB = cEB;
    costAB = cAB;
    costBA = cBA;

    if (!(Ca > 0 && Ca <= Cb) || !(Cb > goal && Cb <= 1000))
    {
        return; // Returns if the capacity constraints are not satisfied
    }

    if (cFA < 0 || cFB < 0 || cEA < 0 || cEB < 0 || cAB < 0 || cBA < 0)
    {
        return; // Returns if any cost is negative
    }

    graph(adjList); // Constructs the graph
}

Jug::~Jug()
{
}

void Jug::fillA(Vertex &v)
{
    v.state.first = capacityA; // Fills jug A to its maximum capacity
    return;
}

void Jug::fillB(Vertex &v)
{
    v.state.second = capacityB; // Fills jug B to its maximum capacity
    return;
}

void Jug::emptyA(Vertex &v)
{
    v.state.first = 0; // Empties jug A
    return;
}

void Jug::emptyB(Vertex &v)
{
    v.state.second = 0; // Empties jug B
    return;
}

void Jug::pourAtoB(Vertex &v)
{
    while (v.state.first != 0)
    {
        if (v.state.second == capacityB)
        {
            return; // Returns if jug B is already at its maximum capacity
        }
        v.state.first--; // Pours from jug A to jug B
        v.state.second++;
    }
    return;
}

void Jug::pourBtoA(Vertex &v)
{
    while (v.state.second != 0)
    {
        if (v.state.second == capacityB)
        {
            return; // Returns if jug A is already at its maximum capacity
        }
        v.state.second--; // Pours from jug B to jug A
        v.state.first++;
    }
    return;
}

void Jug::graph(vector<Vertex> &vertex)
{
    Vertex v;
    Vertex curr;
    vertex.push_back(v); // Adds the initial state to the list of vertices

    for (unsigned i = 0; i < vertex.size(); i++)
    {
        curr = vertex.at(i);
        Vertex v1 = curr;
        Vertex v2 = curr;
        Vertex v3 = curr;
        Vertex v4 = curr;
        Vertex v5 = curr;
        Vertex v6 = curr;

        fillA(v1); // Fills jug A
        fillB(v2); // Fills jug B
        emptyA(v3); // Empties jug A
        emptyB(v4); // Empties jug B
        pourAtoB(v5); // Pours from jug A to jug B
        pourBtoA(v6); // Pours from jug B to jug A

        if (!solutionFound(v1))
        {
            vertex.push_back(v1); // Adds the new state to the list of vertices if it is not already found
        }

        if (!solutionFound(v2))
        {
            vertex.push_back(v2);
        }

        if (!solutionFound(v3))
        {
            vertex.push_back(v3);
        }

        if (!solutionFound(v4))
        {
            vertex.push_back(v4);
        }

        if (!solutionFound(v5))
        {
            vertex.push_back(v5);
        }

        if (!solutionFound(v6))
        {
            vertex.push_back(v6);
        }

        curr.neighbor[0] = pair<int, int>(locateVertex(v1), costA); // Updates the neighbor and cost for filling A
        curr.neighbor[1] = pair<int, int>(locateVertex(v2), costB); // Updates the neighbor and cost for filling B
        curr.neighbor[2] = pair<int, int>(locateVertex(v3), costEmptyA); // Updates the neighbor and cost for emptying A
        curr.neighbor[3] = pair<int, int>(locateVertex(v4), costEmptyB); // Updates the neighbor and cost for emptying B
        curr.neighbor[4] = pair<int, int>(locateVertex(v5), costAB); // Updates the neighbor and cost for pouring A to B
        curr.neighbor[5] = pair<int, int>(locateVertex(v6), costBA); // Updates the neighbor and cost for pouring B to A

        vertex.at(i) = curr;
    }
}

int Jug::locateVertex(Vertex &v)
{
    for (unsigned i = 0; i < adjList.size(); i++)
    {
        if (adjList.at(i).state.first == v.state.first && adjList.at(i).state.second == v.state.second)
        {
            return i; // Returns the index of the vertex if the state is already in the graph
        }
    }
    return -1; // Returns -1 if the state is not found in the graph
}

bool Jug::solutionFound(Vertex &v)
{
    for (unsigned i = 0; i < adjList.size(); ++i)
    {
        if (adjList.at(i).state.first == v.state.first && adjList.at(i).state.second == v.state.second)
        {
            return true; // Returns true if the state is found in the graph
        }
    }
    return false; // Returns false if the state is not found in the graph
}

void Jug::solutionPath()
{
    queue<Vertex *> unQ;
    for (unsigned i = 0; i < adjList.size(); ++i)
    {
        adjList.at(i).distance = INT_MAX;
        adjList.at(i).prev = 0;
        unQ.push(&adjList.at(i));
    }
    adjList.at(0).distance = 0; // Sets the distance of the initial state to 0

    while (!unQ.empty())
    {
        Vertex *curr = unQ.front();
        unQ.pop();

        for (unsigned i = 0; i < 6; ++i)
        {
            int edgeW = curr->neighbor[i].second; // Retrieves the cost of the edge
            int alt = curr->distance + edgeW; // Calculates the alternative distance

            int A = curr->neighbor[i].first; // Retrieves the index of the neighbor vertex
            if (alt < adjList.at(A).distance)
            {
                adjList.at(A).distance = alt; // Updates the distance if the alternative distance is smaller
                adjList.at(A).prev = curr; // Updates the previous vertex
            }
        }
    }
}

int Jug::solve(string &path)
{
    stringstream ss;

    if (costA < 0 || costB < 0 || costEmptyA < 0 || costEmptyB < 0 || costAB < 0 || costBA < 0)
    {
        path = "";
        return -1; // Returns -1 if any cost is negative
    }

    if (capacityA <= 0 || capacityB <= 0 || capacityA > capacityB)
    {
        path = "";
        return -1; // Returns -1 if the capacity constraints are not satisfied
    }

    if (goal > capacityB || capacityB > 1000 || goal > 1000)
    {
        path = "";
        return -1; // Returns -1 if the goal or capacity exceeds the limits
    }

    int index = 0;
    bool indexAssigned = false;
    for (unsigned i = 0; i < adjList.size(); ++i)
    {
        if (adjList.at(i).state.first == 0 && adjList.at(i).state.second == goal)
        {
            index = i;
            indexAssigned = true;
        }
    }

    if (!indexAssigned)
    {
        path = "";
        return 0; // Returns 0 if the solution index is not assigned
    }

    solutionPath();

    stack<Vertex *> s;
    Vertex *curr = &adjList.at(index);

    while (curr != 0)
    {
        s.push(curr);
        curr = curr->prev;
    }

    while (s.size() - 1 != 0)
    {
        curr = s.top();
        s.pop();

        Vertex *prev = s.top();

        if (&adjList.at(curr->neighbor[0].first) == prev)
        {
            ss << "fill A" << endl; // Appends "fill A" to the solution path
        }

        if (&adjList.at(curr->neighbor[1].first) == prev)
        {
            ss << "fill B" << endl; // Appends "fill B" to the solution path
        }

        if (&adjList.at(curr->neighbor[2].first) == prev)
        {
            ss << "empty A" << endl; // Appends "empty A" to the solution path
        }

        if (&adjList.at(curr->neighbor[3].first) == prev)
        {
            ss << "empty B" << endl; // Appends "empty B" to the solution path
        }

        if (&adjList.at(curr->neighbor[4].first) == prev)
        {
            ss << "pour A B" << endl; // Appends "pour A B" to the solution path
        }

        if (&adjList.at(curr->neighbor[5].first) == prev)
        {
            ss << "pour B A" << endl; // Appends "pour B A" to the solution path
        }
    }

    ss << "success " << adjList.at(index).distance;
    path = ss.str(); // Sets the solution path and distance

    return 1; // Returns 1 indicating success
}