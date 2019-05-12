#include <iostream>
#include "App.h"


//Our animations
App* singleton;

void timer(int id){
    
    float x1 = singleton->background->getX();
    float x2 = singleton->secondbg->getX();;
    float x3 = singleton->thirdbg->getX();;
    
    if (singleton->forward){
        if (x1 <= -6){
            x1 = x3+4;
        }
        if (x2 <= -6){
            x2 = x1+4;
        }
        if (x3 <= -6){
            x3 = x2+4;
        }
    }
    else{
        if (x1 >= 2){
            x1 = x3-4;
        }
        if (x2 >= 2){
            x2 = x1-4;
        }
        if (x3 >= 2){
            x3 = x2-4;
        }
    }
    
    float amount;
    if (!singleton->forward){
        amount = -singleton->inc;
    }
    else{
        amount = singleton->inc;
    }
    
    singleton->background->setX(x1-amount);
    singleton->secondbg->setX(x2-amount);
    singleton->thirdbg->setX(x3-amount);
    singleton->redraw();
    glutTimerFunc(16, timer, id);
}


App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){
    
    
    ship = new TexRect("ship.png", -1.5, 0.5, 1, 1);//AXIS are Inverted!
    background = new TexRect("BG.png", -4, 1, 4, 2);
    secondbg = new TexRect("BG.png", 0, 1, 4, 2);
    thirdbg = new TexRect("BG.png", 4, 1, 4, 2);
    inc = 0.03;
    forward = true;
    singleton = this;
    timer(1);
}

void App::draw() {
    background->draw(0);
    secondbg->draw(0);
    thirdbg->draw(0);
    ship->draw(0.5);

}

void App::idle(){
    
}

void App::keyDown(unsigned char key, float x, float y){
    if (key == 27){
        exit(0);
    }
    
    if (key == 'd'){
        inc += 0.01;
    }
    if (key == 'a'){
        inc -= 0.01;
    }
    
    // if (key == 'x'){
    //     ship->flip();
    //     forward = !forward;
    // }
    
    // if (key == ' '){
    //     ship->playLoop();
    // }
}



void App::rightMouseDown(float x, float y){
    std::cout << "I right-clicked" << std::endl;
}

void App::keyUp(unsigned char key, float x, float y){

}

void App::drag(float x, float y){
    std::cout << x << ", "<< y << std::endl;
}

void App::specialKeyUp(int key, float x, float y){
    std::cout << key << std::endl;
}

App::~App(){
    std::cout << "Exiting..." << std::endl;
    delete ship;
    delete background;
    delete secondbg;
    delete thirdbg;
}
