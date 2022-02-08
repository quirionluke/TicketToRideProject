#ifndef BUYNOW_HPP
#define BUYNOW_HPP

#include <astrategy.hpp>

/*
    BuyNow is a child class of Strategy and represents the Buy-Now strategy
        Buy-Now follows the rules:
            -Picks the last Destination lexicographically
            -Requests more cards when no Connections can be bought
            -Purchases the first Connection from the lexicographically sorted sequence for which it has enough cards and rails
*/
class BuyNow : public AStrategy {

    // override methods of parent class
    bool shouldRequestMoreCards();
};

#endif