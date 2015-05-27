/*********************************************
* file:	~\tnd004\lab\lab4b\graph.h           *
* remark:implementation of undirected graphs *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>

using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Graph::Graph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Graph::~Graph()
{
    delete[] array;
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
    array[v].insert(u, w);
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
    array[v].remove(u);
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const
{

    assert(size > 1);

    int source = 1, totalWeight = 0;

    // Declared on the heap b/c we dont have a constant size of the array (vector should also be fine)
    std::vector<Edge> edges; // Always one edge less than nr of nodes
    bool* done = new bool[size];
    int* path = new int[size];
    int* dist = new int[size];

    // init
    for(int i = 1; i <= size; i++){

        i != source ? dist[i] = INFINITY : dist[i] = 0;
        i != source ? done[i] = false : done[i] = false;
        path[i] = 0;

    }

    while(true){

        Node* neighbour = array[source].getFirst();

        while(neighbour){

            // update distance of each neighbour if better edge
            if(!done[neighbour->vertex] && dist[neighbour->vertex] > neighbour->weight){

                dist[neighbour->vertex] = neighbour->weight;
                path[neighbour->vertex] = source;

            }


            neighbour = array[source].getNext();

        }

        done[source] = true;

        // Find smallest undone distance vertex
        int d = INFINITY;

        for(int i = 1; i <= size; i++){

            if(!done[i] && dist[i] < d){
                d = dist[i];
                source = i;
            }

        }

        // All neighbour nodes have already been visited
        if(d == INFINITY) break;

        //std::cout << "** Inserting edge: (" << source << ", " << path[source] << ", " << dist[source] << ") " << std::endl;

        // Push every edge into a vector
        edges.push_back(Edge(source, path[source], dist[source]));

    }

    // Print all edges
    for(int i = 0; i < edges.size(); i++){

        std::cout << edges.at(i) << std::endl;
        totalWeight += edges.at(i).weight;

    }

    std::cout << "\nTotal weight = " << totalWeight << std::endl;

    delete[] done;
    delete[] path;
    delete[] dist;

}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{
    // Här: https://www.youtube.com/watch?v=71UQH7Pr9kU

    Heap<Edge> H;
    DSets D(size);
    bool* done = new bool[size];
    int source = 1, totalWeight = 0;

    for(int i = 1; i <= size; i++){
        done[i] = false;
    }

    // Build heap with all edges
    for(int i = 1; i <= size; i++){

        Node* neighbour = array[i].getFirst();
        //std::cout << "** Node " << i << " has neighbour " << neighbour->vertex << std::endl;

        while(neighbour){

            if(!done[neighbour->vertex]){
                H.insert(Edge(i, neighbour->vertex, neighbour->weight));
            }

            neighbour = array[i].getNext();

        }

        done[i] = true;

    }

    delete[] done;

    // Debug tree
    /*for(int i = 0; i < 12; i++){

        std::cout << H.deleteMin() << std::endl;

    }*/

    int counter = 0;

    // Increase counter until we have reached n - 1 edges
    while(counter < size - 1){

        Edge e = H.deleteMin();

        //std::cout << "** Edge " << e << " deleted from tree" << std::endl;

        // If the edge doesn't exist in the disjoint set (no cycles), insert. (we always find the minimum edges first)
        if(D.find(e.head) != D.find(e.tail)){

            //std::cout << "OK, edge inserted " << e << std::endl;
            D.join(D.find(e.head), D.find(e.tail));

            //std::cout << "Disjointset is now " << std::endl;
            D.print();
            std::cout << e << std::endl;
            totalWeight += e.weight;

            counter++;

        }

    }

    std:cout << "\nTotal weight = " << totalWeight << std::endl;

}

// print graph
void Graph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                                            " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}
