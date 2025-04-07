#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include <iostream>
#include "ball.h"
#include <vector>
#include <cstdlib> // For rand()
#include <ctime>   // For time()


int main() {
    int choice;
    std::cout << "Velg hva du vil teste:\n";
    std::cout << "1: Bouncing ball\n";
    std::cout << "2: Bouncing ball with 2 balls\n";
    std::cout << "3: Bouncing balls with collision\n";
    std::cout << "Skriv tall og trykk Enter: ";
    std::cin >> choice;

    switch (choice) {
        case 1:{
        constexpr int width = 800;
        constexpr int height = 600;
        int rad = 20;
        int xVel = 2;
        int yVel = 5;
        void run_bouncing_ball();{
            TDT4102::AnimationWindow window{100, 100, width, height, "Bouncing Ball"};
            Ball ball({width / 2, height / 2}, rad, xVel, yVel, width, height);
    
             while (!window.should_close()) {
             ball.update();
             ball.draw(window);
             window.next_frame();}
        }
    }
   
            break;

        case 2:{
            // same as the other one but with two balls
            constexpr int width = 800;
            constexpr int height = 600;
            int rad = 20;
            int xVel = 2;
            int yVel = 5;
            void run_bouncing_ball();{
            TDT4102::AnimationWindow window{100, 100, width, height, "Bouncing Ball"};
            Ball ball({width / 2, height / 2}, rad, xVel, yVel, width, height, TDT4102::Color::yellow);
            Ball ball2({width/4, height/ 4}, rad+10, 3, 5, width, height, TDT4102::Color::aqua);
        
            while (!window.should_close()) {
            ball.update();
            ball2.update();
            ball.draw(window);
            ball2.draw(window);
            window.next_frame();
            }
        } 
    }   break;   


        case 3: {
            constexpr int width = 800;
            constexpr int height = 600;
            const int rad = 20;

    TDT4102::AnimationWindow window{100, 100, width, height, "Collision Test"};

    // To baller med ulik posisjon, hastighet og farge
    Ball ball1({200, 300}, rad, 2, 3, width, height, TDT4102::Color::red);
    Ball ball2({100, 300}, rad, 4, 3, width, height, TDT4102::Color::blue);

    while (!window.should_close()) {
        // Oppdater begge baller
        ball1.update();
        ball2.update();

        // Sjekk kollisjon og reager
        if (ball1.check_collision_with(ball2)) {
            ball1.reverse_velocity();
            ball2.reverse_velocity();
        }

        // Tegn begge baller
        ball1.draw(window);
        ball2.draw(window);

        window.next_frame();
    }
        }

    case 4: {

        constexpr int width = 800;
    constexpr int height = 600;
    constexpr int numBalls = 10;

    TDT4102::AnimationWindow window{100, 100, width, height, "Many Balls with Collision"};
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed for random

    std::vector<Ball> balls;

    // 🎯 Lag mange baller med tilfeldige startverdier
    for (int i = 0; i < numBalls; ++i) {
        int radius = 10 + std::rand() % 15;
        int x = radius + std::rand() % (width - 2 * radius);
        int y = radius + std::rand() % (height - 2 * radius);
        int vx = (std::rand() % 5 + 1) * (std::rand() % 2 == 0 ? 1 : -1);
        int vy = (std::rand() % 5 + 1) * (std::rand() % 2 == 0 ? 1 : -1);
        TDT4102::Color color = static_cast<TDT4102::Color>(std::rand() % 16);

        balls.emplace_back(TDT4102::Point{x, y}, radius, vx, vy, width, height, color);
    }

    // 🌀 Hovedløkke
    while (!window.should_close()) {
        // Oppdater og tegn alle baller
        for (auto& ball : balls) {
            ball.update();
            ball.draw(window);
        }

        // Kollisjonssjekk mellom alle ball-par
        for (size_t i = 0; i < balls.size(); ++i) {
            for (size_t j = i + 1; j < balls.size(); ++j) {
                if (balls[i].check_collision_with(balls[j])) {
                    balls[i].reverse_velocity();
                    balls[j].reverse_velocity();
                }
            }
        }

        window.next_frame();
    }

    }

        default:
            std::cout << "Ugyldig valg.\n";
            break;
    }

    return 0;
}