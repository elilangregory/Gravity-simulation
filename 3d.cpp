#include "3d.h"
#include <cmath>



Vec3 Vec3::operator+(const Vec3& other) const {
    return {x + other.x, y + other.y, z + other.z};
}

Vec3 Vec3::operator-(const Vec3& other) const {
    return {x - other.x, y - other.y, z - other.z};
}

Vec3 Vec3::operator*(float s) const { // multiplying vector with a scalar s
    return {x * s, y * s, z * s}; 
}

Vec3 cross(const Vec3& a, const Vec3& b) { //crossproduct of vector a and b to find the orthogonal vector
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

Vec3 normalize(const Vec3& v) { // normalize the vector so the length = 1
    float length = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (length == 0.0f) return {0, 0, 0};
    return {v.x / length, v.y / length, v.z / length};
}

float dot(const Vec3& a, const Vec3& b) { // dotproduct of vector a and b
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

TDT4102::Point project(const Vec3& v, float focalLength, int cx, int cy) { // Projects a 3D point to 2D screen coordinates using perspective projection
    return {
        static_cast<int>(focalLength * v.x / v.z + cx), // focalLength controls the zoom, (cx, cy) is the screen center since animation window (0,0) point is in left top corner.
        static_cast<int>(focalLength * v.y / v.z + cy)
    };
}

void draw_mesh_filled(const Mesh& mesh, TDT4102::AnimationWindow& win, TDT4102::Color baseColor) {
    Vec3 lightDir = normalize({0, 0, -1}); // Light from camera

    // vector made by the triangle coordinates
    for (const auto& tri : mesh.triangles) {
        Vec3 a = mesh.vertices[tri[0]];
        Vec3 b = mesh.vertices[tri[1]];
        Vec3 c = mesh.vertices[tri[2]];

        //finding the ortogonal vector on the plane span by the triangle, and then normalize it.
        Vec3 u = b - a;
        Vec3 v = c - a;
        Vec3 normal = normalize(cross(u, v));

        // Taking the dot product between two normalized vectors gives the cosine of the angle between them.
        // We use this to compute brightness based on how directly a surface faces the light.
        float brightness = std::max(0.0f, dot(normal, lightDir)); 

        int r = static_cast<int>((baseColor.redChannel + 10) * brightness);
        int g = static_cast<int>((baseColor.greenChannel + 10) * brightness);
        int bCol = static_cast<int>((baseColor.blueChannel + 10) * brightness);

        if (r > 255) r = 255;
        if (g > 255) g = 255;
        if (bCol > 255) bCol = 255;


        // Construct shaded color
        TDT4102::Color shadedColor{
            static_cast<unsigned char>(r),
            static_cast<unsigned char>(g),
            static_cast<unsigned char>(bCol),
        };

        TDT4102::Point p1 = project(a);
        TDT4102::Point p2 = project(b);
        TDT4102::Point p3 = project(c);
        // draw each triangle with the calculated shade 
        win.draw_triangle(p1, p2, p3, shadedColor);
    }
}

Mesh generate_sphere_mesh(int latitudeSteps, int longitudeSteps, float radius) {
    Mesh mesh;

    // Generate points and using M_PI for precise pi value from cmath lib
    for (int i = 0; i <= latitudeSteps; ++i) {
        float theta = M_PI * i / latitudeSteps; // 0 to pi, from northpole to southpole
        for (int j = 0; j <= longitudeSteps; ++j) {
            float phi = 2 * M_PI * j / longitudeSteps; // 0 to 2pi, around the sphere

            // Conversion to 3D coordinates
            float x = radius * sin(theta) * cos(phi);
            float y = radius * sin(theta) * sin(phi);
            float z = radius * cos(theta);

            mesh.vertices.push_back({x, y, z+ 3.0f}); //move the sphere just in case it is on the projection and not divisible by zero
        }
    }

    // Make triangle between points
    for (int i = 0; i < latitudeSteps; ++i) {
        for (int j = 0; j < longitudeSteps; ++j) {
            int current = i * (longitudeSteps + 1) + j; // point in "latitude row"
            int next = current + longitudeSteps + 1; // similar point on the next 

            mesh.triangles.push_back({current, next, current + 1});
            mesh.triangles.push_back({current + 1, next, next + 1});
        }
    }

    return mesh;
}   