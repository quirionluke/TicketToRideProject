#include <City.hpp>

void City::AddConnection(Connection c) {

    if(c.getCities().first != name && c.getCities().second != name) {
        throw std::invalid_argument("a connection cannot be formed between these two cities");
    }


    bool contained = false;
    for(Connection con : outbound) {
        if(con == c) {
            contained = true;
        }
    }

    if(!contained) {
        outbound.push_back(c);
    }
    else {
        std::cerr << "Connection already exists" << std::endl;
    }
}

bool City::operator==(const City& lhs) const{
    return this->pos.x == lhs.pos.x
        && this->pos.y == lhs.pos.y
        && this->name == lhs.name
        && this->outbound == lhs.outbound;
}


SDL_Point City::getPosn() {
    return pos;
}

std::string City::getName() {
    return name;
}

std::vector<Connection> City::getOutbound() {
    return outbound;
}