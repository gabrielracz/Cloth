#include"../include/ropesim.hpp"
#include<iostream>

RopeSim::RopeSim(int masscount, int width, float totalmass, float x, float y, float dt, float k){
    this->dt = dt;
    this->k = k;
    this->springlength = width / masscount;
    
    // float pointMass = totalmass / (masscount * masscount);
    float pointMass = totalmass / masscount;

    buildCloth(x, y, masscount, pointMass);

    // buildString(x, y, masscount, springlength, pointMass);
    
}

void RopeSim::getGridPos(int index, int width, int* x, int* y){
    *x = index % width;
    *y = floor(index / width);
}

//Should create cloth as a inheritance of rope
void RopeSim::buildCloth(float startx, float starty, int masscount, float pointMass){
    //Start at top left corner
    //masscount will be a square piece of cloth
    int totalMasses = masscount * masscount;
    int mx, my;

    Mass* anchor = new Mass(startx, starty, pointMass);
    masses.push_back(anchor);
    anchors.push_back(anchor);
    anchor->anchored = true;

    for(int i = 1; i < totalMasses; i++){
        getGridPos(i, masscount, &mx, &my);
        Mass *m = new Mass( springlength * mx + startx, my * springlength + starty, pointMass);
        masses.push_back(m);
        if((my == 0) && mx % ((masscount-1)/5) == 0){
            m->anchored = true;
            anchors.push_back(m);
        }
        m->position.x /= 1.1;
    }

    int maxy = my;
    float kscale;

    for(int i = 0; i < totalMasses; i++){
        getGridPos(i, masscount, &mx, &my);
        kscale = k  + k * (my/maxy);
        if(mx > 0){
            addSpring(i, i - 1, k);
            // if(my < masscount - 1)
            //     addSpring(i, i + masscount - 1, k);
        }
        if(mx < masscount - 1){
            addSpring(i, i + 1, k);
            // if(my < masscount - 1)
            //     addSpring(i, i + masscount + 1, k);
        }
        if(my > 0){
            addSpring(i, i - masscount, k);
        }
        if(my < masscount - 1){
            addSpring(i, i + masscount, k);
        }
    }
}

void RopeSim::buildString(float x, float y, int masscount, float springlength, float pointMass){
    Mass* anchor = new Mass(x, y, pointMass);
    masses.push_back(anchor);
    anchors.push_back(anchor);
    anchor->anchored = true;

    for (int i = 1; i < masscount; i++)
    {
        Mass *m = new Mass(springlength * i + x, y, pointMass);
        masses.push_back(m);
        Spring *s = new Spring(masses[i - 1], m, k, springlength);
        springs.push_back(s);
    }
}

void RopeSim::update(){
    for(int i = 0; i < springs.size(); i++){
        Spring* s = springs.at(i);
        if(s->tear) continue;
            s->solve(dt);
    }for(int i = 0; i < masses.size(); i++){
        masses[i]->solve(dt);
    }
        
}

void RopeSim::update(bool cutting, Vector2D mousepos){
    // std::cout << mousepos.x << " " << mousepos.y << std::endl;
    for(int i = 0; i < springs.size(); i++){
        Spring* s = springs.at(i);
        if(s->tear || s->check_tear() || s->check_collision(mousepos)) continue;
        s->solve(dt);
    }for(int i = 0; i < masses.size(); i++){
        masses[i]->solve(dt);
    }
        
}

void RopeSim::render(sf::RenderWindow *window){
for(int i = 0; i < springs.size(); i++){
        Spring* s = springs.at(i);
        if(s->tear || s->check_tear()) continue;
        s->draw(window);
    }
}

void RopeSim::addMass(float x, float y, float mass){
    Mass *m = new Mass(x, y, mass);
    masses.push_back(m);
    
}

void RopeSim::addSpring(int i1, int i2, float kc){
    Spring *s = new Spring(masses[i1], masses[i2], kc, springlength);
    springs.push_back(s);
}

void RopeSim::free(){
    for (auto &m : masses)
    {
        delete m;
    }
    for (auto &s : springs)
    {
        delete s;
    }
}
