#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <vector>
#include "Game.h"


Game::Game(){

	blueshipfile = "blueship.png";
	orangeshipfile = "orangeship.png";
	jellyfishfile = "jellyfish.png";
	spacebgfile = "spacebg.png";

	bluebulletfile = "bluebullet.png";
	orangebulletfile = "orangebullet.png";

	fireballfile = "fireball.png";
	explosion = new AnimatedRect(fireballfile, 6, 6, 64, false, false, -0.25, 0.8, 0.5, 0.5);

	blueship = new TexRect(blueshipfile,-1.5, 0.2, 0.5, 0.25);
	orangeship = new TexRect (orangeshipfile, 1.2, 0.25, 0.2, 0.3);
	jellyfish = new TexRect (jellyfishfile, 0, 0, 0.4, 0.4);

	background = new TexRect(spacebgfile, -4, 1, 4, 2);
    secondbg = new TexRect(spacebgfile, 0, 1, 4, 2);
    thirdbg = new TexRect(spacebgfile, 4, 1, 4, 2);

    blueshipV = true;
	orangeshipV = true;
	jellyfishV = true;

	inc = 0.0025;
    hit = false;
    forward = true;

	oprojup = true;

	bprojup = false;
	bprojdown = false;
	bprojleft = false;
	bprojright = false;
	
    setRate(1);
    start();
}



void Game::action(){

	float x1 = background->getX();
	float x2 = secondbg->getX();
	float x3 = thirdbg->getX();

	if (forward){
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
	if (!forward){
		amount = -inc;
	}
	else{
		amount = inc;
	}
	
	background->setX(x1-amount);
	secondbg->setX(x2-amount);
	thirdbg->setX(x3-amount);

    float mx = 0.5;
    float my = 0;

	float ox = orangeship-> getX();
	float oy = orangeship-> getY();

	float bx = blueship -> getX();
	float by = blueship -> getY();

	float jx = jellyfish-> getX();
	float jy = jellyfish-> getY();

	if(jellyfishV){
		jy += 0.0005;
		jellyfish->setY(jy);
	}

	if(jellyfish->getY()> 1.3){
		jellyfish ->setY(-1);
	}

	if(oprojup){
		oy += 0.0005;
		orangeship->setY(oy);
	}else{
		oy -= 0.0005;
		orangeship->setY(oy);
	}

	if(oy > 0.75){
		oprojup = false;
	}

	if(oy <-0.55){
		oprojup = true;
	}

	if(bprojup){
		by += 0.0005;
		blueship->setY(by);	
	} 

	if(bprojdown){
		by -= 0.0005;
		blueship->setY(by);
	}

	if(bprojleft){
		bx -= 0.0005;
		blueship-> setX(bx);
	}

	if(bprojright){
		bx += 0.0005;
		blueship -> setX(bx);
	}

	

	for (int i = 0; i < bluebullets.size(); i++){
		float xpos = bluebullets[i]->getX();
        xpos +=0.005;
        bluebullets[i]->setX(xpos);
	}
    
	if(orangeshipV){
		for (int i = 0; i < bluebullets.size(); i++) {
			if (orangeship->contains(bluebullets[i]->getX(), bluebullets[i]->getY())){ 
				hit = true;
				orangeshipV = false;
				explosion->setX(orangeship->getX());
				explosion->setY(orangeship->getY());
				explosion->playOnce();
			}
		}
	}

	if(jellyfishV){
		for (int i = 0; i < bluebullets.size(); i++) {
			if (jellyfish->contains(bluebullets[i]->getX(), bluebullets[i]->getY())){  
				hit = true;
				jellyfishV= false;
				explosion->setX(jellyfish->getX());
				explosion->setY(jellyfish->getY());
				explosion->playOnce();
			}
		}
	}
	

	for (int i = 0; i < orangebullets.size(); i++){
		float xpos = orangebullets[i]->getX();
        xpos -=0.005;
        orangebullets[i]->setX(xpos);
	}

	for (int i = 0; i < bluebullets.size(); i++) {
		if (bluebullets[i]->getX() > 1 && bluebullets[i]->getX() < 1.5) { 
			if (oprojup) {
				orangeship->setY(bluebullets[i]->getY() + 0.6);
			}
			else {
				orangeship->setY(bluebullets[i]->getY() - 0.3);
			}
			
		}
	}
    
    if (hit){
        explosion->setX(explosion->getX()-0.0001);
    }

	
	
	glutPostRedisplay();
}

void Game::draw() const{ 
    background->draw(0);
    secondbg->draw(0);
    thirdbg->draw(0);


    if (blueshipV){
        blueship->draw(0.4);
    }
    if (orangeshipV){
        orangeship->draw(0.4);
    }

	if(jellyfishV){
		jellyfish->draw(0.2);
	}

	for (int i = 0; i < bluebullets.size(); i++){
		bluebullets[i]->draw(0.3);
	}

	for (int i = 0; i < orangebullets.size(); i++){
		orangebullets[i]->draw(0.3);
	}
	

    explosion->draw(0.5);
};

void Game::handleKeyUp(unsigned char key, float x, float y){
	if (key == 'a'){
		bprojleft = false;
	}
	if (key == 's'){
		bprojdown = false;
	}
	if (key == 'd'){
		bprojright = false;
	}
	if (key == 'w'){
		bprojup = false;
	}
}


void Game::handleKeyDown(unsigned char key, float x, float y){
    if (key == ' '){
		bluebullets.push_back(new TexRect(bluebulletfile, blueship->getX() + blueship->getW(), blueship->getY() - blueship->getH()/2 + 0.025, 0.1, 0.05));
    }
	else if (key=='t'){
		orangebullets.push_back(new TexRect(orangebulletfile, orangeship->getX() + orangeship->getW()/2, orangeship->getY() - orangeship->getH()/2 + 0.025, 0.1, 0.1));
	}
    else if (key == 'p'){
        stop();
    }
    else if (key == 'r'){
        start();
    }
	if (key == 'w'){
		bprojdown = false;
		bprojup = true;
	}
	if (key == 'a'){
		bprojright = false;
		bprojleft = true;

	}
	if (key == 's'){
		bprojup = false;
		bprojdown = true;
	}
	if (key == 'd'){
		bprojleft = false;
		bprojright = true;
	}


}

Game::~Game(){
    stop();

	delete background;
	delete secondbg;
	delete thirdbg;

	delete blueship; 
	delete orangeship;
	delete jellyfish;
}
