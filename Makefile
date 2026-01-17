all:
	g++ -std=c++11 main.cpp Player.cpp Asteroid.cpp -o main -Isrc/include -Lsrc/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -static-libstdc++ -static-libgcc
