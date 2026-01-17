// main.cpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "Player.h"
#include "Asteroid.h"

// Game class to manage the main game loop and objects
class Game {
public:
    // Constructor
    Game();
    // Destructor
    ~Game();

    // Initialize the game
    bool init();
    // Run the game loop
    void run();

private:
    // Handle user input
    void handleEvents();
    // Update game objects
    void update();
    // Render game objects
    void render();
    // Check for collisions
    void checkCollisions();
    // Render text
    void renderText(const std::string& text, int x, int y);

    // SDL window and renderer
    SDL_Window* window;
    SDL_Renderer* renderer;
    // Font
    TTF_Font* font;
    // Game loop flag
    bool isRunning;
    // Player object
    Player* player;
    // Vector of asteroids
    std::vector<Asteroid> asteroids;
    // Score and lives
    int score;
    int lives;
};

// --- Game class implementation ---

Game::Game() : window(nullptr), renderer(nullptr), font(nullptr), isRunning(false), player(nullptr), score(0), lives(3) {}

Game::~Game() {
    // Delete player object
    delete player;
    // Close the font
    if (font) {
        TTF_CloseFont(font);
    }
    // Destroy renderer and window
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    // Quit SDL subsystems
    TTF_Quit();
    SDL_Quit();
}

bool Game::init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    // Create window
    window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Load font
    font = TTF_OpenFont("src/include/SDL2/DroidSans.ttf", 24);
    if (font == nullptr) {
        //fallback to any other font
        font = TTF_OpenFont("C:/Windows/Fonts/Arial.ttf", 24);
        if (font == nullptr) {
            std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
            return false;
        }
    }


    // Create player
    player = new Player(renderer);

    // Create asteroids
    for (int i = 0; i < 10; ++i) {
        asteroids.emplace_back(renderer, 3, rand() % 800, rand() % 600);
    }

    isRunning = true;
    return true;
}

void Game::run() {
    // Main game loop
    while (isRunning) {
        handleEvents();
        update();
        checkCollisions();
        render();
    }
}

void Game::handleEvents() {
    SDL_Event event;
    // Poll for events
    while (SDL_PollEvent(&event)) {
        // If user closes the window
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        // Handle player input
        player->handleEvents(event);
    }
}

void Game::update() {
    // Update player
    player->update();
    // Update asteroids
    for (auto& asteroid : asteroids) {
        asteroid.update();
    }
}

void Game::checkCollisions() {
    // Check collisions between bullets and asteroids
    auto& bullets = player->getBullets();
    for (auto it_bullet = bullets.begin(); it_bullet != bullets.end(); ) {
        bool bullet_removed = false;
        for (auto it_asteroid = asteroids.begin(); it_asteroid != asteroids.end(); ) {
            float dx = it_asteroid->getX() - it_bullet->getX();
            float dy = it_asteroid->getY() - it_bullet->getY();
            float distance = sqrt(dx * dx + dy * dy);
            if (distance < it_asteroid->getSize() * 10) {
                // Collision detected
                score += 10;
                if (it_asteroid->getSize() > 1) {
                    asteroids.emplace_back(renderer, it_asteroid->getSize() - 1, it_asteroid->getX(), it_asteroid->getY());
                    asteroids.emplace_back(renderer, it_asteroid->getSize() - 1, it_asteroid->getX(), it_asteroid->getY());
                }
                it_asteroid = asteroids.erase(it_asteroid);
                it_bullet = bullets.erase(it_bullet);
                bullet_removed = true;
                break;
            } else {
                ++it_asteroid;
            }
        }
        if (!bullet_removed) {
            ++it_bullet;
        }
    }

    // Check collisions between player and asteroids
    for (auto it_asteroid = asteroids.begin(); it_asteroid != asteroids.end(); ) {
        float dx = it_asteroid->getX() - player->getX();
        float dy = it_asteroid->getY() - player->getY();
        float distance = sqrt(dx * dx + dy * dy);
        if (distance < it_asteroid->getSize() * 10) {
            lives--;
            if (lives == 0) {
                isRunning = false;
            } else {
                player->reset();
                it_asteroid = asteroids.erase(it_asteroid);
            }
        } else {
            ++it_asteroid;
        }
    }
}


void Game::render() {
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render player
    player->render();
    // Render asteroids
    for (auto& asteroid : asteroids) {
        asteroid.render();
    }
    
    // Render score and lives
    renderText("Score: " + std::to_string(score), 10, 10);
    renderText("Lives: " + std::to_string(lives), 10, 40);


    // Present the renderer
    SDL_RenderPresent(renderer);
}

void Game::renderText(const std::string& text, int x, int y) {
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dstrect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

// --- Main function ---

int main(int argc, char* argv[]) {
    // Create a game instance
    Game game;
    // Initialize and run the game
    if (game.init()) {
        game.run();
    }
    return 0;
}
