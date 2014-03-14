/** 
 *  Author: Duy Ngoc Le   - Anh Dang
 *  
 * 
 *  Date: September 2, 2013
 */


#include <vector>
#include <queue>

#include <limits>
#include "graphs.hpp"

using namespace::std;



/** This method uses the Dijkstra's algorithm to find the shortest 
 * path in the graph. It is used to calculate the total transmit 
 * time it takes to move between all pairs of computers in the 
 * minimum-cost network.
 */

int Graphs::FindShortestPath(int vIndex){

  // transmit time
  int trsTime = 0;

  // set all vertices distance to infinity
  int index = 0;
  while (index < vertexList.size()){ 
    vertexList[index] -> distance = numeric_limits<int>::max(); 
    index++;
  } 

  // set all the bool flag to false 
  int bIndex = 0; 
  while (bIndex < vertexList.size())
  {
    vertexList[bIndex]->alreadyChecked = false; 
    bIndex++;
  }

  // set initial vertex to first element in the vector
  Vertex* startVert = vertexList[vIndex]; 

  // set previous ptr to null
  startVert -> prevPtr = NULL;

  // set distance to 0
  startVert -> distance = 0; 

  // create a priority queue to add the edges around a vertex into it
  priority_queue <Edges, vector <Edges>, CompareEdgeTransitTime> myQueue;

  // mark the distance of the adjacent vertex as the transmitTime from 
  // startVert
  int eIndex = 0; 
  for (eIndex = 0 ;eIndex < startVert -> 
                                 ListEdgesAround.size();eIndex++)
  { 
    if (startVert ->stringName != 
          startVert->ListEdgesAround[eIndex].endVert->stringName) {
      // adjacent edge to the start vertex
      Edges adjEdge = startVert->ListEdgesAround[eIndex];

      // mark the distance of adj vertex as transmit Time
      adjEdge.endVert -> distance = 
       startVert->ListEdgesAround[eIndex].transmitTime; 

      // increment index of edgelist
    
      // enqueue all the edges to the priority queue
      myQueue.push(startVert -> ListEdgesAround[eIndex]); 
    }
  }
  // while priority queue is not empty
  while(myQueue.empty() != true)
  { 
    // the smallest edge from pqueue
    Edges edge = myQueue.top(); 

    // the adjacent vertex
    Vertex* adjVert = edge.endVert;

    // dequeue the smallest edge from pqueue
    myQueue.pop(); 

    // if the adjacent vertex is marked then skip the rest 
    if(adjVert -> alreadyChecked) 
      continue; 

    // add the smallest vertex's distance to time
    //cout << "distance " << adjVert->distance << endl;
    
    trsTime = trsTime + adjVert -> distance; 

    // mark the adjacent vertex as visited   
    adjVert -> alreadyChecked == true; 
    
    for (int i = 0; i < vertexList.size(); i++)
    {
      if (vertexList[i]->stringName == adjVert->stringName)
        vertexList[i]->alreadyChecked = true;
    }

    // looping through the edges around the vertex
    int eIndex; 
    for (eIndex = 0; eIndex < adjVert ->  
                                ListEdgesAround.size();eIndex++)
    { 
      if (edge.endVert->stringName != 
        edge.endVert->ListEdgesAround[eIndex].endVert ->stringName) {  
        // adjacent edge of the vertex
        Edges adjEdge = adjVert->ListEdgesAround[eIndex];   

        // calculate the best path cost
        int bestPathCost = adjEdge.transmitTime + adjVert->distance; 
      
        // if best path cost is smaller, make it the new distance
        if( adjEdge.endVert -> distance > bestPathCost)
        {         
          // make best path cost the new distance
          adjEdge.endVert->distance = bestPathCost; 

          // enqueue the adjacent edge
	  myQueue.push(adjEdge); 
        }
      } // closing while loop
    }
  } // closing the while myQueue not empty loop
  return trsTime; 
}


/** This method builds a minimum spanning tree 
 * for the given graph. This will be used to
 * calculate the total cost of the building
 * for the cheapest network.
 * */
