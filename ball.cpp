#include "ball.h"

using namespace TDT4102;
    
Ball::Ball(Point startPos, int rad, int xVel, int yVel, int winW, int winH, TDT4102::Color col )
    : position(startPos), radius(rad), xVelocity(xVel), yVelocity(yVel),
          windowWidth(winW), windowHeight(winH), color(col) {}
    
void Ball::update() {
    position.x += xVelocity;
    position.y += yVelocity;
    
    if (position.x - radius <= 0 || position.x + radius >= windowWidth) {
        xVelocity = -xVelocity;
        }
    if (position.y - radius <= 0 || position.y + radius >= windowHeight) {
        yVelocity = -yVelocity;
        }
    }
    
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
