/** 
 *  Author: Duy Ngoc Le   - Anh Dang
 *  
 *  
 *  Date: September 7, 2013
 */

#ifndef GRAPHS_HPP
#define GRAPHS_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include "vertex.hpp"
#include <queue>

using namespace::std;




/** This class will constructed the graph for the netplan.
 * It will include the Dijkstra's algorithm to find
 * the shortest (time) path from one point to the other.
 * It will also include the minimum spanning tree
 * algorithm.
 */

class Graphs
{
  private:

  public:

  vector<Vertex*> vertexList;      // list of all vertices


  /** This is the constructor that is used to make the graphs
   * for the netplan.
   */

  Graphs(){}

 /** This method builds a minimum spanning tree 
  * for the given graph. This will be used to
  * calculate the total cost of the building
  * for the cheapest network.
  * */
  Graphs* minSpanTree();            


 /** This method uses the Dijkstra's algorithm to find the shortest 
  * path in the graph. It is used to calculate the total transmit 
  * time it takes to move between all pairs of computers in the 
  * minimum-cost network.
  */
  int FindShortestPath(int index);


 /** This method is used to check if a vertex
  * already exists in the graph by comparing its
  * name with the names of all the vertices in the 
  * graph. It returns true or false depending on
  * whether the name is found or not.
  */
  bool containsVertex(string vName);


 /** This method is used to get a vertex in the graph
  * which as the same name as the name being passed
  * into the parameter. It returns the vertex.
  */
  Vertex* getVertex(string vName);


 /** This is the destructor of this class. It is used
  * to destroy the graph when it is called. This is 
  * to prevent memory leaks from happening.
  */
  ~Graphs();


 /** This method is used to calculate the
  * total cost that are passed in as user
  * input. It does not have any parameters
  * and it returns an integer value.
  */
  int totalEdgeCost();


  
};

/** This class is used to compare the transmit time of the edges. 
 * It will return true if the trasmit time of the fist
 * edge is larger than the transmit time of the second edge.
 * */

class CompareEdgeTransitTime
{
  public:
    bool operator() (Edges e1, Edges e2)
    {
      if (e1.transmitTime > e2.transmitTime)
        return true;
      else return false;
    }
};

/** This class is used to compare the cost of the edges. 
 * It will return true if the cost of the first edge is
 * larger than the cost of the second edge.
 * */
class CompareEdgeCost
{
  public:
    bool operator() (Edges e1, Edges e2)
    {
      if (e1.edgeCost > e2.edgeCost)
        return true;
      else return false;
    }


};

#endif // GRAPHS_HPP

