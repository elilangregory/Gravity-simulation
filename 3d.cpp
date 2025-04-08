#include "3d.h"
#include <cmath>

// ---------- Vec3 operators ----------
Vec3 Vec3::operator+(const Vec3& other) const {
    return {x + other.x, y + other.y, z + other.z};
}

Vec3 Vec3::operator-(const Vec3& other) const {
    return {x - other.x, y - other.y, z - other.z};
}

Vec3 Vec3::operator*(float s) const {
    return {x * s, y * s, z * s};
}

// ---------- Project 3D to 2D ----------
TDT4102::Point project(const Vec3& v, float focalLength, int cx, int cy) {
    return {
        static_cast<int>(focalLength * v.x / v.z + cx),
        static_cast<int>(focalLength * v.y / v.z + cy)
    };
}

void draw_mesh_filled(const Mesh& mesh, TDT4102::AnimationWindow& win, TDT4102::Color color) {
    for (const auto& tri : mesh.triangles) {
        TDT4102::Point p1 = project(mesh.vertices[tri[0]]);
        TDT4102::Point p2 = project(mesh.vertices[tri[1]]);
        TDT4102::Point p3 = project(mesh.vertices[tri[2]]);
        win.draw_triangle(p1, p2, p3, color);
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