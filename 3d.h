#pragma once
#include "AnimationWindow.h"
#include <cmath>

struct Vec3 {
    float x, y, z;
    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3 operator*(float s) const;
};

struct Mesh {
    std::vector<Vec3> vertices;
    std::vector<std::array<int, 3>> triangles;
};

// Projiserer et 3D-punkt til 2D for visning
TDT4102::Point project(const Vec3& v, float focalLength = 300.0f, int cx = 400, int cy = 300);

// Tegner trekantnett som wireframe
void draw_mesh_filled(const Mesh& mesh, TDT4102::AnimationWindow& win, TDT4102::Color color = TDT4102::Color::yellow);

// Lager en kule av triangler
Mesh generate_sphere_mesh(int latitudeSteps, int longitudeSteps, float radius = 1.0f);