Graphs* Graphs::minSpanTree()
{
  // reset all nodes to non visited
  int bIndex = 0;
  while (bIndex < vertexList.size())
  {
    vertexList[bIndex]->alreadyChecked = false; 
    bIndex++;
  }

   // create a new graph for spanning tree
   Graphs* spanGraph = new Graphs();


  // start spanning vertex
  Vertex* startVert = vertexList[0];

  // set pointer and boolean value
  startVert->prevPtr = NULL;
  startVert->alreadyChecked = true;


  // create a pqueue to hold edge, edge vector and cost compare class
  priority_queue<Edges, vector<Edges>, CompareEdgeCost> mySpanQueue;

  // enqueue to the priority queue
  int index = 0;
  while(index < startVert->ListEdgesAround.size())
  {
    mySpanQueue.push(startVert->ListEdgesAround[index]);
    index++;
  }


  // dequeue from pqueue
  while(mySpanQueue.empty() != true)
  {
    // save the top of the queue
    Edges edg = mySpanQueue.top();
    
    // dequeue shortest edge from the queue
    mySpanQueue.pop();

    // if end vert is visited then continue
    if( edg.endVert->alreadyChecked)
      continue;
      
    // set end vertex to visited 
    edg.endVert->alreadyChecked = true;

    // set prev of w to indicate v
    edg.endVert->prevPtr = edg.initVert;

    // create 2 vertices to make the edge for MST
    Vertex* initSpanVert = new Vertex(edg.initVert->stringName);
    Vertex* endSpanVert = new Vertex(edg.endVert->stringName);

    // set the ptr to existing vertex
    if ((spanGraph->containsVertex(initSpanVert->stringName))) 
      initSpanVert = spanGraph->getVertex(initSpanVert->stringName);
    
    // if vertex not on the graph, then add new one
    else 
      spanGraph->vertexList.push_back(initSpanVert);
    
    // else set ptr to existing vertex
    if ((spanGraph->containsVertex(endSpanVert->stringName))) 
      endSpanVert = spanGraph->getVertex(endSpanVert->stringName);

    // if vertex not on graph, then add new one
    else 
      spanGraph->vertexList.push_back(endSpanVert);
    
    // add the vertices
    initSpanVert->createEdge( endSpanVert, edg.edgeCost, edg.transmitTime);
    endSpanVert->createEdge( initSpanVert, edg.edgeCost, edg.transmitTime);

    // create w's adjacency list
    vector<Edges> wAdjList = edg.endVert->ListEdgesAround;

    // push each edge of w's adjacent list to queue
    int wIndex = 0;
    while (wIndex < wAdjList.size()){
      mySpanQueue.push(wAdjList[wIndex]);
      wIndex++;
    }
    
  }

  // return the minimum spanning tree
  return spanGraph;


}

/** This method is used to calculate the
 * total cost that are passed in as user
 * input. It does not have any parameters
 * and it returns an integer value.
 */
int Graphs::totalEdgeCost()
{
  // total cost
  int totalCost = 0;


  // looping through the list of vertices
  int index = 0;
  while (index < vertexList.size())
  {
    // looping through the list of edges for each vertex
    int vIndex = 0;
    while (vIndex < vertexList[index]->ListEdgesAround.size())
    {
      if(vertexList[index]->alreadyChecked == 
         vertexList[index]->ListEdgesAround[vIndex].endVert->alreadyChecked )
      { 
        // add the edges cost to totalCost
        totalCost += vertexList[index]->ListEdgesAround[vIndex].edgeCost;
      }
      vIndex++; 
    }

    // set the vertex bool to true
    vertexList[index]->alreadyChecked = true;

    // increment index
    index++; 
  }


  // return the total cost
  return totalCost;

}



/** This method is used to check if a vertex
 * already exists in the graph by comparing its
 * name with the names of all the vertices in the 
 * graph. It returns true or false depending on
 * whether the name is found or not.
 */

bool Graphs::containsVertex(string vertName)
{
  int index = 0;
  while (index < vertexList.size())
  {
    // check to see if the passed in name is
    // the same as the vertex's name
    if(vertexList[index]->stringName == vertName)
    {
      return true;
    }
    index++;
  }
  return false;
}

/** This method is used to get a vertex in the graph
 * which as the same name as the name being passed
 * into the parameter. It returns the vertex.
 */

Vertex* Graphs::getVertex(string vertName)
{
  int index = 0;
  while (index < vertexList.size())
  {
    // check to see if the passed in name is
    // the same as the vertex's name
    if(vertexList[index]->stringName == vertName)
    {
      return vertexList[index];
    }
    index++;
  }
  return NULL;
}


/** This is the destructor of this class. It is used
 * to destroy the graph when it is called. This is 
 * to prevent memory leaks from happening.
 */
Graphs::~Graphs()
{
  int index = 0;
  while (index < vertexList.size())
  { 
    // delete all the vertices in the vertex List
    delete vertexList[index];

    // increment index
    index++;
  }

}


