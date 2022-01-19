#include"../include/vector2D.hpp"
#include"../include/physicsobject.hpp"
#include"../include/rope.hpp"
#include"../include/cloth.hpp"
#include"../include/model.hpp"
#include"../include/view.hpp"
#include"../include/controller.hpp"

#include<iostream>

Controller::Controller(){
    model = new Model(this);
    view = new View(1000, 1000, this);
    running = true;
    dt = 0.02f;
    Cloth* rope = new Cloth(90, (int)(1000*.8), 20.0f, 1000*.2f, 10.0f, 45.0f);
    // Rope* rope = new Rope(100, 600, 10.0f, 480.0f, 100.0f, 130.0f); //ROPE
    rope->Build();
    model->AddObject(rope);
    cutting = false;
    grabbing = false;
    rope_toggle = true;
}

void Controller::Update(){
//Step
    model->Step(dt);
    view->Update();     //Get inputs and render
}

Vector2D Controller::GetMousePos(){
    return view->GetMousePos();
}

std::vector<PhysicsObject*>* Controller::GetObjects() {
    return model->GetObjects();
}

void Controller::HandleClosed(){
    delete model;
    delete view;
    running = false;
}

void Controller::HandleCutting(bool t){
    model->cutting = t;
}

void Controller::HandleGrabbing(bool t){
    model->grabbing = t;
}

void Controller::HandleReload(){
    model->ClearObjects();
    if(rope_toggle){
        Rope* rpe = new Rope(100, 600, 10.0f, 480.0f, 100.0f, 130.0f); //ROPE
        rpe->Build();
        model->AddObject(rpe);

    }else{
        Cloth* clt = new Cloth(90, (int)(1000*.8), 20.0f, 1000*.2f, 10.0f, 45.0f);
        clt->Build();
        model->AddObject(clt);
    }
    rope_toggle = !rope_toggle;
    return;
}



