#include <Destination.hpp>

bool Destination::operator==(const Destination &lhs) {
    return ((this->endpointA == lhs.endpointA
         && this->endpointB == lhs.endpointB)
        || (this->endpointA == lhs.endpointB
        &&  this->endpointB == lhs.endpointA));
}

City Destination::getEndpointA() {
    return endpointA;
}

City Destination::getEndpointB() {
    return endpointB;
}