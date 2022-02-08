#ifndef MAP_HPP
#define MAP_HPP

#include <SDL2/SDL.h>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <json-c/json.h>
#include <vector>

#include <City.hpp>
#include <Connection.hpp>
#include <Destination.hpp>


/*
    Map represents the board that the game takes place on
        -width: the width of the board in pixels
        -height: the height of the board in pixels
        -cities: an unordered_map of cities, with the keys being their name and the value being the city
            -it is assumed that the given City objects' outbound is empty
        -connections: a vector of all of the Connections
*/
class Map {
    uint width;
    uint height;
    std::unordered_map<std::string, City> cities;
    std::vector<Connection> connections;
    std::vector<Destination> destinations;

public:
    Map(uint widthx, uint heightx, std::unordered_map<std::string, City> citiesx, std::vector<Connection> connectionsx) {
        width = widthx;
        height = heightx;
        cities = citiesx;
        connections = connectionsx;
        destinations = {};
        buildTrainLines();
    }

    Map(json_object* jobj) {
        jsonToMap(jobj);
        destinations = {};
        buildTrainLines();
    }

    ~Map() {
                
    }

    // getters
    uint getWidth();
    uint getHeight();
    std::unordered_map<std::string, City> getCities();
    std::vector<Connection> getConnections();
    std::vector<Destination> getDestinations();

    // helper method that assigns all of the City's their outbound connections
    void buildTrainLines();

    Color ColorStrTranslator(std::string str);

    // returns all feasible destinations from connections using BFS
    std::vector<Destination> getAllDestinations();

    // converts a well formated json object to a Map object with all the relavent information
    void jsonToMap(json_object* jobj);

    // returns both positions of the cities in a given connections
    std::pair<SDL_Point, SDL_Point> findPosOfConnection(Connection c);

    bool operator==(const Map& lhs);




};





#endif