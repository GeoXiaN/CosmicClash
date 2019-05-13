#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "Game.h"

Game* st;

Game::Game(){
	
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
    forward = true;

    setRate(1);
    start();

	timer(1);
}

void timer(int id){
	float x1 = st->background->getX();
	float x2 = st->secondbg->getX();
	float x3 = st->thirdbg->getX();

	if (st->forward){
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
	if (!st->forward){
		amount = -st->inc;
	}
	else{
		amount = st->inc;
	}
	
	st->background->setX(x1-amount);
	st->secondbg->setX(x2-amount);
	st->thirdbg->setX(x3-amount);
	
	glutPostRedisplay();
	glutTimerFunc(16, timer, id);
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

	delete blueship; 
	delete orangeship;
	delete jellyfish;

	delete bluebullet;
	delete orangebullet;
}
