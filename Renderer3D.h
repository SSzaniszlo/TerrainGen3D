#include "SDL.h"
#include "Structs.h"

class Renderer3D {
    public:
        Renderer3D(){};
        Renderer3D(int width, int height);
        bool init();
        void render(mesh m);

        vector3 camPos;

    private:
        
        vector2 calculatedProjected(vector3 point);
        void drawTriangle(vector2 p0, vector2 p1, vector2 p2);
        int WIDTH;
        int HEIGHT;
        
        SDL_Window* window;
        SDL_Renderer* renderer;
        
};