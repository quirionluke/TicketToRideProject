#include <BuyNow.hpp>

bool BuyNow::shouldRequestMoreCards() {
    return !canBuyConnections();
}