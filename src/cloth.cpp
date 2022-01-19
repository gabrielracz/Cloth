#include"../include/vector2D.hpp"
#include"../include/mass.hpp"
#include"../include/spring.hpp"
#include"../include/cloth.hpp"

#include<iostream>

Cloth::Cloth(int masscount, int width, float totalmass, float x, float y, float k)
    : Rope(masscount, width, totalmass, x, y, k){}

void Cloth::Build(){
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