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
    Vec3 lightDir = normalize({0, 0, -1}); // Lys kommer rett fra kameraet

    for (const auto& tri : mesh.triangles) {
        Vec3 a = mesh.vertices[tri[0]];
        Vec3 b = mesh.vertices[tri[1]];
        Vec3 c = mesh.vertices[tri[2]];

        // Normal fra kryssprodukt
        Vec3 u = b - a;
        Vec3 v = c - a;
        Vec3 normal = normalize(cross(u, v));

        // Lysstyrke = dot(normal, lysretning)
        float brightness = std::max(0.0f, dot(normal, lightDir));
        int shade = static_cast<int>(brightness * 255);  // Fra 0 → 255

        // Lys blåfarge avhengig av lysstyrke
        TDT4102::Color shadedColor{0, 0, static_cast<unsigned char>(shade)};

        TDT4102::Point p1 = project(a);
        TDT4102::Point p2 = project(b);
        TDT4102::Point p3 = project(c);
        win.draw_triangle(p1, p2, p3, shadedColor);
    }
}

Mesh generate_sphere_mesh(int latitudeSteps, int longitudeSteps, float radius) {
    Mesh mesh;

    // Generer punkter
    for (int i = 0; i <= latitudeSteps; ++i) {
        float theta = M_PI * i / latitudeSteps; // 0 → pi
        for (int j = 0; j <= longitudeSteps; ++j) {
            float phi = 2 * M_PI * j / longitudeSteps; // 0 → 2pi

            float x = radius * sin(theta) * cos(phi);
            float y = radius * sin(theta) * sin(phi);
            float z = radius * cos(theta);

            mesh.vertices.push_back({x, y, z+ 3.0f});
        }
    }

    // Generer triangler mellom punktene
    for (int i = 0; i < latitudeSteps; ++i) {
        for (int j = 0; j < longitudeSteps; ++j) {
            int current = i * (longitudeSteps + 1) + j;
            int next = current + longitudeSteps + 1;

            mesh.triangles.push_back({current, next, current + 1});
            mesh.triangles.push_back({current + 1, next, next + 1});
        }
    }

    return mesh;
}   