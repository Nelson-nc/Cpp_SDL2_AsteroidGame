// Asteroid.h
#pragma once
#include <SDL2/SDL.h>
#include <vector>

class Asteroid {
public:
    Asteroid(SDL_Renderer* renderer, int size, float x_pos, float y_pos);
    ~Asteroid();

    void update();
    void render();
    bool isOffScreen();
    float getX();
    float getY();
    int getSize();
    const std::vector<SDL_Point>& getPoints();

private:
    SDL_Renderer* renderer;
    float x, y;
    float speedX, speedY;
    int size;
    std::vector<SDL_Point> relative_points;
    std::vector<SDL_Point> world_points;
};
