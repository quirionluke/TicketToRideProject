#ifndef DESTINATION_HPP
#define DESTINATION_HPP

#include <City.hpp>
#include <Connection.hpp>

/*
    Destination represents the goals of the players, to make a route of Connections between two cities
        -endpointA: one of the endpoint cities
        -endpointB: the other one of the endpoint cities
            -order doesn't matter
        -bonusPoints: the number of points the player gets for completing the goal
*/
class Destination {

    City endpointA;
    City endpointB;

public:
    Destination(City endpointAx, City endpointBx) {
        endpointA = endpointAx;
        endpointB = endpointBx;
    };


    ~Destination() {

    };


    // override double equals
    bool operator==(const Destination &lhs);

    // getters
    City getEndpointA();
    City getEndpointB();


};






#endif