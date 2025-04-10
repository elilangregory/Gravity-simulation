#pragma once
#include <vector>
#include <array>
#include <cmath>  
#include "AnimationWindow.h"

// basic 3D vector with x y z coordinates, and operator overloading
struct Vec3 {
    float x, y, z;

    Vec3 operator+(const Vec3& other) const;  
    Vec3 operator-(const Vec3& other) const;  
    Vec3 operator*(float scalar) const;       
};

// vector math operations
Vec3 cross(const Vec3& a, const Vec3& b);           
float dot(const Vec3& a, const Vec3& b);            
Vec3 normalize(const Vec3& v);                      

// 3D object data structure
struct Mesh {
    std::vector<Vec3> vertices;// positions
    std::vector<std::array<int, 3>> triangles;// triangle corners
};

// projects 3D point to 2D screen space
TDT4102::Point project(const Vec3& v, float focalLength = 250.0f, int cx = 400, int cy = 300);

// draw filled triangle mesh w/ shading
void draw_mesh_filled(const Mesh& mesh, TDT4102::AnimationWindow& win, TDT4102::Color baseColor);

// makes sphere using mesh 
Mesh generate_sphere_mesh(int latitudeSteps, int longitudeSteps, float radius);