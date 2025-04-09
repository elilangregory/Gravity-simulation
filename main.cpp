#include "AnimationWindow.h"
#include <iostream>
#include "ball.h"
#include "3d.h"
#include "celestial_body.h"
#include <vector>

int main() {
    int choice;
    std::cout << "Choose which one u wanna run:\n";
    std::cout << "1: Bouncing ball\n";
    std::cout << "2: Bouncing ball with 2 balls\n";
    std::cout << "3: Bouncing balls with collision\n";
    std::cout << "4: Gravity test\n";
    std::cout << "5 3d build\n";
    std::cout << "6 3d build and orbit\n";
    std::cout << "7 Static sun\n";
    std::cout << "8 Sun + orbiting planet\n";
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
        break;}

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
        break;}      

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
        break;}

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
        constexpr int width = 800;
        constexpr int height = 600;
    
        TDT4102::AnimationWindow window{100, 100, width, height, "3D Orbiting Sphere"};
        Mesh sphere = generate_sphere_mesh(20, 20, 1.0f);
    
        float theta = 0.0f;
        float orbitRadius = 9.0f;
        Vec3 center = {0.0f, 0.0f, 6.0f}; // 3D-senter som er synlig foran kamera
    
        while (!window.should_close()) {
            window.draw_rectangle({0, 0}, width, height, TDT4102::Color::black);
    
            // Beregn ny posisjon på banen
            Vec3 orbitPos = {
                center.x + orbitRadius * cos(theta),
                center.y,
                center.z + orbitRadius * sin(theta)
            };
    
            // Kopiér og flytt kula til ny bane-posisjon
            Mesh movedSphere = sphere;
            for (auto& v : movedSphere.vertices) {
                v = v + orbitPos;
            }
    
            draw_mesh_filled(movedSphere, window);
            theta += 0.02f;
    
            window.next_frame();
        }
        break;
    }

        case 7: {
        try {
            constexpr int width = 800;
            constexpr int height = 600;
            TDT4102::AnimationWindow window{100, 100, width, height, "Static Sun"};
    
            // Lag bare sola – ingen bevegelse
            Sun sun(
                Vec3{0.0f, 0.0f, 6.0f},   // posisjon i senter foran kamera
                Vec3{0.0f, 0.0f, 0.0f},   // ingen hastighet
                10000.0f,                 // stor masse
                1.5f                      // radius på kule
            );
    
            while (!window.should_close()) {
                window.draw_rectangle({0, 0}, width, height, TDT4102::Color::black);
    
                // Tegn sola
                Mesh moved = sun.mesh;
                for (auto& v : moved.vertices) {
                    v = v + sun.position;
                }
                draw_mesh_filled(moved, window, TDT4102::Color::yellow);
    
                window.next_frame();
            }
    
        } catch (const std::exception& e) {
            std::cerr << "[FATAL] Simulation failed: " << e.what() << std::endl;
        }
        break;
    }

        case 8: {
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
    
            // Planet object created with start position and velocirt
            Planet planet(
                Vec3{10.0f, 0.0f, 6.0f},     // 10 units bort
                Vec3{0.0f, 0.1f, 0.0f},      // oppover fart
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
    
                        // debug: in case program crash or weird behaviour from planets path (check acceleration, velocity and Gravity constant from newtons law)
                        if (body->type() == "Planet") {
                            std::cout << "Planet pos: ("
                                      << body->position.x << ", "
                                      << body->position.y << ", "
                                      << body->position.z << ")\n";
                        }
    
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
            std::cerr << "[Simulation failed: Unknown failure!!!" << std::endl;
        }
        break;
    }

        case 9: {
        try {
            constexpr int width = 800;
            constexpr int height = 600;
            TDT4102::AnimationWindow window{100, 100, width, height, "Sun + Earth + Moon (with trails)"};
    
            float G = 0.1f;
            float theta = 0.0f;
    
            // Sun i sentrum
            Vec3 sunPos = {0.0f, 0.0f, 6.0f};
            Mesh sunMesh = generate_sphere_mesh(20, 20, 1.5f);
    
            // Planetens bane
            float planetOrbitRadius = 10.0f;
            Mesh planetMesh = generate_sphere_mesh(20, 20, 0.5f);
    
            // Månens bane (30x raskere)
            float moonOrbitRadius = 1.2f;
            Mesh moonMesh = generate_sphere_mesh(20, 20, 0.2f);
    
            std::vector<TDT4102::Point> planetTrail;
            std::vector<TDT4102::Point> moonTrail;
    
            while (!window.should_close()) {
                window.draw_rectangle({0, 0}, width, height, TDT4102::Color::black);
    
                // Beregn posisjon for planet
                Vec3 planetPos = {
                    sunPos.x + planetOrbitRadius * std::cos(theta),
                    0.0f,
                    sunPos.z + planetOrbitRadius * std::sin(theta)
                };
    
                // Beregn posisjon for måne
                float moonAngle = 30.0f * theta;
                Vec3 moonPos = {
                    planetPos.x + moonOrbitRadius * std::cos(moonAngle),
                    0.0f,
                    planetPos.z + moonOrbitRadius * std::sin(moonAngle)
                };
    
                // Lagre prosjektert punkt for banetegning
                planetTrail.push_back(project(planetPos));
                moonTrail.push_back(project(moonPos));
    
                // Tegn sol
                Mesh sunMoved = sunMesh;
                for (auto& v : sunMoved.vertices) v = v + sunPos;
                draw_mesh_filled(sunMoved, window, TDT4102::Color::yellow);
    
                // Tegn planet
                Mesh planetMoved = planetMesh;
                for (auto& v : planetMoved.vertices) v = v + planetPos;
                draw_mesh_filled(planetMoved, window, TDT4102::Color::blue);
    
                // Tegn måne
                Mesh moonMoved = moonMesh;
                for (auto& v : moonMoved.vertices) v = v + moonPos;
                draw_mesh_filled(moonMoved, window, TDT4102::Color::white);
    
                // Tegn stier
            //   for (size_t i = 1; i < planetTrail.size(); ++i) {
            //       window.draw_line(planetTrail[i - 1], planetTrail[i], TDT4102::Color::blue);
            //   }
            //   for (size_t i = 1; i < moonTrail.size(); ++i) {
            //       window.draw_line(moonTrail[i - 1], moonTrail[i], TDT4102::Color::gray);
            //  }
    
                 theta += 0.01f;
               window.next_frame();
            }
        } catch (const std::exception& e) {
            std::cerr << "[FATAL] Simulation failed: " << e.what() << std::endl;
        }
        break;
    }

    
        default:
            std::cout << "Invalid choice.\n";
            break;
    }

    return 0;
}