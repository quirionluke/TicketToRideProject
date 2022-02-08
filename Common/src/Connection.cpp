#include <Connection.hpp>

bool Connection::operator==(const Connection& lhs) const {
    return ((this->cityA == lhs.cityA
        && this->cityB == lhs.cityB)
        || (this->cityA == lhs.cityB
        && this->cityB == lhs.cityA))
        && this->length == lhs.length
        && this->col == lhs.col;
}

std::pair<std::string,std::string> Connection::getCities() {
    return std::pair<std::string, std::string>(cityA, cityB);
}

Color Connection::getColor() {
    return col;
}

uint Connection::getLength() {
    return length;
}
