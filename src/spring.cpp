#include"../include/vector2D.hpp"
#include"../include/mass.hpp"
#include"../include/spring.hpp"


Spring::Spring(Mass *mass1, Mass *mass2, float springConstant, float springlength){
    this->mass1 = mass1;
    this->mass2 = mass2;
    this->springConstant = springConstant;
    this->springlength = springlength;
    this->tear = false;
}

//Solves spring equation and appslies force
//To the two connected masses
void Spring::Update(float dt){
    // Fs = -k (x - l)
    // k = springConstant, x = positionDelta, l = springlength

    Vector2D deltaPos = mass1->position - mass2->position;
    float r = deltaPos.getLength();
    Vector2D springForce = (deltaPos / r) * (-(springlength - r)) * (-springConstant);
    Vector2D netForce = springForce + (-((mass1->velocity) - (mass2->velocity))) * 0.4;

    if (!mass1->anchored){
        mass1->ApplyForce(netForce, dt);
        mass1->Update(dt);
    }
    if (!mass2->anchored){
        Vector2D oppForce = -netForce;
        mass2->ApplyForce(oppForce, dt);
        mass2->Update(dt);
    }
}

void Spring::Update(Vector2D mousepos, int m, float dt){

}

std::vector<std::pair<Vector2D, Vector2D>>* Spring::Draw(){
    std::vector<std::pair<Vector2D, Vector2D>>* v = new std::vector<std::pair<Vector2D, Vector2D>>();
    v->push_back(std::pair (mass1->position, mass2->position));
    return v;
}



bool Spring::CheckTear(){
    if(!(mass1->anchored || mass2->anchored) && mass1->position.getDistance(mass2->position) > springlength * 5){    //change this to be some force requirement
        tear = true;
        return true;
    }else{
        return false;
    }   
}

bool Spring::CheckCollision(Vector2D comp){
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
