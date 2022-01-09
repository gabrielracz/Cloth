#include"../include/vector2D.hpp"
#include"../include/mass.hpp"
#include"../include/spring.hpp"
#include"../include/ropesim.hpp"
#include"../include/controller.hpp"
#include"../include/model.hpp"

Model::Model(Controller* initCtrl){
    ctrl = initCtrl;
    float dt = 0.02f;
    grabbing = false;
    cutting = false;

    //             num, length, weight, x, y, dt, k
    // rope = new RopeSim(90, width*.8, 20, width*.2, 10, dt, 45);  
    // RopeSim rope(100, 600, 10, 480, 100, dt, 130);
    //rope->masses.back()->m = 1.5;

}

Model::~Model(){
    for(auto obj : objects)
        delete obj;
}

std::vector<RopeSim*>* Model::GetObjects(){
    return &objects;
}

void Model::AddObject(RopeSim* obj){
    objects.push_back(obj);
}

void Model::Step(float dt){
    for(auto obj : objects){
        obj->Update(dt);
    }   
}

void Model::Step(Vector2D hitbox, int m, float dt){
    for(auto obj : objects){
        obj->Update(hitbox, m, dt);
    }   
}

void Model::Draw(){
    for(auto obj : objects){
        obj->Draw();
    }  
}

// void Model::Step(){
//     while (window->isOpen()){
//         handle_events();

//         if(cutting)
//         rope->update(true, Vector2D(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y));
//         else
//         rope->update();
            
//         window->clear(sf::Color(0, 0, 0, 255));
//         rope->render(window);
//         window->display();
//     }
// }


