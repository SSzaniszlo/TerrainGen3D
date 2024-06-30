#include <vector>

struct vector2 {
    float x;float y;
};

struct vector3 {
    float x;float y;float z;
};

struct tri {
    vector3 points[3];
};

struct mesh {
    std::vector<tri> tris;
};
