//
//  ITPSimpleGraph.cpp
//  hw10
//
//  Created by Joshua Tran on 12/4/23.
//

#include "ITPSimpleGraph.hpp"
#include "Airport.hpp"
#include <iostream>
#include <queue>
#include <unordered_set>

//Constructor
ITPSimpleGraph::ITPSimpleGraph(){}

//Creates a node in the nodeMap
void ITPSimpleGraph::createNode(const std::string& name, double x, double y) {
    // 1. If the node already exists, error!
    if (mNodeMap.contains(name)){
        std::cout << ("Can't create two Aiports with the same name!") <<std::endl;
    }
    // 2. Dynamically allocate a new node
    Airport* node = new Airport;
    // 3. Set its name
    node->mCode = name;
    node->mX = x;
    node->mY = y; 
    // 4. Insert the node into the node map
    mNodeMap.emplace(name, node);
}

//gets a node from nodeMap from string input
Airport* ITPSimpleGraph::getNode(const std::string& name)
{
    // 1. If the node doesn't exist, error!
    if (!mNodeMap.contains(name))
    {
        std::cout<<("Requested Airport doesn't exist!") <<std::endl;
    }
    // 2. Return the node pointer
    return mNodeMap[name];
}

void ITPSimpleGraph::createEdge(const std::string& from, const std::string& to, double cost)
{
    // 1. Get the from node
    Airport* fromNode = getNode(from);
    // 2. Get the second node
    Airport* toNode = getNode(to);
    // 3. Add a connection from->to
    GraphEdge* firstEdge = new GraphEdge();
    firstEdge->mOtherNode = toNode;
    firstEdge->mCost = cost;
    fromNode->mAdjacencyList.push_back(firstEdge);
    
}

bool ITPSimpleGraph::containsNode(const std::string& name) const
{
    return mNodeMap.find(name) != mNodeMap.end();
}

void ITPSimpleGraph::listCodes(){
    std::cout << "Airport Codes: " << std::endl;
    for (const auto& entry : mNodeMap) {
        std::cout << "Codes: " << entry.second->getCode() <<std::endl;
    }
}

void ITPSimpleGraph::addPathInfo(){
    //iterate through every node and their adjacency list to create path list
    for (const auto& entry: mNodeMap){
        Airport* currentNode = entry.second;
        for (GraphEdge* edge : currentNode->mAdjacencyList) {
            currentNode->mPath.push_back(PathInfo(edge->mOtherNode->getCode(), edge->mCost));
        }
    }
}

void ITPSimpleGraph::showConnected(){
    for (const auto &entry : mNodeMap) {
        Airport *currentAirport = entry.second;
        
        if (!currentAirport->mVisited) {
            std::cout << "Connected Airports: ";
            std::queue<Airport *> bfsQ;
            bfsQ.push(currentAirport);

            while (!bfsQ.empty()) {
                Airport *currentNode = bfsQ.front();
                bfsQ.pop();
                
                //print out the currentNode if it has not been visited
                if (!currentNode->mVisited) {
                    currentNode->mVisited = true;
                    std::cout << currentNode->getCode() << " ";
                    
                    //for every node in the currentNode's adjacencylsit, add it to the queue
                    for (GraphEdge *edge : currentNode->mAdjacencyList) {
                        Airport *adjacentNode = edge->mOtherNode;
                        if (!adjacentNode->mVisited) {
                            bfsQ.push(adjacentNode);
                        }
                    }
                }
            }
            std::cout << "\n";
        }
    }
    clearIsVisited();
}

void ITPSimpleGraph::showFlightsFromAirport(const std::string& airportCode){
    if (containsNode(airportCode)) {
        Airport* from = getNode(airportCode);
        std::cout << "Destinations from " << from->getCode() << ":" << std::endl;
        
        for (PathInfo destination : from->mPath){
            std::cout << "- " <<destination.mAirport << ": $" << destination.mCost <<std::endl;
        }
    } else {
        std::cout << "Airport not found" << std::endl;
    }
}

