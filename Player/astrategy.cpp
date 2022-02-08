#include <astrategy.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


std::vector<Destination> AStrategy::pickDestination(std::vector<Destination> destination) {
    std::vector<Destination> result = {};

    if(destination.size() >= 2) {
        result.push_back(destination.at(0));
        result.push_back(destination.at(1));
    }
    else if(destination.size() == 1) {
        result.push_back(destination.at(0));
    }

    return result;
}


std::vector<Destination> AStrategy::pickDestinationA(std::vector<Destination> destinationSet, bool firstOrLast) {
    std::vector<Destination> sortedDests = destinationSet;
    // now sortedDests should be sorted

    // TODO: this doesnt even begin to run
    sort(sortedDests.begin(), sortedDests.end(), [this](const Destination& lhs, const Destination& rhs) {
        return lexigraphicCompDestinations(lhs, rhs);
    });

    int dest1Pos;
    int dest2Pos;

    if(firstOrLast) {
        dest1Pos = 0;
        dest2Pos = 1;
    }
    else {
        dest1Pos = sortedDests.size()-1;
        dest2Pos = sortedDests.size()-2;
    }

    std::vector<Destination> result = {};

    if(sortedDests.size() >= 2) {
        result = {sortedDests.at(dest1Pos), sortedDests.at(dest2Pos)};
    }
    else if(sortedDests.size() == 1) {
        result = {sortedDests.at(dest1Pos)};
    }
    else {
        throw std::invalid_argument("No Destinations to pick from");
    }
    return result;

}

// code should never get here
bool AStrategy::shouldRequestMoreCards() {
    return (rand() % 2) + 1 != 2;
}

DesiredMove AStrategy::takeTurn() {
    if(canBuyConnections()) {
        std::vector<Connection> result = {};
        result.push_back(whichConnectionToBuy());

        return DesiredMove(result);
    }
    else {
        return DesiredMove();
    }


}

bool AStrategy::canBuyConnections() {
    for(Connection c : player.GetAvailableConnections()) {
        if(player.GetHand().at(c.getColor()) >= c.getLength()
        && player.GetRails() >= c.getLength()) {
            return true;
        }
    }
    return false;
}

bool AStrategy::canBuyOneConnection(Connection c) {
    return player.GetHand().at(c.getColor()) >= c.getLength()
    && player.GetRails() >= c.getLength();
}

Connection AStrategy::whichConnectionToBuy() {
    std::vector<Connection> sortedCons = player.GetAvailableConnections();

    //now we sort sortedCons
    sort(sortedCons.begin(), sortedCons.end(), [this](const Connection& lhs, const Connection& rhs){
        return lexigraphicCompConnections(lhs, rhs);
    });

    if(sortedCons.size() == 0) {
        throw std::invalid_argument("No Connections available");
        // this should be calling for more cards, but we don't know how to communicate with the referee yet
    }
    else {
        for(Connection c : sortedCons) {
            if(canBuyOneConnection(c)) {
                return c;
            }
        }

        throw std::invalid_argument("no connections available pt 2");

    }

}

bool AStrategy::lexigraphicCompConnections(Connection a, Connection b) {
    if(a.getCities().first == b.getCities().first) {
        int comp = a.getCities().second.compare(b.getCities().second);
        if(comp < 0) {
            return true;
        }
        else if(comp > 0) {
            return false;
        }
        else {
            if(a.getLength() == b.getLength()) {
                if(a.getColor() < b.getColor()) {
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                if(a.getLength() < b.getLength()) {
                    return true;
                }
                else {
                    return false;
                }
            }
        }
    }
    else {
        if(a.getCities().first.compare(b.getCities().first) < 0) {
            return true;
        }
        else {
            return false;
        }
    }
}


bool AStrategy::lexigraphicCompDestinations(Destination a, Destination b) {
    int comp = a.getEndpointA().getName().compare(b.getEndpointA().getName());
    if(comp == 0) {
        int compb = a.getEndpointB().getName().compare(b.getEndpointB().getName());
        if(comp >= 0) {
            return false;
        }
        else {
            return true;
        }
    }
    else if(comp > 0) {
        return false;
    }
    else {
        return true;
    }
}

void AStrategy::AssignGameState(PlayerGS gamestate) {
    player = gamestate;
}

Map AStrategy::constructMap() {
    City a = {SDL_Point{0, 1}, "a"};
    City b = {SDL_Point{0, 2}, "b"};
    City c = {SDL_Point{0, 3}, "c"};
    City d = {SDL_Point{0, 4}, "d"};
    City e = {SDL_Point{0, 5}, "e"};

    Connection ab = {a.getName(), b.getName(), 3, red};
    Connection ac = {a.getName(), c.getName(), 5, green};

    Connection cd = {c.getName(), d.getName(), 4, blue};
    Connection de = {d.getName(), e.getName(), 3, white};

    std::vector<Connection> connections = {ab, ac, cd, de};

    a.AddConnection(ab);
    a.AddConnection(ac);
    c.AddConnection(cd);
    d.AddConnection(de);

    std::unordered_map<std::string, City> cities = {{a.getName(), a}, {b.getName(), b}, {c.getName(), c}, {d.getName(), d}, {e.getName(), e}};

    Map m = {100, 100, cities, connections};
    return m;
}