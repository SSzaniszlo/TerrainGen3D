#include "Renderer3D.h"

class TerrainGen3D {

    public:
        TerrainGen3D(){};

        
        bool init();
        void runLoop();

    private:

        int WIDTH;
        int HEIGHT;

        void processInput(float deltaTime);
        
        mesh createTerrainMesh();
        
        void populateRandomGradients();
        float perlin(float x, float y);
        float dotGridGradient(int ix, int iy, float x, float y);
        float interpolate(float a0, float a1, float w);

        const Uint8* keyState;

        bool running;
        float ticksCount;

        mesh terrainMesh;

        Renderer3D renderer3D;

};