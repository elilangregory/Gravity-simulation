#pragma once
#include "std_lib_facilities.h"
#include "AnimationWindow.h"

class Ball{
    private:
    TDT4102::Point position;
    int radius;
    int xVelocity;
    int yVelocity;
    int windowWidth;
    int windowHeight;
    TDT4102::Color color;
        
    public:
        Ball(Point startPos, int rad, int xVel, int yVel, int winW, int winH, TDT4102::Color col = TDT4102::Color::red);
        void update();
        void draw(AnimationWindow& window);

        TDT4102::Point get_position() const;
        void reverse_velocity();
        bool check_collision_with(const Ball& other) const;


};
