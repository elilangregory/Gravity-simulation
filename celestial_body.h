#pragma once
#include "3d.h"
#include <iostream>
#include <stdexcept>

// base class for all celestial objects
class CelestialBody {
public:
    Vec3 position;
    Vec3 velocity;
    float mass;
    Mesh mesh;

    CelestialBody(Vec3 pos, Vec3 vel, float mass, float radius);

    // update motion (can be overridden by subclasses)
    virtual void update_position();

    // apply gravity from another body
    virtual void apply_gravity_from(const CelestialBody& other);

    // for try catch and identification
    virtual std::string type() const = 0;

    virtual ~CelestialBody() = default; // virtual destructor just for safety, just in case
};

// planet has same logic as base, but can throw if too far away
class Planet : public CelestialBody {
public:
    using CelestialBody::CelestialBody;

    void update_position() override;
    std::string type() const override { return "Planet"; }
};

// sun will stay static at the center
class Sun : public CelestialBody {
public:
    using CelestialBody::CelestialBody;

    void update_position() override {} 
    std::string type() const override { return "Sun"; }
};

class Moon : public CelestialBody {
public:
    using CelestialBody::CelestialBody;

    void update_position() override;
    std::string type() const override { return "Moon"; }
};