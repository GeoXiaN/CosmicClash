#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "Game.h"
#include "App.h"
#include "GlutApp.h"

Game* singleton;

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

Game::Game(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){
	
	blueshipfile = "blueship.png";
	orangeshipfile = "orangeship.png";
	jellyfishfile = "jellyfish.png";
	spacebgfile = "spacebg.png";


	blueship = new TexRect(blueshipfile,-1.5, 0.5, 1, 1);
	orangeship = new TexRect (orangeshipfile, 0, 0, 0, 0);
	jellyfish = new TexRect (jellyfishfile, 0, 1, 0, 0);

	background = new TexRect(spacebgfile, -4, 1, 4, 2);
    secondbg = new TexRect(spacebgfile, 0, 1, 4, 2);
    thirdbg = new TexRect(spacebgfile, 4, 1, 4, 2);
 
    blueshipV = true;
	orangeshipV = true;
	jellyfishV = true;
	
	firebullet = false;
    hit = false;
    forward = false;

    setRate(1);
    start();
}

void Game::action(){
    float mx = 0.5;
    float my = 0;
    

    if (!hit && firebullet){
        float ypos = bluebullet->getY();
        ypos +=0.005;
        bluebullet->setY(ypos);

        if (orangeship->contains(0, ypos-0.005)){
            firebullet = false;
            hit = true;
            orangeshipV = false;
            bluebulletV= false;
            explosion->setX(orangeship->getX());
            explosion->setY(orangeship->getY());
            explosion->playOnce();
        }
    }
    
    if (hit){
        explosion->setY(explosion->getY()-0.0001);
    }
}

void Game::draw() const{ // removed const temporarily
    background->draw(0);
    secondbg->draw(0);
    thirdbg->draw(0);


    if (blueshipV){
        blueship->draw(0.2);
    }
    if (orangeshipV){
        orangeship->draw(0.2);
    }

	if(jellyfishV){
		jellyfish->draw(0.3);
	}
	if(bluebulletV){
		bluebullet->draw(0.2);
	}
	if(orangebulletV){
		orangebullet->draw(0.2);
	}

    explosion->draw(0.1);
};

void Game::handleKeyDown(unsigned char key, float x, float y){
    if (key == ' '){
        firebullet = true;
    }
    else if (key == 'p'){
        stop();
    }
    else if (key == 'r'){
        start();
    }
}

Game::~Game(){
    stop();

	delete blueship; //mushroom
	delete orangeship;
	delete jellyfish;

	delete bluebullet;
	delete orangebullet;
}
