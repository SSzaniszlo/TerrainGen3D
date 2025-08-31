#include "Renderer3D.h"
#include <iostream>

using namespace std;

Renderer3D::Renderer3D(int width, int height) {
    WIDTH = width;
    HEIGHT = height;

    camPos.x = 0;
    camPos.y = 0;
    camPos.z = 0;



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


    
    vector<vector3*> projectedTriangles;

    for (int i = 0; i < m.tris.size(); i++) {
        
        
        vector3 p0 = calculatedProjected(m.tris.at(i).points[0]);
        vector3 p1 = calculatedProjected(m.tris.at(i).points[1]);
        vector3 p2 = calculatedProjected(m.tris.at(i).points[2]);

        vector3 projectedTri[3];

        projectedTri[0] = p0;
        projectedTri[1] = p1;
        projectedTri[2] = p2;

        projectedTriangles.emplace_back(projectedTri);

        
        SDL_RenderDrawPointF(renderer, p0.x, p0.y);
        SDL_RenderDrawPointF(renderer, p1.x, p1.y);
        SDL_RenderDrawPointF(renderer, p2.x, p2.y);

        drawTriangle(p0, p1, p2);
    }

    quickSort(projectedTriangles, 0, projectedTriangles.size() - 1);

    for (int i = projectedTriangles.size(); i >= 0; i--)
    {
        //SDL_SetRenderDrawColor(renderer, (pro[i].z / 1000.f) * 255,(points[i].z / 1000.f) * 255,(points[i].z / 1000.f) * 255, 255 );
        

        //SDL_RenderDrawPointF(renderer, points[i].x, points[i].y);
    }
    


    SDL_RenderPresent(renderer);
    
}

vector3 Renderer3D::calculatedProjected(vector3 point) {
    
    float dx = point.x - camPos.x;
    float dy = point.y - camPos.y;
    float dz = point.z - camPos.z;

    if (dz == 0) {
        dz = 1;
    }   

    //std::cout << point.z << " " << camPos.z << " " << dz << std::endl;

    float projectedX = 0.5 * (WIDTH) * dx / dz;
    float projectedY = 0.5 * (HEIGHT) * dy / dz;


    return vector3{projectedX, projectedY, dz};
}

void Renderer3D::drawTriangle(vector3 p0, vector3 p1, vector3 p2) {
    

    SDL_RenderDrawLineF(renderer, p0.x, p0.y, p1.x, p1.y);
    SDL_RenderDrawLineF(renderer, p1.x, p1.y, p2.x, p2.y);
    SDL_RenderDrawLineF(renderer, p2.x, p2.y, p0.x, p0.y);
    
}


int Renderer3D::partition(vector<vector3*> arr, int start, int end)
{
    
    float pivot = average(arr[start]);
 
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (average(arr[i]) <= pivot)
            count++;
    }
 
    //Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);
 
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (average(arr[i]) <= pivot) {
            i++;
        }
 
        while (average(arr[i]) > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--]);
        }
    }
 
    return pivotIndex;
}

float Renderer3D::average(vector3 in[3]) {
    return (in[0].z + in[1].z + in[2].z) / 3;
}
 

void Renderer3D::quickSort(vector<vector3*> arr, int start, int end)
{
 
    // base case
    if (start >= end)
        return;
 
    // partitioning the array
    int p = partition(arr, start, end);
 
    // Sorting the left part
    quickSort(arr, start, p - 1);
 
    // Sorting the right part
    quickSort(arr, p + 1, end);
}











