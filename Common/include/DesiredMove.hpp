#ifndef DESIREDMOVE_HPP
#define DESIREDMOVE_HPP

#include <vector>
#include <Connection.hpp>

/*
    a DesiredMove represents the move that a player wishes to make
        -desiredCon --> returns any Connections that the Player may want to acquire this turn, empty if drawing cards
        -desireCards --> true if the player is requesting more cards, false if acquiring Connection
*/
struct DesiredMove {
    std::vector<Connection> desiredCon;
    bool desireCards;


    // empty constructor if just requesting cards
    DesiredMove() {
        desiredCon = {};
        desireCards = true;
    }

    DesiredMove(std::vector<Connection> desiredConx) {
        if(desiredConx.empty()) {
            throw std::invalid_argument("error: must either request connection or draw cards on your turn");
        }
        desiredCon = desiredConx;
        desireCards = false;
    }
};


#endif