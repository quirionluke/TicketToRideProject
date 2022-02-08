#ifndef REFEREE_HPP
#define REFEREE_HPP

#include <referee-game-state.hpp>
#include <player.hpp>
#include <map>
#include <config.hpp>


/*
    This is the Referee class, which represents the rules and single general game manager 
        -RefereeGS gameState --> what the referee 'sees' and can manipulate as the manager of the game
        -map<Player, PlayerGS> players --> a map of the Player individual's to their respective gamestates, 
            -the player's get sent their gamestates at the start of their turn
*/
class Referee {
    RefereeGS refGameState;
    std::map<Player, PlayerGS*> playerData;
    std::vector<Player> kickedPlayers;
    bool gameOver;


public:

    Referee(RefereeGS refGameStatex) : refGameState(refGameStatex) {
        refGameState = refGameStatex;
        playerData = {};
        kickedPlayers = {};
        gameOver = false;
    }

    Referee(std::vector<Player> players, Map map) : refGameState(&map) {
        this->refGameState = {&map};
        for(Player p : players) {
            PlayerGS* adding = {};
            refGameState.AddPlayerToGame(adding);
            playerData.insert(std::pair<Player, PlayerGS*>{p, adding});
        }
        kickedPlayers = {};
        gameOver = false;
    }

    // TODO: check if the players given are the same as those in the gamestate
    Referee(RefereeGS refGameStatex, std::vector<Player> players) : refGameState(refGameStatex) {
        refGameState = refGameStatex;
        for(Player p : players) {

            PlayerGS* adding = new PlayerGS();
            refGameState.AddPlayerToGame(adding);
            std::pair<Player, PlayerGS*> addingPair{p, adding};
            playerData.insert(addingPair);
        }
        kickedPlayers = {};
        gameOver = false;
    }

    ~Referee() {

    }


    /*
        hands out all of the rails and cards and makes the players choose their Destinations
    */
    Referee* setupGame();


    /*
        returns the pair of Player to PlayerGS whos turn it is according to the refGameState
    */
    Player whosTurnIsItAnyways();


    /*
        returns true if the given player can buy the Connection they ask for or draw more cards
            -basically the player is just kind of request that their gamestate be changed to what is different in movepair
                -it is important to check that a player does not ask for both, as that is an invalid move
    */
    bool validatePlayerMove(Player player, DesiredMove move);


    /*
        updates the given Player's gamestate according to the given pair of Connection vector and bool
    */
    void applyPlayerMove(Player player, DesiredMove move);

    /*
        at the end of the game, return the highest scoring player
    */
    Player getWinner();

    /*
        returns true if the game is over
    */
    bool isGameOver();

    /*
        returns true if any player's rails drops below END_PHASE_RAIL_NUM
    */
    bool isEndPhase();

    /*
        handles the last turn that everyone has
    */
    void endPhase();


    /*
        returns the player ranking, with the person who won at index 0
    */
    std::vector<Player> findRanking();
    
    /*
        kicks the given player out of the turn order and frees up their owned connections for later use
    */
    void eliminatePlayer(Player player);

    /*
        adds a random card from the deck to the player's hand
    */
    void dealRandomCardTo(Player player);

    /*
        returns the score number of the given player
    */
    int calculateScore(Player player);

    /*
        runs a game by having each player take their turn and returns the resulting ref object
    */
    Referee* runGame();

    /*
        returns a random color card from the deck
    */
    Color drawRandomCardWeighted();
    Color drawRandomCard();

    /*
        Gets all cheaters for the game this Referee is overseeing
    */
    std::vector<Player> getCheaters();

    // getters exclusively for unit tests
    std::map<Player, PlayerGS*> GetPlayerData();
    RefereeGS GetRefGS();


};


#endif