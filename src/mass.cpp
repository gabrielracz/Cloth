#include"../include/mass.hpp"

Mass::Mass(float x, float y, float mass){
    m = mass;
    position = Vector2D(x, y);
    // position = new Vector2D(x, y);
    // velocity = new Vector2D();
    // acceleration = new Vector2D();
    anchored = false;
}

void Mass::draw(sf::RenderWindow *window){
    float r = 2; //fmax(m/2, 2);
    sf::CircleShape circle(r);
    circle.setOrigin(r, r);
    circle.setPosition(sf::Vector2f(position.x, position.y));
    window->draw(circle);
}

void Mass::solve(float dt){
    Vector2D gravity(0, 9.8 * m);
    Vector2D airResistance = velocity * -0.0075;
    Vector2D forceNet = gravity + airResistance;

    applyForce(forceNet, dt);
}

void Mass::applyForce(Vector2D &force, float dt){
    //a = F/m
    acceleration = force * 1 / m; //Acceleration due to current
    velocity = velocity + (acceleration * (dt));
}

void Mass::move(float dt){
    position = position + velocity * dt;
}
