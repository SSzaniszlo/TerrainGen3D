#include "TerrainGen3D.h"

int main() {
    TerrainGen3D terrain;

    if (terrain.init()) {
        terrain.runLoop();
    }
}