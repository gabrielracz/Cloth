#include"../include/spring.hpp"


Spring::Spring(Mass *mass1, Mass *mass2, float springConstant, float springlength){
    this->mass1 = mass1;
    this->mass2 = mass2;
    this->springConstant = springConstant;
    this->springlength = springlength;
    this->tear = false;
}

void Spring::solve(float dt){
    // Fs = -k (x - l)
    // k = springConstant, x = positionDelta, l = springlength

    Vector2D deltaPos = mass1->position - mass2->position;
    float r = deltaPos.getLength();
    Vector2D springForce = (deltaPos / r) * (-(springlength - r)) * (-springConstant);
    Vector2D netForce = springForce + (-((mass1->velocity) - (mass2->velocity))) * 0.4;

    if (!mass1->anchored){
        mass1->applyForce(netForce, dt);
        mass1->move(dt);
    }
    if (!mass2->anchored){
        Vector2D oppForce = -netForce;
        mass2->applyForce(oppForce, dt);
        mass2->move(dt);
    }
}

void Spring::move(){
}

void Spring::draw(sf::RenderWindow *window){
    // sf::Color color (0xE0D7CAff);
    sf::Color color (0xFFFFFFFF);
    //sf::Color color (255, 255, 255, 255);

    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(mass1->position.x, mass1->position.y), color),
        sf::Vertex(sf::Vector2f(mass2->position.x, mass2->position.y), color)
    };
    window->draw(line, 2, sf::Lines);
}

bool Spring::check_tear(){
    if(!(mass1->anchored || mass2->anchored) && mass1->position.getDistance(mass2->position) > springlength * 5){    //change this to be some force requirement
        tear = true;
        return true;
    }else{
        return false;
    }   
}

bool Spring::check_collision(Vector2D comp){
    //find midpoint of spring
    //compare that with some square hitbox to comp

    Vector2D midpoint ( (mass1->position.x + mass2->position.x)/2, (mass1->position.y + mass2-> position.y)/2);
    int w = 4;
    if(midpoint.x > comp.x - w && midpoint.x < comp.x + w && midpoint.y > comp.y - w && midpoint.y < comp.y + w){
        tear = true;
        return true;
    }
    else{
        return false;
    }
}
