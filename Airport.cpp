//
//  Airport.cpp
//  hw10
//
//  Created by Joshua Tran on 11/30/23.
//

#include "Airport.hpp"

Airport::Airport(){
    mVisited = false; 
};

Airport::Airport(const std::string code, double x, double y){
    mCode = code;
    mX = x;
    mY = y;
    mVisited = false;
};

std::string Airport::getCode(){
    return mCode;
}

double Airport::getX(){
    return mX;
}

double Airport::getY(){
    return mY;
}
Airport::~Airport() {
    // Clean up the dynamically allocated GraphEdge objects in the adjacency list
    for (GraphEdge* edge : mAdjacencyList) {
        delete edge;
    }
    // Clear the vector after deleting the objects to prevent dangling pointers
    mAdjacencyList.clear();
}

