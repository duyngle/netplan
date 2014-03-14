/** 
 *  Author: Duy Ngoc Le    - Anh Dang
 *   
 *  
 *  Date: September 7, 2013
 */

#include "string.h"
#include "graphs.hpp"
using namespace std;

int main (int argc, char *argv[]) {

  // regular graph and minimum spanning tree
  Graphs* testGraph  = new Graphs();
  Graphs* testGraph_opt = new Graphs();

  // first computer and second computer
  string first_col = ""; 
  string second_col = "";

  // cost and time
  int cost = 0, time = 0;

  // optimal cost and optimal time
  int opt_cost = 0, opt_time=0;

  // normal time and normal cost
  int normal_time = 0, normal_cost = 0;

  if (argc !=2) {
    cout << " The program require two argument strictly\n";
    return -1;
  }

  // input file 
  ifstream infile;

  // reading the input file
  infile.open(argv[1]);

  while (infile.good()) {

    // read file and save the information into the variables
    infile >> first_col; 
    infile >> second_col; 
    infile >> cost; 
    infile >> time;

    // creating the start vertex and end vertex
    Vertex *initVert = new Vertex (first_col);

    Vertex *endVert = new Vertex (second_col);

    // if vertex already on the graph, set the vertex pointer
    if (testGraph ->containsVertex (first_col))
       initVert = testGraph->getVertex(first_col); 

    // if not on the graph, then add it on
    else
      testGraph->vertexList.push_back(initVert);

    // if vertex already on the graph, set the vertex pointer
    if (testGraph ->containsVertex (second_col))
      endVert = testGraph->getVertex(second_col);

    // if not on the graph, then add it on
    else
      testGraph->vertexList.push_back(endVert);

    // create the edge for start vertex and end vertex
    initVert -> createEdge (endVert, cost, time);
    endVert -> createEdge (initVert, cost, time);
  }

    // closing the input file
    infile.close();

    // calculate the normal total cost of building all links
    normal_cost = testGraph->totalEdgeCost();
    cout <<normal_cost <<endl;

    // creating a minimum spanning tree
    testGraph_opt = testGraph->minSpanTree();
 
    // print out the total cost of the cheapest network from MST
    opt_cost = testGraph_opt ->totalEdgeCost();
    cout <<opt_cost<<endl;

    // print out the diffeence between the normal cost and optimal cost
    cout <<normal_cost - opt_cost<<endl;

    // looping through the list of vertices
    for (int i=0; i< testGraph->vertexList.size(); i++)
    {    
      normal_time = normal_time + testGraph->FindShortestPath(i);
    }

    // printing out the total time to send a packet in regular network
    cout <<normal_time << endl;

    // looping through the vertexList to find the time it takes
    // to send a packet in a minimum cost network
    for (int i=0; i< testGraph->vertexList.size(); i++)
    {
      opt_time = opt_time + testGraph_opt -> FindShortestPath(i);
    }

    // printing out the optimal time
    cout << opt_time<<endl;

    // printing out the difference between regular network and cheap one
    cout << opt_time - normal_time << endl;

    // delete the 2 graphs to free memory (memory leak avoidance)
    delete testGraph;
    delete testGraph_opt;
}



