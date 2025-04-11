# TDT4102 Gravity Simulation – Final Project

This project simulates a simple solar system with a sun, a planet, and a moon in orbit. The program uses a combination of 2D and 3D graphics via the AnimationWindow library. The simulation is physics-based and applies Newton’s law of universal gravitation to replicate the interaction between the objects.

Disclaimer: Although Newton’s law is implemented and gravity between the Earth and the Sun is simulated, real-world values for mass, radius, and distance have not been used. Instead, values were scaled to produce similar behavior visually. Due to these adjustments, the moon’s gravitational behavior did not behave as desired, and it was therefore hardcoded to follow a simple orbit instead.

⸻

## Structure and Key Files

The project consists of three main components, each implemented in its own header file:

### ball.h

This class represents a 2D ball used in early experiments (case 1–4). It contains methods like update() to update position based on velocity, draw() to draw the ball, and apply_gravity_from() to simulate gravitational attraction between balls. These tests formed the foundation of the project, where I experimented with Newton’s laws, collisions, and basic gravitational dynamics.

### 3d.h

This file defines structures and functions for 3D visualization. Vec3 represents a 3D vector and includes overloaded operators such as +, -, and * to make vector math easier.

The project() function is particularly interesting: it uses perspective projection to convert a 3D point into a 2D screen coordinate. The draw_mesh_filled() function utilizes standard computer graphics techniques to draw a shaded triangle mesh that visually approximates a sphere. Shading is calculated using the dot product between the surface normal and a light direction vector to simulate lighting.

Another key function is generate_sphere_mesh(), which creates a sphere represented as a mesh of small triangles. It uses two nested loops to iterate over latitude (theta) and longitude (phi) angles and places points evenly on the surface of a 3D sphere. These points are then connected to form triangles that define the full surface of the mesh.

### celestial_body.h

This is the object-oriented foundation of the project. CelestialBody is an abstract base class representing astronomical bodies. It defines virtual functions such as update_position(), apply_gravity_from(), and type(), allowing derived classes (Sun, Planet, Moon) to override behavior. For example, the Sun does not move, the Planet can throw an exception if it escapes the system, and the Moon moves more slowly than other bodies.

⸻

### Case 8 – Final Demo

The main demonstration (case 8) shows a planet orbiting a sun based on physics. The moon follows a hardcoded orbit around the planet. Trajectories are visualized using vectors, and the 3D illusion is enhanced through lighting and shading. Object color and behavior are influenced by their mass and classification. The simulation also supports a “slingshot” scenario, where the Earth’s starting velocity is slightly decreased, allowing it to start orbit, and then when it comes closer to the sun it is thrown away fast, before it slowly returns to the new orbit. Try it yourself!

⸻

### Summary

This project demonstrates:

    Inheritance 
	Vector math and 3D transformation
	Application of Newton’s law of gravity
    Use of a graphical user interface
	Exception handling in physics simulation

No code was fully AI-generated, but I used ChatGPT as a sparring partner while writing the draw_mesh_filled() function and exploring computer graphics concepts. I learned how perspective projection and vector-based shading work mathematically, and received some assistance when writing draw_mesh_filled() function.