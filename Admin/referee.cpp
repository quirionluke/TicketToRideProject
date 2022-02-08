#include <referee.hpp>


// this is an EXTREMELY temporary method for just getting a random card
// we will replace this with the weighted method below but that is a low priority
Color Referee::drawRandomCard() {

    if(refGameState.GetNumCardsInDeck() <= 0) {
        throw std::invalid_argument("no cards to draw from");
    }

    // this sucks so bad, yall
    for(std::pair<Color, int> c : refGameState.GetDeck()) {
        if(c.second > 0) {
            return c.first;
        }
    }



    // check if there are any cards of the one we randomly selected
    throw std::invalid_argument("no cards to draw from");

}


/*
// this method doesnt really work
Color Referee::drawRandomCardWeighted() {

    int totalCards = refGameState.GetNumCardsInDeck();
    int sumOfWeights = 0;

    if(totalCards == 0) {
        throw std::invalid_argument("no cards to draw from");
    }

    for(std::pair<Color, int> p : refGameState.GetDeck()) {
        double probability = (double)p.second/totalCards;
        int percentage = probability*100;
        sumOfWeights += percentage;
    }


    int rnd = rand() % sumOfWeights;

    for(std::pair<Color, int> p : refGameState.GetDeck()) {
        int choiceWeight = ((int)((double)p.second/totalCards)*100);
        if(rnd < choiceWeight) {
            // remove the card from the deck and return it
            refGameState.GetDeck().at(p.first)--;
            return p.first;
        }
        rnd -= choiceWeight;
    }

    throw std::invalid_argument("the code should not get here when picking cards");
}
*/

void Referee::dealRandomCardTo(Player player) {
    Color c = drawRandomCard();
    playerData.at(player)->takeCard(c);    
}


Referee* Referee::setupGame() {
    std::vector<Destination> allDests = refGameState.GetBoard()->getDestinations();
    for(std::pair<Player, PlayerGS*> p : playerData) {

        // give them their rails
        p.second->SetRails((int)STARTING_RAILS);
        

        // give them their hands
        for(int i = 0; i < STARTING_CARDS; ++i) {
            dealRandomCardTo(p.first);
        }

        // let them pick their Destinations
        std::vector<Destination> dests = p.first.pickDestinations(allDests);

        p.second->SetDestinations(dests);

        // remove the selected Destinations from the list of available Destinations
        for(Destination d : dests) {
            allDests.erase(std::remove(allDests.begin(), allDests.end(), d), allDests.end());
        }
    }

    refGameState.UpdateUnownedConnections();
    return this;
}

Player Referee::whosTurnIsItAnyways() {
    PlayerGS* currPlayer = refGameState.GetCurrentPlayer();

    for(std::pair<Player, PlayerGS*> p : playerData) {
        if(p.second == currPlayer) {
            return p.first;
        }
    }

    throw std::invalid_argument("there is no current player");
}

bool Referee::validatePlayerMove(Player player, DesiredMove move) {
    if(move.desireCards) {
        // if they want cards, return true if we have cards to give them
        return refGameState.GetNumCardsInDeck() > 0;
    }
    else if(move.desiredCon.empty()) {
        return false;
    }
    else {
        // if they want connections, see if they have the right cards in their hand, number of rails, and if it's available
        for(Connection c : move.desiredCon) {
            if(!refGameState.canPlayerBuy(*playerData.at(player), c)) {
                return false;
            }
        }

        return true;
    }
}

int destinationPoints(PlayerGS* player) {
    int score = 0;

    


    return score;
}

int Referee::calculateScore(Player player) {
    int score = 0;

    PlayerGS* pgs = playerData.at(player);

    // one point per length
    for(Connection c : pgs->GetOwnedCons()) {
        score += c.getLength();
    }

    // calculate if the player reached their destination
    score += destinationPoints(pgs);


    return score;
}

bool Referee::isEndPhase() {
    for(std::pair<Player, PlayerGS*> p : playerData) {
        if(p.second->GetRails() <= END_PHASE_RAIL_NUM 
        || refGameState.GetUnownedCons().size() <= 0
        || refGameState.GetNumCardsInDeck() <= 0) {
            return true;
        }
    }
    return false;
}

