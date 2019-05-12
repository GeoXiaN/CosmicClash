#include <iostream>
#include "App.h" //Ignor this error

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
    // This will get called every 16 milliseconds after
    // you call it once
    
    // If you want to manipulate the app in here
    // do it through the singleton pointer
    
    if (singleton->up){ //projectile stuff
        float ypos = singleton->projectile->getY();
        ypos +=0.05;
        singleton->projectile->setY(ypos);
        singleton->redraw();
    }
//GLboolean CheckCollision(GameObject &one, GameObject &two) // AABB - AABB collision
// {
//     // // Collision x-axis?
//     // bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
//     //     two.Position.x + two.Size.x >= one.Position.x;
//     // // Collision y-axis?
//     // bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
//     //     two.Position.y + two.Size.y >= one.Position.y;
//     // // Collision only if on both axes
//     // return collisionX && collisionY;
// }  
    
    glutTimerFunc(16, timer, id);
}


App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){
    
    mushroom = new TexRect("mushroom.png", -0.25, 0.9, 0.5, 0.5);
    projectile = new Rect(-0.05, -0.8, 0.1, 0.1);
    up = false;
    
    singleton = this;
    background = new TexRect("BG.png", -4, 1, 4, 2);
    secondbg = new TexRect("BG.png", 0, 1, 4, 2);
    thirdbg = new TexRect("BG.png", 4, 1, 4, 2);
    timer(1);
}

void App::draw() {
    background->draw(0);
    secondbg->draw(0);
    thirdbg->draw(0);
    mushroom->draw(0.1);
    projectile->draw();
}

void App::keyDown(unsigned char key, float x, float y){
    if (key == 27){
        exit(0);
    }
    if (key == ' '){
        up = true;
    }
}

App::~App(){
    delete mushroom;
    std::cout << "Exiting..." << std::endl;
}
