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
        
        vector3 calculatedProjected(vector3 point);
        void drawTriangle(vector3 p0, vector3 p1, vector3 p2);

        int partition(std::vector<vector3*> arr, int start, int end);
        void quickSort(std::vector<vector3*> arr, int start, int end);
        float average(vector3 in[3]);

        int WIDTH;
        int HEIGHT;
        
        SDL_Window* window;
        SDL_Renderer* renderer;
        
};