all:
	g++ -o TerrainGen main.cpp TerrainGen3D.cpp Renderer3D.cpp -I /usr/include/SDL2 -lSDL2 -g