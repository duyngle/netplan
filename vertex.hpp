/** 
 *  Author: Duy Ngoc Le   - Anh Dang
 *   
 *  
 *  Date: September 7, 2013
 */

#ifndef VERTEX_HPP
#define VERTEX_HPP
#include "edges.hpp"

#include <iostream>
#include <fstream>
#include <vector>


/** This class will constructed the edges for the graph.
 * 
 */

class Vertex
{

  private:
   
  
  public:
    
    int distance;                  // distance to the next vertex
    Vertex *prevPtr;               // pointer to previous vertex
    bool alreadyChecked;           // check if the node is visited
    string stringName;             // name of the node
    vector<Edges> ListEdgesAround; // list of edges going from the vertex


    /** This is the constructor that is used to make the vertex 
     * for the graph. It takes in a string parameter.
     */

    Vertex (string stringName)
    {
      // when created, set checked bool to false
      alreadyChecked = false;

      // set the name
      this->stringName = stringName; 
    } 


    /** This method is used to create an edge between
     * an intial vertex, and end vertex. It will take in
     * the end vertex, as well as cost and time as 
     * parameters. It does not return anything.
     */
    void createEdge (Vertex *endV, int edgeCost, int tTime)
    {
      // create an edge with 'this' as the start vertex 
      // and endV as the end vertex
      Edges *edgeCreated = new Edges(this, endV, edgeCost, tTime);

      int flag = 0; // flag for duplicate

      // check for duplicates
      int index = 0;
      while (index < ListEdgesAround.size())
      {
        Edges edge1 = ListEdgesAround[index];

        // check to see if end vertices are the same
        if(edgeCreated->endVert == edge1.endVert)
          flag = 1;
       
        // increments index
        index++;
      }

      // if duplicate detected then ignore it
      if (flag==0)
        ListEdgesAround.push_back(*edgeCreated);
    }
 
};

#endif // VERTEX_HPP

