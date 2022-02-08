#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <player.hpp>
#include <referee.hpp>
#include <config.hpp>

/*
    This represents the tournament manager, or one who can run multiple games with recurring Players, and return a ranking:
        - refs: a vector of Referee's who can run the games
        - activePlayers: a vector of Players who are available to participate in the games
        - kickedPlayers: a vector of Players who have been kicked from games during the tournament
        - winners: the Player(s) who have won the tournament

*/

class Manager {

    // TODO: these may have to be pointers to avoid copying a bunch of data but im not sure yet
    std::vector<Referee*> refs;
    std::vector<Player> activePlayers;
    std::vector<Player> kickedPlayers;
    std::vector<Player> winners;
public:
    Manager() {
        refs = {};
        activePlayers = {};
        kickedPlayers = {};
        winners = {};
    }

    Manager(std::vector<Player> players) {
        refs = {};
        activePlayers = players;
        kickedPlayers = {};
        winners = {};
    }

    // run the current tournament (round by round recursively) by running games and assigning remaining players to new games
    // needs to first get map submissions from players
    void runTournament(Map tournamentMap, std::vector<Player> roundPlayers);

    // divides players into games with the maximum amount of players per game possible
    // also updates the refs field to contain all created referees
    void dividePlayersIntoGames(Map tournamentMap, std::vector<Player> roundPlayers, int numPlayersPerGame);

    // notifies all players that the tournament is about to begin and collect their Map subissions
    // then picks a map and calls runTournament with those maps and players
    void beginTournamentAndGetMap();
    
    // lets every player know that the tournament is about to start and receive their Map submissions
    std::vector<Map> getPlayerMapSubmissions();

    // selects one Map to use for all tournament games
    Map pickMap(std::vector<Map> mapOptions);

    // runs a game with the assigned players and Map and returns the created Referee (that is also added to refs) 
    Referee* createGame(std::vector<Player> players, Map theMap);

    // returns all cheating players for the given Referee's game //TODO maybe keep track of kicked players in Referee too so we can just access them?
    std::vector<Player> getCheaters(Referee ref);

    // returns the ranking of Players for the given Referee's game after it is over
    std::vector<Player> getGameRanking(Referee ref);

    // ends the current tourtnament and notifies players on their winner / loser status
    // this method must automatically be called when two tournament rounds return the same result
    void endTournament();


    //getters for tests
    std::vector<Referee*> getRefs();
    std::vector<Player> getActivePlayers();
    std::vector<Player> getKickedPlayers();
    std::vector<Player> getWinners();

};

#endif