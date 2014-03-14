/** 
 *  Author: Duy Ngoc Le   - Anh Dang
 *   
 *  
 *  Date: September 7, 2013
 */

#ifndef EDGES_HPP
#define EDGES_HPP

#include <iostream>
#include <fstream>
#include <vector>

using namespace::std;

class Vertex;


/** This class will constructed the edges for the graph.
 * The edge class will hold a pointer to the start vertex,
 * a pointer to the end vertex, the cost, and the transmit
 * time variables.
 */

class Edges
{

  private:
   
  public:


    Vertex *initVert;     // initial vertex of the edge
    Vertex *endVert;      // end vertex of the edge
    int edgeCost;         // cost value of the edge
    int transmitTime;     // transmit time of the edge


    /** This is the constructor that is used to make the edges
     * for the graph. It takes in a initial vertex, end vertex, 
     * cost of the edge and transmit time
     */

    Edges (Vertex *initVert, Vertex *endVert, int edgeCost, int transmitTime)
    { 
      // initialize the variables
      this->initVert = initVert; 
      this->endVert = endVert; 
      this->transmitTime = transmitTime; 
      this->edgeCost = edgeCost; 
    } 

 
};

#endif // EDGES_HPP












