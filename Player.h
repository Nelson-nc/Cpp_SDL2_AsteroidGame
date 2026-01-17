// Player.h
#pragma once
#include <SDL2/SDL.h>
#include <vector>

class Bullet {
public:
    Bullet(float x, float y, float angle);
    void update();
    void render(SDL_Renderer* renderer);
    bool isOffScreen();
    float getX() { return x; }
    float getY() { return y; }
private:
    float x, y;
    float speedX, speedY;
};

class Player {
public:
    Player(SDL_Renderer* renderer);
    ~Player();

    void handleEvents(const SDL_Event& event);
    void update();
    void render();
    void shoot();
    std::vector<Bullet>& getBullets();
    float getX();
    float getY();
    void reset();

private:
    SDL_Renderer* renderer;
    // Player position
    float x, y;
    // Player angle
    float angle;
    // Player speed
    float speed;
    // Player acceleration
    float acceleration;
    // Player deceleration
    float deceleration;
    // Max speed
    float maxSpeed;
    // Bullets
    std::vector<Bullet> bullets;
};
