#ifndef ASTRATEGY_HPP
#define ASTRATEGY_HPP


#include <player-game-state.hpp>
#include <istrategy.hpp>
#include <algorithm>

/*
    Strategy is a parent class and represents how the player AI's make their moves
        -player: the PlayerGS for this player
            Default Strategy follows the rules:
                -Picks the first Destination that they were handed
                -Requests more cards 50% of the time
                -Purchases the first available Connection they see
*/
class AStrategy: public IStrategy {
protected:
    bool firstOrLast;

public:

    AStrategy() {
        player = {};
    }

    AStrategy(PlayerGS playerx) {
        player = playerx;
    }

    ~AStrategy() {

    }


    virtual std::vector<Destination> pickDestination(std::vector<Destination> destination);


    // returns the destination that the player should be moving toward
    std::vector<Destination> pickDestinationA(std::vector<Destination> destinationSet, bool firstOrLast);

    // takes the player's turn and returns their move that they wanna make
    virtual DesiredMove takeTurn();

    // returns true if the player should request more cards, false otherwise
    bool shouldRequestMoreCards();

    // returns true if the player can buy any available Connections, false otherwise
    bool canBuyConnections();

    bool canBuyOneConnection(Connection c);

    // returns true if Connection a comes before Connection b in name
    // if equal, then in length, if equal, then in color
    // returns false otherwise
    bool lexigraphicCompConnections(Connection a, Connection b);

    // returns true if a comes before b alphabetically
    // if they are the same, returns false
    bool lexigraphicCompDestinations(Destination a, Destination b);

    // if buying a Connection, determines which available connection to purchase
    Connection whichConnectionToBuy();

    // assigns the given gamestate to this strategy
    void AssignGameState(PlayerGS player);

    // constructs a map to submit at beginning of tournament
    // using default method for now for testing purposes
    // in the future if any strategy has map design specifications it can override this method
    virtual Map constructMap();
};

#endif