void Referee::endPhase() {
    // everyone gets one last turn and then the game is over
    for(PlayerGS* pgs : refGameState.GetTurnOrder()) {
        Player currentPlayer = whosTurnIsItAnyways();
        DesiredMove playerMove = currentPlayer.takeTurn(*playerData.at(currentPlayer));
        applyPlayerMove(currentPlayer, playerMove);
    }

    gameOver = true;

}

bool Referee::isGameOver() {
    return gameOver;
}

Player Referee::getWinner() {
    return findRanking().at(0);
}

std::vector<Player> Referee::findRanking() {
    std::map<Player, bool> ranking = {};
    std::vector<Player> result = {};

    std::map<Player, int> playerScores = {};

    std::vector<int> allScores = {};

    std::vector<Player> longestPath = {};

    int longestPathLength = MIN_CON_LENGTH;
    for(std::pair<Player, PlayerGS*> p : playerData) {

        int totalScore = calculateScore(p.first);

        // TODO: find longest path, then push them into longestPath if they do, and remove those who don't
        allScores.push_back(totalScore);

        playerScores.insert(std::pair<Player, int>{p.first, totalScore});
    }

    for(Player p : longestPath) {
        playerScores.at(p) += LONGEST_PATH_POINTS;
    }

    // TODO: add the players ordered by score from highest to lowest to the ranking
    
    /*
    std::map<Player, int>::iterator it = playerScores.begin();
    sort(playerScores.begin(), playerScores.end(), []( std::pair<Player, int> x, std::pair<Player, int> y){
        return x.second - y.second;
    });
    */

    sort(allScores.begin(), allScores.end());

    for(std::pair<Player, int> p : playerScores) {
        for(int i = allScores.size()-1; i >= 0; --i) {
            if(p.second == allScores.at(i)) {
                ranking.insert(std::pair<Player, bool>{p.first, true});
            }
        }
    }

    for(std::pair<Player, bool> p : ranking) {
        result.push_back(p.first);
    } 

    return result;
}

void Referee::applyPlayerMove(Player player, DesiredMove move) {
    // applyPlayerMove with validate if the Player can make the given move
    if(validatePlayerMove(player, move)) {
        PlayerGS* playerGameState = playerData.at(player);
        if(move.desireCards) {
            // this line should get repeated with how many cards they get when asking for them (for now it's 2)
            for(int i = 0; i < NUM_CARD_DRAWN_PER_TURN; ++i) {
                playerGameState->takeCard(drawRandomCard());
            }
        }
        else {
            for(Connection c : move.desiredCon) {
                refGameState.GivePlayerCon(playerGameState, c);
            }
        }

        refGameState.NextPlayersTurn();
    }
    else {
        eliminatePlayer(player);
    }
}

void Referee::eliminatePlayer(Player player) {
    kickedPlayers.push_back(player);
    // first, remove the PlayerGS from the turn order in RefereeGS
    std::vector<PlayerGS*> order = refGameState.GetTurnOrder();
    PlayerGS* eliminatedPlayerGS = playerData.at(player);
    order.erase(std::remove(order.begin(), order.end(), eliminatedPlayerGS), order.end());
    playerData.erase(player);
    
    refGameState.SetTurnOrder(order);

    std::vector<Connection> freeableCons = eliminatedPlayerGS->GetOwnedCons();

    // make the owned Connections of the eiminated Player available again
    for(Connection c : freeableCons) {
        refGameState.GetUnownedCons().push_back(c);
    }
    refGameState.UpdateUnownedConnections();
}



// getter just for testing
std::map<Player, PlayerGS*> Referee::GetPlayerData() {
    return playerData;
}

RefereeGS Referee::GetRefGS() {
    return refGameState;
}

Referee* Referee::runGame() {
    // okay this is temporary to score us a few points maybe
    int i = 1000;
    while (!gameOver && i > 1000) {
        Player currentPlayer = whosTurnIsItAnyways();
        DesiredMove playerMove = currentPlayer.takeTurn(*playerData.at(currentPlayer));
        applyPlayerMove(currentPlayer, playerMove);

        // check if the game is in the end phase
        if (isEndPhase()) {
            endPhase();
        }

        i--;
    }
    return this;
}

std::vector<Player> Referee::getCheaters() {
    return kickedPlayers;
}