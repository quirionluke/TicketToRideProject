#ifndef CITY_HPP
#define CITY_HPP


#include <SDL2/SDL.h>
#include <cstdlib>
#include <Connection.hpp>
#include <algorithm>
#include <iostream>
#include <vector>


/*
    City represents a city on the map
        -pos: the position of the City (in pixels) on the map
            -the map checks if the position is valid
        -name: a string representing the name of the city
        -outbound: a vector of Connection objects representing all of the Connections this City belongs to
*/
class City {

    SDL_Point pos;
    std::string name;
    std::vector<Connection> outbound;

public:

    City() {
        pos = {0,0};
        name = "";
        outbound ={};
    }

    City(SDL_Point posx, std::string namex) {
        pos = posx;
        name = namex;
        outbound = {};
    };

    City(SDL_Point posx, std::string namex, std::vector<Connection> outboundx) {
        pos = posx;
        name = namex;
        outbound = {};
    };

    ~City() {

    };


    // getters
    SDL_Point getPosn();
    std::string getName();
    std::vector<Connection> getOutbound();

    // adds the given connection to the outbound list
    void AddConnection(Connection c);

    // overriding the equality operator
    bool operator==(const City& lhs) const;
};





#endif