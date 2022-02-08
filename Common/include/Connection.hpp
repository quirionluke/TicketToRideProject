#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <string>
#include <stdexcept>


/* a Color is one of:
    -red
    -blue
    -green
    -white
*/
// THIS HAS TO BE IN ALPHABETIAL ORDER
// the last one (END) is for generating random colors
enum Color{blue, green, red, white, END};

/*
 * This ColorHash struct is important for getting the unordered_map to use the correct hashing for our Color enum
 * its a weird funky c++ thing that only happens on older compilers but we have to stick with it
 */
struct ColorHash {
	template <typename T>
	std::size_t operator()(T t) const {
		return static_cast<std::size_t>(t);
	}

};


/*
    Connection represents a train line between two cities
        -cityA: the name of one of the cities that is connected
        -cityB: the name of the other city that is connected
            -order doesn't matter
        -length: the length of the railway
        -col: the Color of the railway
*/
class Connection {

    std::string cityA;
    std::string cityB;
    uint length;
    Color col;

public:
    Connection(std::string cityAx, std::string cityBx, uint lengthx, Color colx) {
        if(cityAx == cityBx) {
            throw std::invalid_argument("Cannot form a Connection between the same City");
        }
        cityA = cityAx;
        cityB = cityBx;
        length = lengthx;
        col = colx;
    };

    ~Connection() {

    };

    // override double equals
    bool operator==(const Connection& lhs) const;

    // return a pair of the two cities
    std::pair<std::string, std::string> getCities(); 

    // getters
    Color getColor();
    uint getLength();

};




#endif
