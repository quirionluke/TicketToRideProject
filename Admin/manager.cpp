#include <manager.hpp>
#include <random>

// ran after receiving players, this method collects map submissions from players, picks one,
// then creates games and runs them
void Manager::runTournament(Map tournamentMap, std::vector<Player> roundPlayers) {
    dividePlayersIntoGames(tournamentMap, roundPlayers, MAX_NUM_PLAYERS);
    std::vector<Player> roundWinners = {};
    // run each game and add the round winners to the "winners" field
    for (Referee* roundRef: refs) {
        roundRef->runGame();
        std::vector<Player> refRankings = roundRef->findRanking();
        roundWinners.push_back(roundRef->findRanking()[0]);
    }  

    roundPlayers = roundWinners;

    // sorts and checks if the winners of this round are the same as last round
    std::sort(roundWinners.begin(), roundWinners.end());
    std::sort(winners.begin(), winners.end());
    if (roundWinners == winners) {
        endTournament();
    }

    // check to see if final game needs to be played, 
    // otherwise set activePlayers to winners and winners to an empty list before recursive call
    if (winners.size() <= MAX_NUM_PLAYERS) {
        Referee finalGameRef = *createGame(roundPlayers, tournamentMap);
        finalGameRef = *finalGameRef.runGame();
        // since in the final game, all surviving (aka all non-eliminated) players share the reward
        winners = finalGameRef.findRanking();
        endTournament();
    }
    else {
        winners = roundPlayers;
        runTournament(tournamentMap, roundPlayers);
    }
}

void Manager::beginTournamentAndGetMap() {
    std::vector<Map> mapSubmissions = getPlayerMapSubmissions();
    Map tournamentMap = pickMap(mapSubmissions);
    runTournament(tournamentMap, activePlayers);
}


// sorts the given players into however many games they can be in before creating the associated Referees with the Map
void Manager::dividePlayersIntoGames(Map tournamentMap, std::vector<Player> roundPlayers, int numPlayersPerGame) {
    std::vector<Player> unnassignedPlayers = roundPlayers;
    int numUnnassignedPlayers = unnassignedPlayers.size();

    int remainingPlayersWithMaxPerGame = numUnnassignedPlayers % numPlayersPerGame;

    if (numUnnassignedPlayers > MAX_NUM_PLAYERS) {
        auto first = unnassignedPlayers.cbegin() + 0;
        auto last = unnassignedPlayers.cbegin() + numPlayersPerGame;
        std::vector<Player> gameList(first, last);

        numUnnassignedPlayers = numUnnassignedPlayers - numPlayersPerGame;
        if (remainingPlayersWithMaxPerGame < MIN_NUM_PLAYERS) {
            std::vector<Player> remainingPlayers = gameList;
            remainingPlayers.insert(remainingPlayers.end(), unnassignedPlayers.begin(), unnassignedPlayers.end());
            dividePlayersIntoGames(tournamentMap, remainingPlayers, numPlayersPerGame-1);
        }
        else { // otherwise add the new referee to refs and move on with loop
            auto updatedFirst = unnassignedPlayers.cbegin() + numPlayersPerGame;
            auto updatedLast = unnassignedPlayers.cbegin() + unnassignedPlayers.size() - 1;
            std::vector<Player> updatedUnnassigned(updatedFirst, updatedLast);
            Referee* ref = createGame(gameList, tournamentMap);
            refs.push_back(ref);
            dividePlayersIntoGames(tournamentMap, updatedUnnassigned, numPlayersPerGame);
        }
    }
}

std::vector<Map> Manager::getPlayerMapSubmissions() {
    std::vector<Map> playerMapSubmissions = {};
    for (Player p: activePlayers) {
        Map pmap = p.start();
        playerMapSubmissions.push_back(pmap);
    }
    return playerMapSubmissions;
}

Map Manager::pickMap(std::vector<Map> mapOptions) {
    int theIndex = 0 + ( std::rand() % ( mapOptions.size() - 0 + 1 ) );
    return mapOptions.at(theIndex);
}

Referee* Manager::createGame(std::vector<Player> players, Map theMap) {
    Referee theRef = {players, theMap};
    Referee* result = theRef.setupGame();
    refs.push_back(result);
    return result;
}

std::vector<Player> Manager::getCheaters(Referee ref) {
    return ref.getCheaters();
}

std::vector<Player> Manager::getGameRanking(Referee ref) {
    return ref.findRanking();
}

void Manager::endTournament() {
    for (Player winner : winners) {
        winner.end(true);
    }
    for (Player loser : kickedPlayers) {
        loser.end(false);
    }
}


// getters beyond this point
std::vector<Referee*> Manager::getRefs() {
    return refs;
}
std::vector<Player> Manager::getActivePlayers() {
    return activePlayers;
}
std::vector<Player> Manager::getKickedPlayers() {
    return kickedPlayers;
}
std::vector<Player> Manager::getWinners() {
    return winners;
} 