// Player.cpp
#include "Player.h"
#include <cmath>
#include <algorithm>

#ifndef M_PI
#define M_PI (atan(1)*4)
#endif

// --- Bullet class implementation ---

Bullet::Bullet(float x, float y, float angle) : x(x), y(y) {
    float speed = 10.0f;
    speedX = speed * sin(angle * M_PI / 180.0f);
    speedY = -speed * cos(angle * M_PI / 180.0f);
}

void Bullet::update() {
    x += speedX;
    y += speedY;
}

void Bullet::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
    SDL_RenderDrawPoint(renderer, x, y);
}

bool Bullet::isOffScreen() {
    return (x < 0 || x > 800 || y < 0 || y > 600);
}

// --- Player class implementation ---

// Player constructor
Player::Player(SDL_Renderer* renderer) 
    : renderer(renderer), x(400), y(300), angle(0), speed(0),
      acceleration(0.2f), deceleration(0.99f), maxSpeed(5.0f) {
}

// Player destructor
Player::~Player() {
}

// Handle player input
void Player::handleEvents(const SDL_Event& event) {
    // Keyboard input for rotation and acceleration
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_LEFT]) {
        angle -= 5.0f;
    }
    if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
        angle += 5.0f;
    }
    if (currentKeyStates[SDL_SCANCODE_UP]) {
        speed += acceleration;
        if (speed > maxSpeed) {
            speed = maxSpeed;
        }
    }

    // Shooting
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
        shoot();
    }
}

// Update player position and bullets
void Player::update() {
    // Apply deceleration
    speed *= deceleration;

    // Update player position based on angle and speed
    x += speed * sin(angle * M_PI / 180.0f);
    y -= speed * cos(angle * M_PI / 180.0f);

    // Wrap around the screen
    if (x < 0) x = 800;
    if (x > 800) x = 0;
    if (y < 0) y = 600;
    if (y > 600) y = 0;

    // Update bullets
    for (auto& bullet : bullets) {
        bullet.update();
    }
    // Remove bullets that are off-screen
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet& b) {
        return b.isOffScreen();
    }), bullets.end());
}

// Render the player and bullets
void Player::render() {
    // Define the player's triangle shape
    SDL_Point points[4];
    points[0] = { (Sint16)(x + 20 * sin(angle * M_PI / 180.0f)), (Sint16)(y - 20 * cos(angle * M_PI / 180.0f)) };
    points[1] = { (Sint16)(x - 10 * sin((angle + 30) * M_PI / 180.0f)), (Sint16)(y + 10 * cos((angle + 30) * M_PI / 180.0f)) };
    points[2] = { (Sint16)(x - 10 * sin((angle - 30) * M_PI / 180.0f)), (Sint16)(y + 10 * cos((angle - 30) * M_PI / 180.0f)) };
    points[3] = points[0]; // Close the triangle

    // Set draw color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // Draw the triangle
    SDL_RenderDrawLines(renderer, points, 4);

    // Render bullets
    for (auto& bullet : bullets) {
        bullet.render(renderer);
    }
}

// Create a new bullet
void Player::shoot() {
    bullets.emplace_back(x, y, angle);
}

// Get the bullets vector
std::vector<Bullet>& Player::getBullets() {
    return bullets;
}

// Get player's x position
float Player::getX() {
    return x;
}

// Get player's y position
float Player::getY() {
    return y;
}

// Reset player's position
void Player::reset() {
    x = 400;
    y = 300;
    speed = 0;
    angle = 0;
}
