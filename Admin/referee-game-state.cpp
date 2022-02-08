#include <referee-game-state.hpp>

void RefereeGS::NextPlayersTurn() {
    if(currentPlayer+1 >= playerTurnOrder.size()) {
        currentPlayer = 0;
    }
    else {
        currentPlayer++;
    }
}

void RefereeGS::UpdateUnownedConnections() {
    for(PlayerGS* p : playerTurnOrder) {
        p->SetAvailableConnections(unownedCons);
    }
}

void RefereeGS::AddPlayerToGame(PlayerGS* player) {
    playerTurnOrder.push_back(player);
}

bool RefereeGS::canPlayerBuy(PlayerGS player, Connection con) {
    // check if the player has the right number of cards and rails
    if(player.GetHand().at(con.getColor()) >= con.getLength() && player.GetRails() >= con.getLength()) {
        // check if anyone owns the connection
        std::vector<Connection>::iterator it = std::find(unownedCons.begin(), unownedCons.end(), con);
        
        return it != unownedCons.end();
    }
    else {
        return false;
    }
}

void RefereeGS::GivePlayerCard(PlayerGS* player, Color c) {
    player->GetHand().at(c)++;
}

void RefereeGS::GivePlayerCon(PlayerGS* player, Connection con) {
    // we are also going to have to remove this connection from unowned
    player->GetOwnedCons().push_back(con);

    unownedCons.erase(std::find(unownedCons.begin(), unownedCons.end(), con));

    player->GetHand().at(con.getColor()) -= con.getLength();
    player->SetRails(player->GetRails() - con.getLength());

    UpdateUnownedConnections();
}


// getters
PlayerGS* RefereeGS::GetPlayer(uint ind) {
    return playerTurnOrder.at(ind);
}
std::vector<PlayerGS*> RefereeGS::GetTurnOrder() {
    return playerTurnOrder;
}

PlayerGS* RefereeGS::GetCurrentPlayer() {
    return playerTurnOrder.at(currentPlayer);
}
std::vector<Connection> RefereeGS::GetUnownedCons() {
    return unownedCons;
}

Map* RefereeGS::GetBoard() const {
    return board;
}

std::unordered_map<Color, int, ColorHash> RefereeGS::GetDeck() {
    return deck;
}

// setters
void RefereeGS::SetTurnOrder(std::vector<PlayerGS*> players) {
    playerTurnOrder = players;
}

void RefereeGS::SetBoard(Map* boardx) {
    board = boardx;
}

void RefereeGS::SetCurrentPlayer(uint ind) {
    currentPlayer = ind;
}

void RefereeGS::SetDeck(std::unordered_map<Color, int, ColorHash> decks) {
    deck = decks;
}

int RefereeGS::GetNumCardsInDeck() {
    int result = 0;
    for(std::pair<Color, int> p : deck) {
        result += p.second;
    }
    return result;
}
