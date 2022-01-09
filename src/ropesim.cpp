#include"../include/vector2D.hpp"
#include"../include/mass.hpp"
#include"../include/spring.hpp"
#include"../include/ropesim.hpp"
#include<math.h>

RopeSim::RopeSim(int masscount, int width, float totalmass, float x, float y, float k){
    this->k = k;
    this->springlength = width / masscount;
    this->startx = x;
    this->starty = y;

    // float pointmass = totalmass / (masscount * masscount);
    this->pointmass = totalmass / masscount;
    this->masscount = masscount;

    buildCloth();

    // buildString(x, y, masscount, springlength, pointmass);
    
}

RopeSim::~RopeSim(){
    for (auto &m : masses){
        delete m;
    }
    for (auto &s : springs){
        delete s;
    }
}

void RopeSim::Update(float dt){
    for(int i = 0; i < springs.size(); i++){
        Spring* s = springs.at(i);
        if(s->tear) continue;
            s->Update(dt);
    }for(int i = 0; i < masses.size(); i++){
        masses[i]->grabbed = false;
        masses[i]->Solve(dt);
        // masses[i]->Update(dt);
    }
        
}

//m == 1 ---- CUT
//m == 2 ---- GRAB
void RopeSim::Update(Vector2D hitbox, int m,  float dt){
    // std::cout << mousepos.x << " " << mousepos.y << std::endl;
    for(int i = 0; i < springs.size(); i++){
        Spring* s = springs.at(i);
        if(s->tear || s->CheckTear() || (m == 1 && s->CheckCollision(hitbox))) 
            continue;
        s->Update(dt);
    }
    for(int i = 0; i < masses.size(); i++){
        masses[i]->Solve(dt);
    }
        
}

std::vector<std::pair<Vector2D, Vector2D>>* RopeSim::Draw(){
    std::vector<std::pair<Vector2D, Vector2D>>* verts = new std::vector<std::pair<Vector2D, Vector2D>>();
    for(auto spr : springs){
        std::pair<Vector2D, Vector2D> l (Vector2D(spr->mass1->position.x, spr->mass1->position.y), Vector2D(spr->mass2->position.x, spr->mass2->position.y));
        verts->push_back(l);
    }
    return verts;
}
void RopeSim::getGridPos(int index, int width, int* x, int* y){
    *x = index % width;
    *y = floor(index / width);
}

//Should create cloth as a inheritance of rope
void RopeSim::buildCloth(){
    //Start at top left corner
    //masscount will be a square piece of cloth
    int totalMasses = masscount * masscount;
    int mx, my;

    Mass* anchor = new Mass(startx, starty, pointmass);
    masses.push_back(anchor);
    anchors.push_back(anchor);
    anchor->anchored = true;

    for(int i = 1; i < totalMasses; i++){
        getGridPos(i, masscount, &mx, &my);
        Mass *m = new Mass( springlength * mx + startx, my * springlength + starty, pointmass);
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

void RopeSim::buildString(float x, float y, int masscount, float springlength, float pointmass){
    Mass* anchor = new Mass(x, y, pointmass);
    masses.push_back(anchor);
    anchors.push_back(anchor);
    anchor->anchored = true;

    for (int i = 1; i < masscount; i++)
    {
        Mass *m = new Mass(springlength * i + x, y, pointmass);
        masses.push_back(m);
        Spring *s = new Spring(masses[i - 1], m, k, springlength);
        springs.push_back(s);
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

void RopeSim::rebuild(){
    masses.clear();
    springs.clear();
    anchors.clear();
    buildCloth();
}


