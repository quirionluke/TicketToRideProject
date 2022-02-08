#include <map.hpp>

void Map::buildTrainLines() {

    // check if all the given cities are valid
    for(std::pair<std::string, City> cityPair : cities) {
        if(cityPair.second.getPosn().x >= width
        || cityPair.second.getPosn().y >= height){
            throw std::invalid_argument("City out of bounds of map");
        }
    }
    

    // now we need to set outbound for each city
    for(Connection c : connections) {
        try{
            City* a = &cities.at(c.getCities().first);
            City* b = &cities.at(c.getCities().second);

            a->AddConnection(c);
            b->AddConnection(c);

        }
        catch(std::out_of_range) {
            throw std::invalid_argument("Connection between nonexistant Cities");
        }
    }

}

std::vector<Destination> Map::getAllDestinations() {
    std::vector<Destination> result = {};

 
    if(cities.size() == 0) {
        return result;
    }

    // this does bfs for each city
    for(std::pair<std::string, City> currcit : cities) {

        std::vector<City> visited;
        std::vector<City> toProcess;

        City source = currcit.second;
        toProcess.push_back(source);
        visited.push_back(source);

        // puts all possible end destinations into a vector
        while(!toProcess.empty()) {
            City processing;
            processing = toProcess.back();
            toProcess.pop_back();

            // looks at all of the neighbors of the node we are processing
            for(Connection c : processing.getOutbound()) {
                City nbor;
                if(processing.getName() != c.getCities().first) {
                    nbor = cities.at(c.getCities().first);
                }
                else {
                    nbor = cities.at(c.getCities().second);
                }

                // if nbor has already been visited, then we ignore it
                std::vector<City>::iterator it;
                it = find(visited.begin(), visited.end(), nbor);

                if(it != visited.end()) {
                    continue;
                }
                
                toProcess.push_back(nbor);
                visited.push_back(nbor);
            }
        }

        // create destinations and add them to result
        // these destinations will have start at source and end at
        // each of the visited cities
        for(City cityx : visited) {
            if(cityx.getName() != source.getName()) {
                Destination adding{source, cityx};

                std::vector<Destination>::iterator it;
                it = find(result.begin(), result.end(), adding);

                if(it != result.end()) {
                    continue;
                }
                result.push_back(adding);
            }
        }
    }

    destinations = result;

    return result;
}

// a helper method that translates the string into a Color enum
// definition of Color is in Connection.hpp
Color Map::ColorStrTranslator(std::string str) {

    if(str == "red") {
        return red;
    }
    else if(str == "blue") {
        return blue;
    }
    else if(str == "green") {
        return green;
    }
    else if(str == "white") {
        return white;
    }
    else {
        throw std::invalid_argument("invalid color given");

    }
}


// helper method that parses through the cities in a json
std::pair<std::string, City> CityParser(json_object* val, int i) {
    json_object* currCity = json_object_array_get_idx(val, i);
    //std::cout << json_object_to_json_string_ext(currCity, JSON_C_TO_STRING_PRETTY) << std::endl;
    std::string str;
    str = json_object_get_string(json_object_array_get_idx(currCity, 0));
    
    
    json_object* currpos = json_object_array_get_idx(currCity, 1);

    int x = json_object_get_int(json_object_array_get_idx(currpos, 0));
    int y = json_object_get_int(json_object_array_get_idx(currpos, 1));
    SDL_Point pnt;
    pnt = {x,y};
    
    City adding;
    adding = {pnt, str};

    std::pair<std::string, City> pairc;
    pairc = {adding.getName(), adding};
    return pairc;
}

/*
// helper method that parses through the connections in a json
void ConnectionParser(json_object* val, std::vector<Connection> &givenConnections) {
    std::string cityA;
    std::string cityB;
    unsigned int length;

    int len = json_object_array_length(val);

    // parse through the given connections
    // and take the cities, lengths, and colors
    // then translate them into our object types
    for(int i = 0; i < len; ++i) {
        json_object* arrval = json_object_array_get_idx(val, i);
        json_object_object_foreach(arrval, key, val) {
            cityA = key;
            json_object* target = val;
            json_object_object_foreach(target, key, val) {
                cityB = key;
                json_object* segment = val;
                json_object_object_foreach(segment, key, val) {
                    length = json_object_get_int(val);
                    Color colr = ColorStrTranslator(std::string(key));
                    Connection adding{cityA, cityB, length, colr};
                    givenConnections.push_back(adding);

                }
            }
        }
    }
}
*/

std::pair<SDL_Point, SDL_Point> Map::findPosOfConnection(Connection c) {
    SDL_Point firstp;
    std::string nameOfPrevProcessed = "";
    SDL_Point secondp;
    for(std::pair<std::string, City> p : cities) {
        if(p.first == c.getCities().first || p.first == c.getCities().second) {
            if(nameOfPrevProcessed.empty()) {
                firstp = p.second.getPosn();
                nameOfPrevProcessed = p.first;
            }
            else {
                secondp = p.second.getPosn();
                break;
            }
        }
    }

    return std::pair<SDL_Point, SDL_Point>{firstp, secondp};
}


void Map::jsonToMap(json_object* jobj) {
    cities = {};
    connections = {};

    json_object_object_foreach(jobj, key, val) {
        std::string strkey(key);

        if(strkey == "width") {
            width = json_object_get_int(val);
        }
        else if(strkey == "height") {
            height = json_object_get_int(val);
        }
        else if(strkey == "cities") {

            for(int i = 0; i < json_object_array_length(val); ++i) {

                cities.insert(CityParser(val, i));

                
            }
        }
        else if(strkey == "connections") {
            std::string cityA;
            std::string cityB;
            unsigned int length;

            json_object* value;
            value = val;

            // parse through the given connections
            // and take the cities, lengths, and colors
            // then translate them into our object types
            json_object_object_foreach(value, key, val) {
                cityA = key;
                json_object* target = val;
                json_object_object_foreach(target, key, val) {
                    cityB = key;
                    json_object* segment = val;
                    json_object_object_foreach(segment, key, val) {
                        length = json_object_get_int(val);
                        Color colr = ColorStrTranslator(key);
                        Connection adding{cityA, cityB, length, colr};
                        connections.push_back(adding);
                    }
                }
            }
        }
    }
}

bool Map::operator==(const Map& lhs) {
    return width == lhs.width
    && height == lhs.height
    && cities == lhs.cities
    && connections == lhs.connections;
}


uint Map::getWidth() {
    return width;
}

uint Map::getHeight() {
    return height;
}

std::unordered_map<std::string, City> Map::getCities() {
    return cities;
}

std::vector<Connection> Map::getConnections() {
    return connections;
}

std::vector<Destination> Map::getDestinations() {
    return destinations;
}