#include"../include/vector2D.hpp"
#include"../include/mass.hpp"
#include"../include/spring.hpp"
#include"../include/rope.hpp"

#include<iostream>
#include<math.h>

Rope::Rope(int masscount, int width, float totalmass, float x, float y, float k){
    this->k = k;
    this->springlength = width / masscount;
    this->startx = x;
    this->starty = y;

    // float pointmass = totalmass / (masscount * masscount);
    this->pointmass = totalmass / masscount;
    this->masscount = masscount;
    // buildString(x, y, masscount, springlength, pointmass);
    
}

Rope::~Rope(){
    for (auto m : masses){
        delete m;
    }
    for (auto s : springs){
        delete s;
    }
}

void Rope::Update(float dt){
    for(int i = 0; i < springs.size(); i++){
        Spring* s = springs.at(i);
        
        if(s->tear || s->CheckTear()) 
            continue;
        s->Update(dt);
    }
    if(grabbed != nullptr){
        grabbed = nullptr;
    }

    for(int i = 0; i < masses.size(); i++){
        masses[i]->Solve(dt);
        // masses[i]->Update(dt);
    }
        
}

//m == 1 ---- CUT
//m == 2 ---- GRAB
void Rope::Update(Vector2D hitbox, int m,  float dt){
    // std::cout << mousepos.x << " " << mousepos.y << std::endl;
    for(int i = 0; i < springs.size(); i++){
        Spring* s = springs.at(i);
        if(s->tear || s->CheckTear() || (m == 1 && s->CheckCollision(hitbox))) 
            continue;
        s->Update(dt);
    }
    //Check if we are initiating a grab
    for(int i = 0; i < masses.size(); i++){
        if(m == 2 && grabbed == nullptr && masses[i]->anchored && masses[i]->CheckCollision(hitbox)){
            grabbed = masses[i];
            continue;
        }
        masses[i]->Solve(dt);
    }
    if(grabbed != nullptr){
        grabbed->position = hitbox;
    } 
}

std::vector<std::pair<Vector2D, Vector2D>>* Rope::Draw(){
    std::vector<std::pair<Vector2D, Vector2D>>* verts = new std::vector<std::pair<Vector2D, Vector2D>>();
    for(auto spr : springs){
        if(spr->tear) continue;
        std::pair<Vector2D, Vector2D> l (Vector2D(spr->mass1->position.x, spr->mass1->position.y), Vector2D(spr->mass2->position.x, spr->mass2->position.y));
        verts->push_back(l);
    }
    return verts;
}
void Rope::getGridPos(int index, int width, int* x, int* y){
    *x = index % width;
    *y = floor(index / width);
}

void Rope::Build(){
    Mass* anchor = new Mass(startx, starty, pointmass);
    masses.push_back(anchor);
    anchors.push_back(anchor);
    anchor->anchored = true;

    for (int i = 1; i < masscount; i++)
    {
        Mass *m = new Mass(springlength * i + startx, starty, pointmass);
        masses.push_back(m);
        Spring *s = new Spring(masses[i - 1], m, k, springlength);
        springs.push_back(s);
    }
}

void Rope::addMass(float x, float y, float mass){
    Mass *m = new Mass(x, y, mass);
    masses.push_back(m);
    
}

void Rope::addSpring(int i1, int i2, float kc){
    Spring *s = new Spring(masses[i1], masses[i2], kc, springlength);
    springs.push_back(s);
}

void Rope::rebuild(){
    masses.clear();
    springs.clear();
    anchors.clear();
    Build();
}


