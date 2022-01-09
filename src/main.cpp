#include"../include/controller.hpp"
#include<iostream>


int main(int argc, char *argv[]){
    Controller app = Controller();
    app.Update();
    
    while(app.running){
        app.Update();
    }
}

