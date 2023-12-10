//
//  ITPSimpleGraph.hpp
//  hw10
//
//  Created by Joshua Tran on 12/4/23.
//

#pragma once
#include <vector>
#include <string>
#include "Airport.hpp"

//class Airport;
//struct Path;
//
//class ITPSimpleGraph {
//public:
//    // Default constructor
//    ITPSimpleGraph();
//    // Destructor
//    ~ITPSimpleGraph();
//    // Creates a node
//    // Note: Errors if node already exists
//    void createNode(const std::string& name, double x, double y);
//    // Returns a pointer to the node with the requested name
//    // Note: Errors if node does not exist
//    Airport* getNode(const std::string& name);
//    // Create an undirected edge between the two named nodes
//    // Note: Errors if neither node exists
//    // Note 2: Doesn't check if an edge already exists between the nodes
//    void createEdge(const std::string& from, const std::string& to, double cost);
//    
//    bool containsNode(const std::string& name) const;
//    void clearIsVisited();
//    void deleteNode(Airport* node);
//    
//    void listCodes();
//    void showConnected();
//    void addPathInfo();
//    void showFlightsFromAirport(const std::string& airportCode);
//    void cheapestFlights();
//    void roundTrip(const std::string&);
//    Path cheapestPath(const std::string&, const std::string&);
//    
//
//public:
//    // No copy/assignment (rule of three!)
//    ITPSimpleGraph(const ITPSimpleGraph& other);
//    ITPSimpleGraph& operator=(const ITPSimpleGraph& other);
//    // Hash map of all of the nodes in the graph
//    std::unordered_map<std::string, Airport*> mNodeMap;
//};
