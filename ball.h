#pragma once
#include "std_lib_facilities.h"
#include "AnimationWindow.h"

class Ball{
    private:
    TDT4102::Point position;
    int radius;
    float xVelocity;
    float yVelocity;
    int windowWidth;
    int windowHeight;
    TDT4102::Color color;
    float mass;

        
    public:
        Ball(Point startPos, int rad, float xVel, float yVel, int winW, int winH, TDT4102::Color col, float mass);
        void update();
        void draw(AnimationWindow& window);

        TDT4102::Point get_position() const;
        void reverse_velocity();
        bool check_collision_with(const Ball& other) const;
        void apply_gravity_from(const Ball& other, float G = 1.0f);


};
