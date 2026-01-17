# Asteroid Clones

This repository contains two implementations of the classic Asteroids game, one in C++ with SDL2 and another in Python with Pygame.

## C++ with SDL2

This section documents the process of creating the Asteroids clone in C++ with SDL2.

### Setup

1.  **Install MinGW-w64:** If you don't have `g++`, you'll need to install a C++ compiler like MinGW-w64. You can find installers and instructions online.
2.  **Download SDL2 Development Libraries:** Go to the [SDL website](https://www.libsdl.org/download-2.0.php) and download the "Development Libraries" for MinGW (usually a `.zip` file).
3.  **Extract SDL2:** Extract the contents of the `.zip` file to a convenient location.
4.  **Copy SDL2 files:** Copy the `include` and `lib` folders from the extracted SDL2 directory into the `AsteroidClones/sdl2_cpp_asteroid/src` directory. You will also need to copy `SDL2.dll` and `SDL2_ttf.dll` from the `bin` folder of the extracted SDL2 directory into the `AsteroidClones/sdl2_cpp_asteroid` directory (where the executable will be).
5.  **Compile:** Navigate to the `AsteroidClones/sdl2_cpp_asteroid` directory in your terminal and compile the game using the following command:
    ```bash
    g++ -std=c++11 main.cpp Player.cpp Asteroid.cpp -o main -Isrc/include -Lsrc/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
    ```
6.  **Run:** Execute the compiled program:
    ```bash
    ./main.exe
    ```

### Code Structure

The code is organized into three main files:

-   `main.cpp`: This is the main entry point of the game. It contains the `Game` class which manages the game loop, event handling, and rendering.
-   `Player.h`/`Player.cpp`: These files contain the `Player` class, which represents the player's spaceship. It handles the player's movement, rotation, shooting, and drawing. It also contains the `Bullet` class.
-   `Asteroid.h`/`Asteroid.cpp`: These files contain the `Asteroid` class, which represents the asteroids. It handles the asteroid's movement, appearance, and splitting.

### Implementation Details

-   **Game Loop:** The main game loop is in the `run` method of the `Game` class. It handles events, updates the game state, checks for collisions, and draws the game objects on the screen.
-   **Player:** The `Player` class represents the player's spaceship. It is represented by a triangle. The player can rotate left and right, move forward with acceleration and deceleration, and shoot bullets. The player wraps around the screen.
-   **Asteroids:** The `Asteroid` class represents the asteroids. Asteroids are represented by random polygons. They move at a constant velocity and wrap around the screen. When an asteroid is hit by a bullet, it splits into two smaller asteroids. If a small asteroid is hit, it is destroyed.
-   **Bullets:** The `Bullet` class represents the bullets. Bullets are represented by single points. They move at a constant velocity and are destroyed when they go off-screen.
-   **Collision Detection:** Collision detection is done using a simple distance check between the centers of the objects.
-   **Scoring and Lives:** The player starts with 3 lives. The score is incremented when an asteroid is destroyed. A life is lost when the player collides with an asteroid, and the player is respawned. The game ends when the player has 0 lives.
-   **Game Screens:** The game has a start screen and a game over screen. The player can restart the game by pressing any key.
-   **Text Rendering:** Text (score and lives) is rendered using the `SDL_ttf` library.

### Understanding C++ Pointers and `->`

In C++, `->` is called the "arrow operator" and is used to access members of a class, struct, or union through a pointer.

-   **Pointers:** A pointer is a variable that stores the memory address of another variable. For example, `Player* player;` declares a pointer named `player` that can hold the memory address of a `Player` object.
-   **`->` Operator:** When you have a pointer to an object (e.g., `player`), you use the `->` operator to call a method or access a member variable of that object. So, `player->update()` means "call the `update()` method on the object that `player` points to." This is equivalent to `(*player).update()`, where `*player` dereferences the pointer to get the object itself, and then `.` is used to access its members.

### Adding Assets (Images, Sprites, and Animations)

This game uses primitive shapes for rendering. To add more visually appealing assets like images, sprites, and animations, you would typically use an additional SDL2 library called `SDL_image` for loading various image formats (PNG, JPG, etc.).

**Steps to add images/sprites:**

1.  **Include SDL_image:** You would need to include `#include <SDL_image.h>` in your relevant `.cpp` files.
2.  **Initialize SDL_image:** Call `IMG_Init(IMG_INIT_PNG);` (or other formats you need) at the start of your program and `IMG_Quit();` at the end.
3.  **Load Image:** Use `IMG_LoadTexture(renderer, "path/to/your/image.png");` to load an image into an an `SDL_Texture*`.
4.  **Render Image:** Use `SDL_RenderCopy(renderer, texture, &sourceRect, &destinationRect);` to draw a portion of the texture (sprite) to a specific area on the screen.
    -   `sourceRect`: Defines the part of the image you want to draw (for sprite sheets).
    -   `destinationRect`: Defines where on the screen and what size you want to draw it.

**For Sprite Animation:**

-   A sprite animation typically involves a sequence of images (frames) from a sprite sheet.
-   You would keep track of the current frame, the total number of frames, and the time each frame should be displayed.
-   In your `update` method, you'd advance the current frame based on elapsed time.
-   In your `render` method, you'd calculate the `sourceRect` to display the correct frame from your sprite sheet.

## Python with Pygame

This section documents the process of creating the Asteroids clone in Python with Pygame.

### Setup

1.  **Install Python:** Make sure you have Python installed on your system. You can download it from [python.org](https://www.python.org/downloads/).
2.  **Install Pygame:** Open a terminal or command prompt and run the following command to install Pygame:
    ```
    pip install pygame
    ```

### Code Structure

The code is organized into three main files:

-   `main.py`: This is the main entry point of the game. It contains the `Game` class which manages the game loop, event handling, and rendering.
-   `player.py`: This file contains the `Player` class, which represents the player's spaceship. It handles the player's movement, rotation, shooting, and drawing. It also contains the `Bullet` class.
-   `asteroid.py`: This file contains the `Asteroid` class, which represents the asteroids. It handles the asteroid's movement, appearance, and splitting.

### Implementation Details

-   **Game Loop:** The main game loop is in the `run` method of the `Game` class. It handles events, updates the game state, and draws the game objects on the screen.
-   **Player:** The `Player` class is a Pygame `Sprite`. It is represented by a triangle. The player can rotate left and right, move forward with acceleration and deceleration, and shoot bullets. The player wraps around the screen.
-   **Asteroids:** The `Asteroid` class is also a Pygame `Sprite`. Asteroids are represented by random polygons. They move at a constant velocity and wrap around the screen. When an asteroid is hit by a bullet, it splits into two smaller asteroids. If a small asteroid is hit, it is destroyed.
-   **Bullets:** The `Bullet` class is a Pygame `Sprite`. Bullets are represented by circles. They move at a constant velocity and are destroyed when they go off-screen.
-   **Collision Detection:** Collision detection is done using Pygame's `sprite` module. `pygame.sprite.groupcollide` is used to detect collisions between bullets and asteroids. `pygame.sprite.spritecollide` is used to detect collisions between the player and asteroids.
-   **Scoring and Lives:** The player starts with 3 lives. The score is incremented when an asteroid is destroyed. A life is lost when the player collides with an asteroid. The game ends when the player has 0 lives.
-   **Game Screens:** The game has a start screen and a game over screen. The player can restart the game by pressing any key.
-   **Text Rendering:** Text (score and lives) is rendered using the `SDL_ttf` library.

### Adding Assets (Images, Sprites, and Animations)

Pygame makes it relatively straightforward to incorporate images and handle sprite animations.

**Steps to add images/sprites:**

1.  **Load Image:** Use `pygame.image.load("path/to/your/image.png").convert_alpha()` to load an image. `.convert_alpha()` optimizes the image for Pygame and handles transparency.
2.  **Create Sprite:** In your `Sprite` subclass (like `Player`, `Asteroid`, `Bullet`), you would set `self.image` to the loaded image surface and `self.rect` to its `get_rect()`.
3.  **Draw Sprite:** In your `Game` class, after creating a `pygame.sprite.Group()`, you can add your sprites to it and then call `self.all_sprites.draw(self.screen)` in your `draw` method.

**For Sprite Animation:**

-   **Sprite Sheet:** You typically have a single image file (sprite sheet) containing all frames of an animation.
-   **Extract Frames:** Load the sprite sheet and then use `image.subsurface(rect)` to extract individual frames from it. Store these frames in a list.
-   **Animate:** In your sprite's `update` method, cycle through the list of frames based on a timer. For example:
    ```python
    self.current_frame = (self.current_frame + 1) % len(self.animation_frames)
    self.image = self.animation_frames[self.current_frame]
    ```
    You would usually control the speed of animation by only updating the frame every few game ticks.

# Asteroid_with_pygame_and_SDL2
