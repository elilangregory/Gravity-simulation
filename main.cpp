//#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include <iostream>
#include "ball.h"
#include "3d.h"
#include <vector>

int main() {
    int choice;
    std::cout << "Choose which one u wanna run:\n";
    std::cout << "1: Bouncing ball\n";
    std::cout << "2: Bouncing ball with 2 balls\n";
    std::cout << "3: Bouncing balls with collision\n";
    std::cout << "4: Gravity test\n";
    std::cout << "5\n";
    std::cout << "Write a number and press Enter: ";
    std::cin >> choice;

    switch (choice) {
        case 1:{
        constexpr int width = 800;
        constexpr int height = 600;
        int rad = 20;
        float xVel = 2;
        float yVel = 5;
        void run_bouncing_ball();{
            TDT4102::AnimationWindow window{100, 100, width, height, "Bouncing Ball"};
            Ball ball({width / 2, height / 2}, rad, xVel, yVel, width, height, Color::aqua, 5.0);
    
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
            Ball ball({width / 2, height / 2}, rad, xVel, yVel, width, height, TDT4102::Color::yellow, 500.0f);
            Ball ball2({width/4, height/ 4}, rad+10, 3, 5, width, height, TDT4102::Color::aqua, 5.0f);
        
            while (!window.should_close()) {
            ball.update();
            ball2.update();
            ball.draw(window);
            ball2.draw(window);
            window.next_frame(); }
            } 
        }   
        break;   


        case 3: {
            constexpr int width = 800;
            constexpr int height = 600;
            const int rad = 20;

            TDT4102::AnimationWindow window{100, 100, width, height, "Collision Test"};

            // To baller med ulik posisjon, hastighet og farge
            Ball ball1({200, 300}, rad, 2, 3, width, height, TDT4102::Color::red, 5.0f);
            Ball ball2({100, 300}, rad, 4, 3, width, height, TDT4102::Color::blue, 5.0f);

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
        break; 

    case 4: {
        constexpr int width = 800;
        constexpr int height = 600;

    TDT4102::AnimationWindow window{100, 100, width, height, "Gravity Test"};

    Ball bigBall({width / 2, height / 2}, 30, 1, 1, width, height, Color::yellow, 2000.0f);  // massiv
    Ball smallBall({100, 500}, 20, 3, 3, width, height, Color::aqua, 1.0f); // liten og rask

    while (!window.should_close()) {
        
        // tegner svart bakgrunn
        window.draw_rectangle(Point{0, 0}, width, height, Color::black);
        
        // Gravitasjon: den lille ballen tiltrekkes av den store
        smallBall.apply_gravity_from(bigBall);

        // Oppdater posisjoner
        bigBall.update();
        smallBall.update();

        // Tegn begge
        bigBall.draw(window);
        smallBall.draw(window);

        window.next_frame();
        }
    }
    break;

    
    case 5: {
        
        constexpr int width = 800;
        constexpr int height = 600;

        TDT4102::AnimationWindow window{100, 100, width, height, "3D Sphere Test"};
        Mesh sphere = generate_sphere_mesh(20, 20, 1.0f);

        while (!window.should_close()) {
            window.draw_rectangle(Point{0, 0}, width, height, Color::black); // tegner svart bakgrunn
            draw_mesh_filled(sphere, window, TDT4102::Color::blue);
            window.next_frame();

        }
    }
    break;

        default:
            std::cout << "Ugyldig valg.\n";
            break;
    }

    return 0;
}