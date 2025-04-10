#include "AnimationWindow.h"
#include "ball.h"
#include "3d.h"
#include "celestial_body.h"
#include <iostream>

int main() {
    int choice;
    std::cout << "Choose which one u wanna run:\n";
    std::cout << "1: Bouncing ball\n";
    std::cout << "2: Bouncing ball with 2 balls\n";
    std::cout << "3: Bouncing balls with collision\n";
    std::cout << "4: Gravity test\n";
    std::cout << "5: 3d sphere build test\n";
    std::cout << "6: Static sun\n";
    std::cout << "7: Sun + earth orbit\n";
    std::cout << "8: FINAL PRODUCT:\nSun + earth and moon orbit, and trajectory line added\n";
    std::cout << "Write a number and press Enter: ";
    std::cin >> choice;

    switch (choice) {
        case 1:{
        constexpr int width = 800;
        constexpr int height = 600;
        int rad = 20;
        float xVel = 2;
        float yVel = 5;
        // test of bouncing ball
        void run_bouncing_ball();{
            TDT4102::AnimationWindow window{100, 100, width, height, "Bouncing Ball"};
            Ball ball({width / 2, height / 2}, rad, xVel, yVel, width, height, Color::aqua, 5.0);
    
             while (!window.should_close()) {
             ball.update();
             ball.draw(window);
             window.next_frame();}
            }
        break;}

        case 2:{
            // same as the other one but with two instance of ball
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
        break;}      

        case 3: {
            constexpr int width = 800;
            constexpr int height = 600;
            const int rad = 20;

            TDT4102::AnimationWindow window{100, 100, width, height, "Collision Test"};

            // To baller med ulik posisjon, hastighet og farge
            // two instance of ball, with different start position, velocity and color
            Ball ball1({200, 300}, rad, 2, 3, width, height, TDT4102::Color::red, 5.0f);
            Ball ball2({100, 300}, rad, 4, 3, width, height, TDT4102::Color::blue, 5.0f);

            while (!window.should_close()) {
                ball1.update();
                ball2.update();

            // checks for collision and reverse velocity if so
            if (ball1.check_collision_with(ball2)) {
                ball1.reverse_velocity();
                ball2.reverse_velocity();
            }

            ball1.draw(window);
            ball2.draw(window);
            
            window.next_frame();
            }
        break;}

        case 4: {
        constexpr int width = 800;
        constexpr int height = 600;

        TDT4102::AnimationWindow window{100, 100, width, height, "Gravity Test"};

        Ball bigBall({width / 2, height / 2}, 30, 1, 1, width, height, Color::yellow, 2000.0f);  // big ball
        Ball smallBall({100, 500}, 20, 3, 3, width, height, Color::aqua, 1.0f); // small

        while (!window.should_close()) {
        
            // black background
            window.draw_rectangle(Point{0, 0}, width, height, Color::black);
        
            // small ball is affected by big balls gravity
            smallBall.apply_gravity_from(bigBall);

            bigBall.update();
            smallBall.update();

            bigBall.draw(window);
            smallBall.draw(window);

            window.next_frame();
        }
        break;
    }
   
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
    break;}

        case 6: {
        try {
            constexpr int width = 800;
            constexpr int height = 600;
            TDT4102::AnimationWindow window{100, 100, width, height, "Static Sun"};
    
            // instatiating sun object
            Sun sun(
                Vec3{0.0f, 0.0f, 6.0f}, //position
                Vec3{0.0f, 0.0f, 0.0f},// velocity equal zero
                100.0f, //mass
                1.5f // radius
            );
    
            while (!window.should_close()) {
                window.draw_rectangle({0, 0}, width, height, TDT4102::Color::black);
    
                // draw sun object
                Mesh moved = sun.mesh;
                for (auto& v : moved.vertices) {
                    v = v + sun.position;
                }
                draw_mesh_filled(moved, window, TDT4102::Color::yellow);
    
                window.next_frame();
            }
    
        } catch (const std::exception& e) {
            std::cerr << "Simulation failed: " << e.what() << std::endl;
        }
        break;
    }

        case 7: {
        try {
            constexpr int width = 800;
            constexpr int height = 600;
            TDT4102::AnimationWindow window{100, 100, width, height, "Sun + earth orbit planet"};
    
            // The sun stays in the middle
            Sun sun(
                Vec3{0.0f, 0.0f, 6.0f},
                Vec3{0.0f, 0.0f, 0.0f},
                10.0f,
                1.5f
            );
    
            // Planet object created with start position and velociry
            Planet planet(
                Vec3{10.0f, 0.0f, 6.0f}, //10 enheter from the sun in x direction     
                Vec3{0.0f, 0.1f, 0.0f}, // slight speed in y 
                1.0f,
                0.5f
            );
    
            std::vector<CelestialBody*> bodies = {&sun, &planet};
    
            while (!window.should_close()) {
                window.draw_rectangle({0, 0}, width, height, TDT4102::Color::black);
    
                // Gravity
                for (auto* body : bodies) {
                    for (auto* other : bodies) {
                        if (body != other) {
                            try {
                                body->apply_gravity_from(*other);
                            } catch (const std::exception& e) {
                                std::cerr << "Gravity error" << body->type() << ": " << e.what() << std::endl;
                            }
                        }
                    }
                }

                // Update and draw
                for (auto* body : bodies) {
                    try {
                        body->update_position();
    
                        // debug: in case program crash or 
                        //weird behaviour from planets path (check acceleration, velocity and Gravity constant from newtons law)
                        //you can log planets position to the console 
                        /*
                        if (body->type() == "Planet") {
                            std::cout << "Planet pos: ("
                                      << body->position.x << ", "
                                      << body->position.y << ", "
                                      << body->position.z << ")\n";
                        }
                        */
                        Mesh moved = body->mesh;
                        for (auto& v : moved.vertices) {
                            v = v + body->position;
                        }
    
                        TDT4102::Color color;
                        if (body->type() == "Sun") {
                            color = TDT4102::Color::yellow;
                        } else {
                            color = TDT4102::Color::blue;
                            }
                        draw_mesh_filled(moved, window, color);
    
                    } catch (const std::exception& e) {
                        std::cerr << "Update error" << body->type() << ": " << e.what() << std::endl;
                    }
                }
    
                window.next_frame();
            }
        } catch (const std::exception& e) {
            std::cerr << "Simulation failed: Unknown failure!!!" << std::endl;
        }
        break;
    }

        case 8: {
            std::cout << "Do you want to see the normal version or the slingshot version?\n";
            std::cout << "For normal, press 1 and enter, for slingshot press 2 and enter\n";

            int sling_choice;
            std::cin >> sling_choice;
            float sling;
            
            if (sling_choice == 2) {sling = 0.05f;}
            else {sling = 0.1f;}
    

        try {
        
            constexpr int width = 800;
            constexpr int height = 600;
            TDT4102::AnimationWindow window{100, 100, width, height, "Sun + orbiting planet + moon"};
    
            Sun sun(
                Vec3{0.0f, 0.0f, 6.0f},
                Vec3{0.0f, 0.0f, 0.0f},
                10.0f,
                1.5f
            );
    
            Planet planet(
                Vec3{10.0f, 0.0f, 6.0f},
                Vec3{0.0f, sling, 0.0f}, // 0.1 v.y for ideal orbit, 0.05 for a funny slingshot
                1.0f,
                0.5f
            );
    
            Moon moon(
                Vec3{11.2f, 0.0f, 6.0f}, // Start slightly offset
                Vec3{0.0f, 0.0f, 0.0f},
                0.1f,
                0.2f
            );
    
            std::vector<CelestialBody*> bodies = {&sun, &planet};
    
            std::vector<TDT4102::Point> planetTrail;
            std::vector<TDT4102::Point> moonTrail;
    
            int frame = 0;
    
            while (!window.should_close()) {
                window.draw_rectangle({0, 0}, width, height, TDT4102::Color::black);
                frame++;
    
                // Apply gravity
                for (auto* body : bodies) {
                    for (auto* other : bodies) {
                        if (body != other) {
                            body->apply_gravity_from(*other);
                        }
                    }
                }
    
                for (auto* body : bodies) {
                    body->update_position();
                }
    
                // Hardcoded moon orbiting the planet (not using gravity) due to the imbalance of the physics
                float moonAngle = 30.0f * frame * 0.01f;
                moon.position = {
                    planet.position.x + 1.2f * std::cos(moonAngle),
                    planet.position.y + 1.2f * std::sin(moonAngle),
                    planet.position.z
                };
    
                // draw trajectory of planet and moon
                planetTrail.push_back(project(planet.position));
                moonTrail.push_back(project(moon.position));
                
                //limit the trail vector to 200 points
                if (planetTrail.size() > 200) {
                    planetTrail.erase(planetTrail.begin());}

                if (moonTrail.size() > 200){
                    moonTrail.erase(moonTrail.begin()); }
    
                for (int i = 1; i < planetTrail.size(); ++i) {
                    window.draw_line(planetTrail[i - 1], planetTrail[i], TDT4102::Color::purple);
                }
    
                for (int i = 1; i < moonTrail.size(); ++i) {
                    window.draw_line(moonTrail[i - 1], moonTrail[i], TDT4102::Color::aquamarine);
                }
    
                // Draw all objects
                std::vector<CelestialBody*> drawables = {&sun, &planet, &moon};
                for (auto* body : drawables) {
                    Mesh moved = body->mesh;
                    for (auto& v : moved.vertices) {
                        v = v + body->position;
                    }
    
                    TDT4102::Color color = TDT4102::Color::gray;
                    if (body->type() == "Sun") {color = TDT4102::Color::yellow;}
                    else if (body->type() == "Planet") {color = TDT4102::Color::blue;}
    
                    draw_mesh_filled(moved, window, color);
                }
    
                window.next_frame();
            }
        } catch (const std::exception& e) {
            std::cerr << "[Simulation failed] " << e.what() << std::endl;
        }
        break;
    }

        default:
            std::cout << "Invalid choice.\n";
            break;
    }

    return 0;
}