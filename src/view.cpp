#include"SFML/Graphics.hpp"
#include"../include/vector2D.hpp"
#include"../include/physicsobject.hpp"
#include"../include/controller.hpp"
#include"../include/view.hpp"

#include<iostream>


View::View(int initWidth, int initHeight, Controller* initCtrl){
    ctrl = initCtrl;
    width = initWidth;
    height = initHeight;
    InitWindow();
    // std::cout << "view is good" << std::endl;
}

View::~View(){
    window->close();
    delete window;
}

void View::InitWindow(){
    window = new sf::RenderWindow(sf::VideoMode(width, height), "Rope");
    window->clear(sf::Color(0, 0, 0, 255));
    window->display();
    window->setKeyRepeatEnabled(false);
    window->setFramerateLimit(300);
    window->setKeyRepeatEnabled(false);
}

void View::Update(){
    Draw();
    PollEvents();

}

void View::Draw(){
    window->clear();
    std::vector<PhysicsObject*>* objs = ctrl->GetObjects(); 
    for(auto obj : *objs){
        sf::Color color (0xFFFFFFFF);
        std::vector<std::pair<Vector2D, Vector2D>>* verts = obj->Draw();
        for(auto v : *verts){
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(v.first.x, v.first.y), color),
                sf::Vertex(sf::Vector2f(v.second.x, v.second.y), color)
            };
            window->draw(line, 2, sf::Lines);
        }
        delete verts;
    }
    window->display();
}

void View::PollEvents(){
    sf::Event e;
    while (window->pollEvent(e)){
        if (e.type == e.Closed){
            ctrl->HandleClosed();
            return;
        }

        //KEYBOARD
        if(e.type == sf::Event::KeyPressed){
            //KEY DOWN
        }else if(e.type == sf::Event::KeyReleased){
            if(e.key.code == sf::Keyboard::R){
                ctrl->HandleReload();
            } 
        }

        //MOUSE
        if(e.type == sf::Event::MouseButtonPressed){
            if(e.mouseButton.button == sf::Mouse::Right){
                ctrl->HandleGrabbing(true);
            }else if(e.mouseButton.button == sf::Mouse::Left){
                ctrl->HandleCutting(true);
            }
        }else if(e.type == sf::Event::MouseButtonReleased){
            if(e.mouseButton.button == sf::Mouse::Right){
                ctrl->HandleGrabbing(false);
            }else if(e.mouseButton.button == sf::Mouse::Left){
                ctrl->HandleCutting(false);  //Turn Off
            }
        }
    }
}

Vector2D View::GetMousePos(){
    return Vector2D(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
}
