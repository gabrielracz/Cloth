#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>
#include <math.h>
#include"../include/ropesim.hpp"

class Model {
    public:
    sf::RenderWindow* window;
    // vector<PhysicsObject*> objects;
    RopeSim* rope;
    bool grabbing;
    bool cutting;
    Mass* targetgrabbed;

    Model(){
        window = new sf::RenderWindow(sf::VideoMode(1000, 1000), "Rope");
        window->clear(sf::Color(0, 0, 0, 255));
        window->display();
        window->setKeyRepeatEnabled(false);
        window->setFramerateLimit(300);
        window->setKeyRepeatEnabled(false);

        float dt = 0.02f;

        //             num, length, weight, x, y, dt, k
        rope = new RopeSim(90, 800, 20, 180, 10, dt, 45);  
        // RopeSim rope(100, 600, 10, 480, 100, dt, 130);
        //rope->masses.back()->m = 1.5;

        bool grabbing = false;
        bool cutting = false;
        Mass* targetgrabbed = NULL;
    }

    void loop(){
        while (window->isOpen()){
            handle_events();

            if(cutting)
            rope->update(true, Vector2D(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y));
            else
            rope->update();
                
            window->clear(sf::Color(0, 0, 0, 255));
            rope->render(window);
            window->display();
        }
    }

    void handle_events(){
        sf::Event e;
        while (window->pollEvent(e))
        {
            if (e.type == e.Closed){
                window->close();
            }
            //KEYBOARD
            if(e.type == sf::Event::KeyPressed){
                if((e.key.code == sf::Keyboard::C) && !cutting){
                    cutting = true; 
                }
            }else if(e.type == sf::Event::KeyReleased){
            if(e.key.code == sf::Keyboard::C){
                    cutting = false;             
                } 
            }

            //MOUSE
            if(e.type == sf::Event::MouseButtonPressed){
                if(e.mouseButton.button == sf::Mouse::Left && !cutting){
                    cutting = true;
                }
            }else if(e.type == sf::Event::MouseButtonReleased){
                if(e.mouseButton.button == sf::Mouse::Right){
                    grabbing = !grabbing;
                    float leastdistance = 1000000000000.0;
                    float distance;
                    Vector2D mousepos (sf::Mouse::getPosition(*(window)).x, sf::Mouse::getPosition(*(window)).y);
                    for(auto &m : rope->anchors){
                        distance = (m->position - mousepos).getLength();
                        if(distance < leastdistance){
                            leastdistance = distance;
                            targetgrabbed = m;
                        }
                    }
                    if(targetgrabbed)
                        targetgrabbed->anchored = true;
                }else if(e.mouseButton.button == sf::Mouse::Left){
                    cutting = false;
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                targetgrabbed->anchored = false;
                grabbing = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
                targetgrabbed->anchored = true;
                grabbing = true;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                while(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    usleep(0.0015 * 1000000);
                }
            }
            if (grabbing)
            {
                targetgrabbed->position.x = sf::Mouse::getPosition(*(window)).x;
                targetgrabbed->position.y = sf::Mouse::getPosition(*(window)).y;
            }
        }
    }

    void free(){
        delete window;
        rope->free();
    }
};
int main(int argc, char *argv[]){
    Model Simulation = Model();
    Simulation.loop();
    Simulation.free();
    return 0;
}

