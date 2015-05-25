/*********************************************
* file:	~\tnd004\lab\lab4a\digraph.cpp       *
* remark: mplementation of directed graphs   *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "digraph.h"
#include "queue.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Digraph::Digraph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    dist  = new int [n + 1];
    path  = new int [n + 1];
    done  = new bool[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Digraph::~Digraph()
{
    delete[] array;
    delete[] dist;
    delete[] path;
    delete[] done;
}

// -- MEMBER FUNCTIONS

// insert directed edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Digraph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
}

// remove directed edge (u, v)
void Digraph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
}

// unweighted single source shortest paths
void Digraph::uwsssp(int s)
{

    // *** För mer om Queue, kolla denna totte:  https://www.youtube.com/watch?v=XuCbpw6Bj1U ***
    // Exempel på Fö.13

    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    // Create a queue with ints
    Queue<int> Q;

    // For all vertexes in list set dist to infinity and path to 0
    for(int i = 1; i <= size; ++i){

        // Set all other vertices distance to infinity
        i != s ? dist[i] = INFINITY : dist[i] = 0;
        path[i] = 0;

    }

    //std::cout << "ARR first" << array[1].getFirst()->vertex << std::endl;

    Q.enqueue(s);

    while(!Q.isEmpty()){

        // Get first element in queue and remove it
        int v = Q.getFront();
        Q.dequeue();

        // Get the pointer to the first neighbour node that holds the info about vertex, weight and next node
        Node* neighbour = array[v].getFirst();

        // for all neighbour vertices to v, calculate distance to "this" vertex and add this vertex to the neighbour vertex path,
        // also put the new vertex in our queue
        while(neighbour){

            std::cout << "Vertex number: " << v << " has neighbour vertex: " << neighbour->vertex << std::endl;

            // neighbour was never visited
            if(dist[neighbour->vertex] == INFINITY){

                // update distance
                dist[neighbour->vertex] = dist[v] + 1;
                // update path to store the vertex before
                path[neighbour->vertex] = v;

                // Must check the neighbour later
                Q.enqueue(neighbour->vertex);

            }

            // proceed to next neighbour (if any)
            neighbour = array[v].getNext();

        }

    }

}

// positive weighted single source shortest pats
void Digraph::pwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    // init
    for(int i = 1; i <= size; i++){

        dist[i] = INFINITY;
        path[i] = 0;
        done[i] = false;

    }

    dist[s] = 0;
    done[s] = true;

    // set start to current vertex
    int currentVertex = s;

    while(true){

        //int d = INFINITY;

        // Gets the first neighbour (if any)
        Node* neighbour = array[currentVertex].getFirst();

        // For all neighbours
        while(neighbour){

            std::cout << "Vertex number: " << currentVertex << " has neighbour vertex: " << neighbour->vertex << std::endl;

            // Update neighbour distance if better path (old distance plus new weight)
            if(!done[neighbour->vertex] && (dist[neighbour->vertex] > dist[currentVertex] + neighbour->weight)){

                std::cout << " dist neighbour vertex " << dist[neighbour->vertex] << "dist current vertex " << dist[currentVertex] << "weight " << neighbour->weight << std::endl;

                dist[neighbour->vertex] = dist[currentVertex] + neighbour->weight;
                path[neighbour->vertex] = currentVertex;

                //if (dist[neighbour->vertex] < d)
                //    d = neighbour->vertex;

            }


            neighbour = array[currentVertex].getNext();

        }

        done[currentVertex] = true;

        int d = INFINITY;

        // Find smallest undone distance vertex
        for(int i = 1; i <= size; i++){

            if(!done[i] && dist[i] < d){
                d = dist[i];
                currentVertex = i;
            }

        }

        if(d == INFINITY) break;

    }

}

// print graph
void Digraph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                  " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}

// print shortest path tree for s
void Digraph::printTree() const
{
    cout << "----------------------" << endl;
    cout << "vertex    dist    path" << endl;
    cout << "----------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " :" << setw(8) << dist[v] << setw(8) << path[v] << endl;
    }

    cout << "----------------------" << endl;
}

// print shortest path from s to t
void Digraph::printPath(int t) const
{

    if (t < 1 || t > size)
    {
         cout << "\nERROR: expected target t in range 1.." << size << " !" << endl;
         return;
    }

    if(path[t] == 0){
        std::cout << " " << t << " ";
        return;
    }

    printPath(path[t]);
    std::cout << " " << t << " ";

/*
    int nextVertex = path[t];
    int totalDist = 1;

    std::cout << node->vertex;

    if(path[t] == 0){
        std::cout << "(" + dist + ")";
        return;
    }*/


}
