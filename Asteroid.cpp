// Asteroid.cpp
#include "Asteroid.h"
#include <cmath>
#include <random>

#ifndef M_PI
#define M_PI (atan(1)*4)
#endif

// Asteroid constructor
Asteroid::Asteroid(SDL_Renderer* renderer, int size, float x_pos, float y_pos)
    : renderer(renderer), size(size), x(x_pos), y(y_pos) {
    // Set random speed
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disSpeed(-2, 2);

    speedX = disSpeed(gen);
    speedY = disSpeed(gen);

    // Create a random polygon shape for the asteroid
    int numPoints = 12;
    float radius = size * 10;
    for (int i = 0; i < numPoints; ++i) {
        float angle = (float)i / numPoints * 2 * M_PI;
        float randomRadius = radius + (rand() % 10 - 5);
        relative_points.push_back({(Sint16)(randomRadius * cos(angle)), (Sint16)(randomRadius * sin(angle))});
    }
}

// Asteroid destructor
Asteroid::~Asteroid() {
}

// Update asteroid position
void Asteroid::update() {
    x += speedX;
    y += speedY;

    // Wrap around the screen
    if (x < 0) x = 800;
    if (x > 800) x = 0;
    if (y < 0) y = 600;
    if (y > 600) y = 0;
}

// Render the asteroid
void Asteroid::render() {
    // Calculate world points
    world_points.clear();
    for (const auto& point : relative_points) {
        world_points.push_back({(Sint16)(x + point.x), (Sint16)(y + point.y)});
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
    // Draw the asteroid polygon
    SDL_RenderDrawLines(renderer, world_points.data(), world_points.size());
    // Close the polygon
    SDL_RenderDrawLine(renderer, world_points.back().x, world_points.back().y, world_points.front().x, world_points.front().y);
}

// Check if asteroid is off-screen
bool Asteroid::isOffScreen() {
    return (x < -50 || x > 850 || y < -50 || y > 650);
}

// Getters
float Asteroid::getX() { return x; }
float Asteroid::getY() { return y; }
int Asteroid::getSize() { return size; }
const std::vector<SDL_Point>& Asteroid::getPoints() { return world_points; }
