//
//  Airport.hpp
//  hw10
//
//  Created by Joshua Tran on 11/30/23.
//

#pragma once
#include <vector>
#include <string>
#include "Flight.hpp"
#include "ITPSimpleGraph.hpp"

//declaring the class beforehand since it is used in the structs below
class Airport;

struct PathInfo {
    // Name of destination
    std::string mAirport;
    // cost to get to destination
    double mCost;
    // Constructor
    PathInfo(const std::string& name); 
    PathInfo(const std::string& name, const double cost) {
    mAirport = name;
    mCost = cost;
    }
};

struct GraphEdge {
    //cost of the travel
    double mCost;
    //destination node
    Airport* mOtherNode;
};

class Airport{
public:
    //Constructor
    Airport();
    Airport(const std::string code, double x, double y);
    //destructor
    ~Airport();
    
    //functions
    std::string getCode();
    double getX();
    double getY();
    
    
public:
    //member variables
    
    std::string mCode;
    double mX;
    double mY;
    bool mVisited;
    std::vector<PathInfo> mPath;
    std::vector<GraphEdge*> mAdjacencyList;
    double mPathCost;
    Airport* mPrevNode; 
};

struct Path
{
    //list of airports
    std::vector<std::string> airports;
    // the total cost of the Path
    double cost;
};

class ITPSimpleGraph {
public:
    // Default constructor
    ITPSimpleGraph();
    // Destructor
    ~ITPSimpleGraph();
    // Creates a node
    // Note: Errors if node already exists
    void createNode(const std::string& name, double x, double y);
    // Returns a pointer to the node with the requested name
    // Note: Errors if node does not exist
    Airport* getNode(const std::string& name);
    // Create an undirected edge between the two named nodes
    // Note: Errors if neither node exists
    // Note 2: Doesn't check if an edge already exists between the nodes
    void createEdge(const std::string& from, const std::string& to, double cost);
    // checks to see if the nodeMap contains node
    bool containsNode(const std::string& name) const;
    //resets the visited nodes
    void clearIsVisited();
    //destructor
    void deleteNode(Airport* node);
    //lists all airport codes
    void listCodes();
    //shows all the connected airports
    void showConnected();
    //adds path info to the mPath
    void addPathInfo();
    //show all destinations from a given airport
    void showFlightsFromAirport(const std::string& airportCode);
    //find the cheapest flight
    void cheapestFlights();
    //show all the roundtrip flights from a given airport
    void roundTrip(const std::string&);
    //find the cheapest path from a given airport to another airport 
    Path cheapestPath(const std::string&, const std::string&);


public:
    // No copy/assignment (rule of three!)
    ITPSimpleGraph(const ITPSimpleGraph& other);
    ITPSimpleGraph& operator=(const ITPSimpleGraph& other);
    // Hash map of all of the nodes in the graph
    std::unordered_map<std::string, Airport*> mNodeMap;
};
