#include <map.hpp>
#include <player-game-state.hpp>

/*
    This is the referee's gamestate, which controls legal moves and who's turn it is
        - playerTurnOrder: vector of Player gamestates (ordered by turn order)
        - unownedCons: vector of unowned Connections
        - board: a reference to the map object 
        - currentPlayer: the index of the player who's turn it currently is
            - this can be thought of like a "player 1" "player 2" kind of thing
        - deck: the colored cards remaining in the deck
*/

// the RefereeGS represents an organized way for the referee to 
// keep track of the players and the overall state of the game
class RefereeGS {
    
    std::vector<PlayerGS*> playerTurnOrder;
    std::vector<Connection> unownedCons;
    Map* board;
    uint currentPlayer;

    std::unordered_map<Color, int, ColorHash> deck;

public:
    
    /*
    RefereeGS() {
        throw std::invalid_argument("Tried to create a RefereeGS with no board");
    }
    */
    

    RefereeGS(const RefereeGS& other) {
        playerTurnOrder = other.playerTurnOrder;
        unownedCons = other.unownedCons;
        board = other.board;
        currentPlayer = other.currentPlayer;
        deck = other.deck;

    }

    RefereeGS(Map* currentMapx) {
        playerTurnOrder = {};
        board = currentMapx;
        unownedCons = {};

        for(Connection c : board->getConnections()) {
            unownedCons.push_back(c);
        }

        UpdateUnownedConnections();

        currentPlayer = 0;

        deck = {};
    }

    // the referee should be created before the players are, and it should only be constructed once at the start of the game
    // we also assume no connections are owned at the start of the game
    RefereeGS(std::vector<PlayerGS*> playerTurnOrderx, Map* currentMapx) {
        playerTurnOrder = playerTurnOrderx;
        board = currentMapx;

        unownedCons = {};

        for(Connection c : board->getConnections()) {
            unownedCons.push_back(c);
        }

        UpdateUnownedConnections();

        currentPlayer = 0;

        deck = {};

    };

    RefereeGS(Map* currentMap, std::unordered_map<Color, int, ColorHash> deckx) {
        playerTurnOrder = {};
        board = currentMap;
        unownedCons = {};
        for(Connection c : board->getConnections()) {
            unownedCons.push_back(c);
        }

        UpdateUnownedConnections();

        currentPlayer = 0;
        deck = deckx;
    }

    // we need to destroy the vector we made because we use 'new'
    ~RefereeGS() {
    };


    /*
    // puts all of the cards that need to be in the deck into the deck
    //std::unordered_map<Color, int> InitializeDeck();
    */

    // set the currentPlayer to the next player in the turn order
    void NextPlayersTurn();

    // updates the available connections in each player so they know what is available
    // needs to be called after updateing the referee's unowned Connections
    void UpdateUnownedConnections();

    // adds the given player to the turn order (this new player will go last)    
    void AddPlayerToGame(PlayerGS* player);

    // return the PlayerGS for the given player
    PlayerGS* GetPlayer(uint ind);

    // checks if it is legal for the given PlayerGS to purchase the given Connection
    bool canPlayerBuy(PlayerGS player, Connection con);

    // add the given connection to the given PlayerGS's owned connections
    void GivePlayerCon(PlayerGS* player, Connection con);

    // add the given card to the given player's hand
    void GivePlayerCard(PlayerGS* player, Color c);

    // getters
    std::vector<PlayerGS*> GetTurnOrder();
    PlayerGS* GetCurrentPlayer();
    std::vector<Connection> GetUnownedCons();
    Map* GetBoard() const;
    std::unordered_map<Color, int, ColorHash> GetDeck();
    int GetNumCardsInDeck();

    // setters 
    void SetTurnOrder(std::vector<PlayerGS*> players);
    void SetBoard(Map* boardx);
    void SetCurrentPlayer(uint ind);
    void SetDeck(std::unordered_map<Color, int, ColorHash> decks);

};
