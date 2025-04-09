#include "ball.h"

using namespace TDT4102;
    
Ball::Ball(Point startPos, int rad, float xVel, float yVel, int winW, int winH, Color col, float mass)
    : position(startPos), radius(rad), xVelocity(xVel), yVelocity(yVel),
          windowWidth(winW), windowHeight(winH), color(col), mass(mass) {}
    
void Ball::update() {
    position.x += xVelocity;
    position.y += yVelocity;
    // Left wall
    if (position.x - radius <= 0) {
        xVelocity = -xVelocity;
        position.x = radius; 
    }
    //Right wall
    else if (position.x + radius > windowWidth) {
        xVelocity = -xVelocity;
        position.x = windowWidth - radius; 
    }
    //Top 
    if (position.y - radius < 0) {
        yVelocity = -yVelocity;
        position.y = radius; 
    }
    //bottom
    else if (position.y + radius > windowHeight) {
        yVelocity = -yVelocity;
        position.y = windowHeight - 2*radius; 
    }}
    
void Ball::draw(AnimationWindow& window) {
    window.draw_circle(position, radius, color);
    }

TDT4102::Point Ball::get_position() const {
    return position;
}

void Ball::reverse_velocity() {
    xVelocity = -xVelocity;
    yVelocity = -yVelocity;
}

bool Ball::check_collision_with(const Ball& other) const {
    TDT4102::Point otherPos = other.get_position();
    float dx = position.x - otherPos.x;
    float dy = position.y - otherPos.y;
    float distance = std::sqrt(dx * dx + dy * dy);
    int combinedRadius = this->radius + other.radius;

    return distance < combinedRadius;
}

void Ball::apply_gravity_from(const Ball& other, float G) {
    if (this == &other) return;

    Point otherPos = other.get_position();
    float dx = otherPos.x - position.x;
    float dy = otherPos.y - position.y;
    float distanceSquared = dx * dx + dy * dy + 0.001f; // unngå /0

    float force = G * (mass * other.mass) / distanceSquared; //newtons lov om universiell gravitasjon.
    float acceleration = force / mass; // F = ma

    float distance = std::sqrt(distanceSquared);
    float ax = acceleration * dx / distance; // decompose acceleration in ax and ay retning. 
    float ay = acceleration * dy / distance;

    xVelocity += ax; // v = v0 + a * delta_t where delta_t = 1
    yVelocity += ay;
}
