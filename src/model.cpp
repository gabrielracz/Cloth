#include"../include/vector2D.hpp"
#include"../include/mass.hpp"
#include"../include/spring.hpp"
#include"../include/rope.hpp"
#include"../include/controller.hpp"
#include"../include/model.hpp"

#include<iostream>

Model::Model(Controller* initCtrl){
    ctrl = initCtrl;
    float dt = 0.02f;
    grabbing = false;
    cutting = false;
    grabbed = nullptr;
}

Model::~Model(){
    for(auto obj : objects){
        delete obj;
    }
}

std::vector<PhysicsObject*>* Model::GetObjects(){
    return &objects;
}

void Model::AddObject(PhysicsObject* obj){
    objects.push_back(obj);
}

void Model::ClearObjects(){
    for(auto obj : objects){
        delete obj;
    }
    objects.clear();
}

void Model::Step(float dt){
    if(cutting){
        for(auto obj : objects){
            obj->Update(ctrl->GetMousePos(), 1, dt);
        }   
    }else if(grabbing){
        for(auto obj : objects){
            obj->Update(ctrl->GetMousePos(), 2, dt);
        }   
    }
    else {
        for(auto obj : objects){
            obj->Update(dt);
        }   
    }
}

void Model::Step(Vector2D hitbox, int m, float dt){
    // if(cutting){
    //     for(auto obj : objects){
    //         obj->Update(hitbox, m, dt);
    //     }   
    // }else if(grabbing){

    // }
}

void Model::Draw(){
    for(auto obj : objects){
        obj->Draw();
    }  
}

void Model::RebuildObjects(){
    for(auto obj : objects){
        // obj->Rebuild();
    }  
}

