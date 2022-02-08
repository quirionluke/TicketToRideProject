#ifndef MAP_EDITOR_HPP
#define MAP_EDITOR_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <map.hpp>
#include <circle.hpp>
#include <config.hpp>

/*
    the Visualizer class handles the drawing of the map to the screen,
    including the colors and positions of the Connections and Cities
        -vMap: the Map object to be drawn
*/
class Visualizer {


    //const uint MARGIN_SIZE = 100;

public:


    Visualizer() {

    };

    ~Visualizer() {

    };

    // shows the map in a new window usin SDL
    void ShowMap(Map vMap);

private:

    // helper method that adds the cities to the renderer as circles with the city names over the circles
    void draw_cities(Map vMap, SDL_Renderer* renderer, TTF_Font* ourFont);
    
    // helper method that adds the connections to the renderer as segmented lines
    void draw_connections(Map vMap, SDL_Renderer* renderer);


};


#endif