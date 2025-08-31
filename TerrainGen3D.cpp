#include "TerrainGen3D.h"
#include <iostream>

bool running;
float ticksCount;

vector2 gradients[1024][1024];

bool TerrainGen3D::init() {
    renderer3D = Renderer3D(800, 800);
    
    if  (!renderer3D.init()) {
        return false;
    }

    keyState = SDL_GetKeyboardState(0);


    WIDTH = 1024;
    HEIGHT = 1024;

    terrainMesh = createTerrainMesh();


    return true;
}

void TerrainGen3D::runLoop() {
    
    running = true;


    while (running) {
        
        while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16));
        
        float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;
        ticksCount = SDL_GetTicks();


        processInput(deltaTime);
        renderer3D.render(terrainMesh);
    }
    
}

void TerrainGen3D::processInput(float deltaTime) {
    
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        
        case SDL_QUIT:
            running = false;
            break;
        default:
            break;
        
        }
    }

    if (keyState[SDL_SCANCODE_ESCAPE]) {
        running = false;
    }

    if (keyState[SDL_SCANCODE_W]) {
        renderer3D.camPos.z += deltaTime * 20;
    }

    if (keyState[SDL_SCANCODE_A]) {
        renderer3D.camPos.x -= deltaTime * 20;
    }

    if (keyState[SDL_SCANCODE_D]) {
        renderer3D.camPos.x += deltaTime * 20;
    }

    if (keyState[SDL_SCANCODE_S]) {
        renderer3D.camPos.z -= deltaTime * 20;
    }

    if (keyState[SDL_SCANCODE_Q]) {
        renderer3D.camPos.y -= deltaTime * 20;
    }

    if (keyState[SDL_SCANCODE_Z]) {
        renderer3D.camPos.y += deltaTime * 20;
    }

    if (keyState[SDL_SCANCODE_SPACE]) {
        terrainMesh = createTerrainMesh();
    }

    //std::cout << "CamPos X: " << renderer3D.camPos.x << " Y: " << renderer3D.camPos.y << " Z: " << renderer3D.camPos.z << std::endl;

}


mesh TerrainGen3D::createTerrainMesh() {
    
    //WORK ON THIS ITS SHIT



    populateRandomGradients();
    
    mesh result;
    float noiseMap[WIDTH][HEIGHT];

    

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            
            noiseMap[x][y] = perlin(x*0.1,y*0.1) * 255;
            
            //std::cout << "X: " << x << " Y: " << y << " " << noiseMap[x][y] << std::endl;
        }
    }
    
    //Multiple of 2
    int divideFactor = 32;
    int count = 0;


    for (int y = 0; y < HEIGHT; y += HEIGHT / divideFactor) {
        for (int x = 0; x < WIDTH; x += WIDTH / divideFactor) {
            
            if (!(x + WIDTH / divideFactor >= WIDTH) && !(y + HEIGHT / divideFactor >= HEIGHT)) {
                
                tri tri0 = {vector3{x, noiseMap[x][y], y}, vector3{x + WIDTH / divideFactor, noiseMap[x + WIDTH / divideFactor][y], y}, vector3{x, noiseMap[x][y + HEIGHT / divideFactor], y + HEIGHT / divideFactor}};
                tri tri1 = {vector3{x + WIDTH / divideFactor, noiseMap[x + WIDTH / divideFactor][y], y}, vector3{x + WIDTH / divideFactor, noiseMap[x + WIDTH / divideFactor][y + HEIGHT / divideFactor], y + HEIGHT / divideFactor}, vector3{x, noiseMap[x][y + HEIGHT / divideFactor],  y + HEIGHT / divideFactor}};
                
                /* Clamping y-value
                for (int i = 0; i < 3; i++) {
                    if (tri0.points[i].y < 128) {
                        tri0.points[i].y = 128;
                    }

                    if (tri1.points[i].y < 128) {
                        tri1.points[i].y = 128;
                    }
                }
                */

            
                result.tris.emplace_back(tri0);
                result.tris.emplace_back(tri1);
            
                
            }
            count++;
        }
    }


    return result;
}



float TerrainGen3D::perlin(float x, float y) {
 
  int x0 = (int) floor(x);
  int x1 = x0 + 1;
  int y0 = (int) floor(y);
  int y1 = y0 + 1;

  float sx = x - (float) x0;
  float sy = y - (float) y0;

  float n0,n1,ix0,ix1,value;
  
  n0 = dotGridGradient(x0, y0, x, y);
  n1 = dotGridGradient(x1, y0, x, y);
  ix0 = interpolate(n0, n1, sx);

  n0 = dotGridGradient(x0, y1, x, y);
  n1 = dotGridGradient(x1, y1, x, y);
  ix1 = interpolate(n0, n1, sx);

  value = interpolate(ix0, ix1, sy);
  
  value = (value * 0.5) + 0.5; // Make positive

  return value;
}

float TerrainGen3D::dotGridGradient(int ix, int iy, float x, float y) {
  vector2 gradient = gradients[ix][iy];

  float dx = x - (float) ix;
  float dy = y - (float) iy;

  return (dx*gradient.x + dy*gradient.y);

}

void TerrainGen3D::populateRandomGradients() {

  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      vector2 v;
      v.x = -1+ 2*((float)rand())/ RAND_MAX;
      v.y = -1+ 2*((float)rand())/ RAND_MAX;
      gradients[x][y] = v; 
    }
  } 

}



float TerrainGen3D::interpolate(float a0, float a1, float w) {
  return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
}
