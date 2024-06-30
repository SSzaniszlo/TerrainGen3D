#include "Renderer3D.h"
#include <iostream>

Renderer3D::Renderer3D(int width, int height) {
    WIDTH = width;
    HEIGHT = height;

    camPos.x = 0;
    camPos.y = 0;
    camPos.z = -100;



}

bool Renderer3D::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Enable to init SDL %s" , SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Renderer", 0, 0, WIDTH, HEIGHT, 0);

    if (!window) {
        SDL_Log("Enable to init window %s" , SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    return true;
}

void Renderer3D::render(mesh m) {
    

    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
            
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < m.tris.size(); i++) {
        vector2 p0 = calculatedProjected(m.tris.at(i).points[0]);
        vector2 p1 = calculatedProjected(m.tris.at(i).points[1]);
        vector2 p2 = calculatedProjected(m.tris.at(i).points[2]);

    
        drawTriangle(p0, p1, p2);
    }


    SDL_RenderPresent(renderer);
    
}

vector2 Renderer3D::calculatedProjected(vector3 point) {
    float dx = point.x - camPos.x;
    float dy = point.y - camPos.y;
    float dz = point.z - camPos.z;

    if (dz == 0) {
        dz = 1;
    }   


    float projectedX = 0.5 * (WIDTH) * dx / dz;
    float projectedY = 0.5 * (HEIGHT) * dy / dz;

    return vector2{projectedX, projectedY};
}

void Renderer3D::drawTriangle(vector2 p0, vector2 p1, vector2 p2) {
    

    SDL_RenderDrawLine(renderer, p0.x, p0.y, p1.x, p1.y);
    SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
    SDL_RenderDrawLine(renderer, p2.x, p2.y, p0.x, p0.y);
}



