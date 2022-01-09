#include"../include/vector2D.hpp"
#include"../include/mass.hpp"

Mass::Mass(float x, float y, float mass){
    m = mass;
    position = Vector2D(x, y);
    anchored = false;
    grabbed = false;
}

void Mass::Solve(float dt){
    Vector2D gravity(0, 9.8 * m);
    Vector2D airResistance = velocity * -0.0075;
    Vector2D forceNet = gravity + airResistance;

    ApplyForce(forceNet, dt);
}

void Mass::Solve(Vector2D hitbox){
    position = hitbox;
}

bool Mass::CheckCollision(Vector2D hitbox){
    int w = 8;
    if(position.x > hitbox.x - w && position.x < hitbox.x + w && position.y > hitbox.y - w && position.y < hitbox.y + w){
        grabbed = true;
        return true;
    }
    else{
        return false;
    }
}

void Mass::ApplyForce(Vector2D &force, float dt){
    //a = F/m
    acceleration = force * 1 / m; //Acceleration due to current
    velocity = velocity + (acceleration * (dt));
}

void Mass::Update(float dt){
    if(!anchored)
        position = position + velocity * dt;
}

void Mass::Update(Vector2D mousepos, int m, float dt){

}


std::vector<std::pair<Vector2D, Vector2D>>* Mass::Draw(){
    std::vector<std::pair<Vector2D, Vector2D>>* v = new std::vector<std::pair<Vector2D, Vector2D>>();
    return v;
}

