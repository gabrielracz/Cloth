#include"../include/vector2D.hpp"
#include"../include/physicsobject.hpp"
#include"../include/ropesim.hpp"
#include"../include/model.hpp"
#include"../include/view.hpp"
#include"../include/controller.hpp"

#include<iostream>

Controller::Controller(){
    model = new Model(this);
    view = new View(1000, 1000, this);
    running = true;
    dt = 0.0185f;
    RopeSim* rope = new RopeSim(90, 1000*.8, 20, 1000*.2, 10, 45);
    model->AddObject(rope);
    cutting = false;
    grabbing = false;
}

void Controller::Update(){
    if(cutting){
        model->Step(GetMousePos(), 1, dt);    //Solve
    }else if(grabbing) {
        model->Step(GetMousePos(), 2, dt);
    }else {
        model->Step(dt);
    }
    view->Update();     //Get inputs and render
}

Vector2D Controller::GetMousePos(){
    return view->GetMousePos();
}

std::vector<RopeSim*>* Controller::GetObjects() {
    return model->GetObjects();
}

void Controller::HandleClosed(){
    delete model;
    delete view;
    running = false;
}

void Controller::HandleCutting(bool t){
    cutting = t;
}

void Controller::HandleGrabbing(bool t){
    grabbing = t;
}

void Controller::HandleReload(){
    //Rebuild all objects?
    return;
}



