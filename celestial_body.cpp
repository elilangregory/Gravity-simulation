#include "celestial_body.h"
#include <stdexcept>
#include <cmath>
#include <iostream>

// constructor generates the 3D mesh sphere based on radius
CelestialBody::CelestialBody(Vec3 pos, Vec3 vel, float mass, float radius)
    : position(pos), velocity(vel), mass(mass) {
    mesh = generate_sphere_mesh(20, 20, radius);
}

// base class update position inherit all function
void CelestialBody::update_position() {
    position = position + velocity;
}

// gravity according to Newton's law of universal gravitation
void CelestialBody::apply_gravity_from(const CelestialBody& other) {
    try {
        Vec3 direction = other.position - position;
        float distanceSquared = direction.x * direction.x + direction.y * direction.y + direction.z * direction.z;

        if (distanceSquared == 0.0f) {
            throw std::runtime_error("Division by zero in gravity calculation");
        }

        Vec3 forceDir = normalize(direction); 
        float G = 0.01f; // scaled gravitational constant 
        Vec3 acceleration = forceDir * (G * other.mass / distanceSquared);  //newtons universal law of gravity adapted for simulation

        velocity = velocity + acceleration; // v = v0 + a*delta_t, where delta_t is 1 per frame (for simplicity)

    } catch (const std::exception& e) {
        std::cerr << "Gravity error in " << type() << ": " << e.what() << std::endl;
    }
}

// Planet throws exception if too far away 
void Planet::update_position() {
    position = position + velocity;

    float dist = std::sqrt(position.x * position.x + position.y * position.y + position.z * position.z);
    if (dist > 50.0f) {
        throw std::runtime_error("Planet has escaped the system!");
    }
}

// Moon moves slower – just for visual difference
void Moon::update_position() {
    position = position + velocity * 0.5f;
}