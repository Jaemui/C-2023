//
//  main.cpp
//  hw10
//
//  Created by Joshua Tran on 11/30/23.
//

#include "main.hpp"
#include <iostream>
#include <fstream>
#include "ITPSimpleGraph.hpp"

//Function for reading in the file and creating the graph
ITPSimpleGraph createAirportGraph(){
    ITPSimpleGraph airportGraph;
    std::ifstream file("/Users/joshtran/ITP 365/hw10/hw10/data.txt");
    if (file.is_open()){
        while (!file.eof()){
            std::string line;
            std::getline(file, line);
            //if the line begins with a for airpor,create an airport node
            if (line.substr(0,1) == "a"){
                std::string code = line.substr(8,3);
                double x = std::stod(line.substr(12,5));
                double y = std::stod(line.substr(17));
                airportGraph.createNode(code, x, y);
            }
            //if the line isnt an airport, create an edge and add it to the corresponding airports frequency list.
            else if (line.substr(0,1) == "f"){
                std::string from = line.substr(7,3);
                std::string to = line.substr(11, 3);
                double cost = std::stod(line.substr(15));
                airportGraph.createEdge(from, to, cost);
            }
        }
    }
    airportGraph.addPathInfo();
    
    return airportGraph;
}

int main(){
    //initializing the graph
    ITPSimpleGraph airportGraph = createAirportGraph();
    
    int choice = 0;
    
    while (choice != -1){
        std::cout << "0. List the Airport Codes" << std::endl;
        std::cout << "1. Show all the Connected Airports" << std::endl;
        std::cout << "2. Find all destinations from one airport" <<std::endl;
        std::cout << "3. List the cheapest flight in the country" <<std::endl;
        std::cout << "4. Find all rountrips from one airport" <<std::endl;
        std::cout << "5. Find the cheapest flights from A to B" << std::endl;
        std::cout << "-1. Exit" <<std::endl;
        
        std::cout << "Pick an option: ";
        std::cin >> choice;
        //check choice validity
        if (std::cin.fail()) {
            std::cin.clear();
            //get rid of empty space from the lines
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch(choice){
            case 0:
                airportGraph.listCodes();
                break;
            case 1:
                airportGraph.showConnected();
                break;
            case 2:
            {
                std::string airport;
                std::cout << "Select an airport to depart from: ";
                std::cin >> airport;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                airportGraph.showFlightsFromAirport(airport);
            }
                break;
            case 3:
                airportGraph.cheapestFlights();
                break;
            case 4:
            {
                std::string rtAirport;
                std::cout << "Select an airport to epart from: ";
                std::cin >> rtAirport;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                airportGraph.roundTrip(rtAirport);
            }
                break;
            case 5:
            {
                Path cheapestPath;
                std::string departureAirport;
                std::string destinationAirport;
                std::cout << "Select the airport you are leaving from: ";
                std:: cin >> departureAirport;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Select the airport you are traveling to: ";
                std::cin >> destinationAirport;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cheapestPath = airportGraph.cheapestPath(departureAirport, destinationAirport);
                std::cout << "The cheapest path from " << departureAirport << " to " << destinationAirport << ": " <<std::endl;
                for (std::string stops : cheapestPath.airports){
                    std::cout << stops << " - ";
                }
                std::cout << "Total cost of trip: $" << cheapestPath.cost << std::endl;
            }
                break;
            case -1:
                break;
        }
    }
}

