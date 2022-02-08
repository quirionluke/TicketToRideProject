#ifndef CONFIG_HPP
#define CONFIG_HPP


// this file declares a bunch of variables that are used in configuring the game

// minumum connection length
const unsigned int MIN_CON_LENGTH = 3;

// maximum connection length
const unsigned int MAX_CON_LENGTH = 5;

// the minimum number of players before a game can start
const unsigned int MIN_NUM_PLAYERS = 2;

// the maximum number of players allowed in a single game
const unsigned int MAX_NUM_PLAYERS = 2;

// the number of connections that one player can buy on one turn
const unsigned int NUM_CONS_BUY_ON_TURN = 1;

// the number of cards a player is handed when requesting them
const unsigned int NUM_CARD_DRAWN_PER_TURN = 2;

// the number of destinations that a player chooses
const unsigned int NUM_DESTINATIONS_CHOSEN = 2;

// the numer of rails that players have at the start of the game
const int STARTING_RAILS = 45;

// the number of cards in the players hand at the start of the game
const int STARTING_CARDS = 4;

// the amount of points someone gets for having the longest path
const int LONGEST_PATH_POINTS = 20;

// the amount of rails that are needed to go into the end phase
const int END_PHASE_RAIL_NUM = 2;

// the path to the font asset, relative to the makefile
// **CHANGE THIS WHENEVER THE MAKEFILE IS MOVED**
const std::string pathToFontAsset = "../Trains/Other/Assets/CityFont2.ttf";

const uint FONT_SIZE = 14;
const uint FONT_FRACTION = 10;
const uint DOT_FRACTION = 100;

#endif