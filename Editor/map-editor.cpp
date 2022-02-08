#include <map-editor.hpp>


// a helper method that translates the string into an SDL_Color
SDL_Color ColorRGBTranslator(Color c) {

    SDL_Color result;

    switch(c) {
        case red:
            result = {255, 0, 0, 255};
            return result;
        case blue:
            result = {0, 100, 255, 255};
            return result;
        case green:
            result = {0, 255, 0, 255};
            return result;
        case white:
            result = {255, 255, 255, 255};
            return result;
        default:
            throw std::invalid_argument("invalid color given");
    }
}

void Visualizer::draw_cities(Map vMap, SDL_Renderer* renderer, TTF_Font* ourFont) {
    SDL_SetRenderDrawColor(renderer, 100, 100, 0, 255);
    for(std::pair<std::string, City> p : vMap.getCities()) {
        SDL_RenderFillCircle(renderer, p.second.getPosn().x, p.second.getPosn().y, vMap.getWidth()/DOT_FRACTION);

        // draw city names as text
        SDL_Color White = {255,255,255,255};

        SDL_Surface* surfaceMessage =
            TTF_RenderText_Solid(ourFont, p.first.c_str(), White);
        
        SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

        SDL_Rect Message_rect;

        int length = p.first.length();
        Message_rect.w = (vMap.getWidth())/(FONT_FRACTION);
        Message_rect.h = (vMap.getHeight())/(FONT_FRACTION);
        Message_rect.x = (p.second.getPosn().x) - Message_rect.w/2;
        Message_rect.y = (p.second.getPosn().y) - Message_rect.h/2;

        SDL_RenderCopy(renderer, message, NULL, &Message_rect);
        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(message);
    }
}

// the formula for the point at numer/denom between points p1 and p2
SDL_Point findPointOnLine(SDL_Point p1, SDL_Point p2, int numer, int denom) {
    return SDL_Point{p1.x + numer*(p2.x-p1.x)/denom, p1.y + numer*(p2.y-p1.y)/denom};
}

// helper method that adds the connections to the renderer as segmented lines
void Visualizer::draw_connections(Map vMap, SDL_Renderer* renderer) {

    //TODO: make a way to have multiple connections between the same two cities

    for(Connection c : vMap.getConnections()) {
        Color colr = c.getColor();
        SDL_Color rgbColr = ColorRGBTranslator(colr);
        SDL_SetRenderDrawColor(renderer, rgbColr.r, rgbColr.b, rgbColr.g, rgbColr.a);
        std::pair<SDL_Point, SDL_Point> currconpos = vMap.findPosOfConnection(c);
        
        /*
        currconpos.first.x += MARGIN_SIZE;
        currconpos.first.y += MARGIN_SIZE;
        currconpos.second.x += MARGIN_SIZE;
        currconpos.second.y += MARGIN_SIZE;
        */

        // draw the lines
        SDL_RenderDrawLine(renderer, currconpos.first.x, currconpos.first.y, currconpos.second.x, currconpos.second.y);

        // divide the line into x amount of segments
        unsigned int len = c.getLength();
        // set the color to black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for(uint i = 1; i < len; i++) {
            SDL_Point currPoint = findPointOnLine(currconpos.first, currconpos.second, i, len);
            SDL_RenderFillCircle(renderer, currPoint.x, currPoint.y, vMap.getWidth()/DOT_FRACTION);
        }
    }
}

void Visualizer::ShowMap(Map vMap) {
    SDL_Window* window = SDL_CreateWindow("Trains.com", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, vMap.getWidth()+1, vMap.getHeight() + 1, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_Rect screenrect{0,0, (int)vMap.getWidth()+1, (int)vMap.getHeight()+1};
    SDL_RenderFillRect(renderer, &screenrect);
    TTF_Font* ourFont = TTF_OpenFont(pathToFontAsset.c_str(), FONT_SIZE);

    draw_connections(vMap, renderer);
    //std::cout << "Connections drawn" << std::endl;
    draw_cities(vMap, renderer, ourFont);
    //std::cout << "cities drawn" << std::endl;

    // this needs to be done in order to "update" our window with the new information
    SDL_RenderPresent(renderer);

    // this is going to have to change
    // this keeps the window up for ten seconds, then closes it
    SDL_Delay(5000);
}