void ITPSimpleGraph::cheapestFlights(){
    //set high price to compare to
    double cheapestFlightPrice = 100000;
    std::string cheapestFlightFrom = "";
    std::string cheapestFlightTo = "";
    //compare every airport and all their departures and prices
    for (const auto& entry : mNodeMap){
        for (GraphEdge* edge : entry.second->mAdjacencyList){
            if (edge->mCost < cheapestFlightPrice){
                cheapestFlightPrice = edge->mCost;
                cheapestFlightFrom = entry.second->getCode();
                cheapestFlightTo = edge->mOtherNode->getCode();
            }
        }
    }
    std::cout << "The Cheapest Flight is from " << cheapestFlightFrom << " to " << cheapestFlightTo << " for $" << cheapestFlightPrice << std::endl;
    clearIsVisited();
}

void ITPSimpleGraph::roundTrip(const std::string& airportCode){
    if (containsNode(airportCode)) {
        std::cout << "Here are the available round trip options from " << airportCode << ": " << std::endl;
        Airport* from = getNode(airportCode);
        for (GraphEdge* edge: from->mAdjacencyList){
            for (GraphEdge* returns : edge->mOtherNode->mAdjacencyList){
                if (returns->mOtherNode->getCode() == from->getCode()){
                    std::cout << edge->mOtherNode->getCode() << ", $" << edge->mCost << std::endl;
                }
            }
        }
    }else{
        std::cout << "Airport not found" <<std::endl;
    }
    clearIsVisited();
}

Path ITPSimpleGraph::cheapestPath(const std::string& from, const std::string& to) {
    //use Djikstra's algorithm 
    //input check
    if (!containsNode(from) || !containsNode(to)) {
            std::cout << "Error: One or both of the specified airports do not exist." << std::endl;
            return Path();
        }
    // initialize nodes
    Airport* start = getNode(from);
    Airport* end = getNode(to);
    //initialize queue
    std::priority_queue<std::pair<double, Airport*>> pq;
    //set your starting node as first in queue with 0 cost since you travel nowhere
    start->mPathCost = 0;
    pq.push({0, start});

    while (!pq.empty()) {

        Airport* currentNode = pq.top().second;
        double currentCost = pq.top().first;
        pq.pop();

        //when reaching destination
        if (currentNode == end) {
            Path bestPath;
            bestPath.airports.push_back(currentNode->mCode);
            
            while (currentNode->mPrevNode != nullptr){
                bestPath.airports.push_back(currentNode->mPrevNode->mCode);
                currentNode = currentNode->mPrevNode;
            }
            
            std::reverse(bestPath.airports.begin(), bestPath.airports.end());
            bestPath.cost = currentCost;
            clearIsVisited();
            return bestPath;
        }
        
        //for every edge in the current Node adjacency list, go down the path and compare costs.

        for (GraphEdge* edge : currentNode->mAdjacencyList) {
            if (!edge->mOtherNode->mVisited) {
                double newCost = currentCost + edge->mCost;
                if (newCost < edge->mOtherNode->mPathCost || edge->mOtherNode->mPrevNode == nullptr) {
                    edge->mOtherNode->mPathCost = newCost;
                    edge->mOtherNode->mPrevNode = currentNode;
                    pq.push({newCost, edge->mOtherNode});
                }
            }
        }


        currentNode->mVisited = true;
    }
    clearIsVisited();
    //if there is no path
    return Path();
}


// Destructor
ITPSimpleGraph::~ITPSimpleGraph() {
    for (const auto& entry : mNodeMap){
//        entry.second->mAdjacencyList.clear();
        delete (entry.second);
    }
}

void ITPSimpleGraph::clearIsVisited() {
    for (const auto& entry : mNodeMap) {
        entry.second->mVisited = false;
//        entry.second->mPath.clear();

        // Reset additional attributes for path-finding
        entry.second->mPathCost = std::numeric_limits<double>::infinity();
        entry.second->mPrevNode = nullptr;
    }
}
