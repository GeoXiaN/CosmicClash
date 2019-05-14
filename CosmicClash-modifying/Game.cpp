#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <vector>

//#include "collider.h"
#include "Game.h"


Game::Game(){

	blueshipfile = "blueship.png";
	orangeshipfile = "orangeship.png";
	// jellyfishfile = "jellyfish.png";
	spacebgfile = "spacebg.png";

	bluebulletfile = "bluebullet.png";
	orangebulletfile = "orangebullet.png";

	fireballfile= "fireball.png";
	explosion = new AnimatedRect(fireballfile, 6, 6, 64, false, false, -0.25, 0.8, 0.5, 0.5);



	blueship = new TexRect(blueshipfile,-1.5, 0.2, 0.5, 0.25);
	orangeship = new TexRect (orangeshipfile, 1.2, 0.25, 0.2, 0.3);
	// jellyfish = new TexRect (jellyfishfile, 0, 1, 0, 0);

	bluebullet = new TexRect(bluebulletfile, -1, 0.1,0.1,0.05);

	background = new TexRect(spacebgfile, -4, 1, 4, 2);
    secondbg = new TexRect(spacebgfile, 0, 1, 4, 2);
    thirdbg = new TexRect(spacebgfile, 4, 1, 4, 2);

    blueshipV = true;
	orangeshipV = true;
	jellyfishV = true;

	bluebulletV = false;
	
	firebullet = false;
	inc = 0.0025;
    hit = false;
    forward = true;

	oprojup = true;


	bprojup = false;
	bprojdown = false;
	bprojleft = false;
	bprojright = false;

	// vector<collider> loadout;
	// for (size_t i = 0; i < count; i++)
	// {
	// 	/* !colider = false; */
	// }
	
    setRate(1);
    start();
	//st = this;
	//timer(1);
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
	//st->redraw();
	glutPostRedisplay();

    float mx = 0.5;
    float my = 0;

	float ox =orangeship-> getX();
	float oy =orangeship-> getY();

	float bx =blueship -> getX();
	float by =blueship -> getY();

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
    

	for (int i = 0; i < bluebullets.size(); i++) {
		if (orangeship->contains(bluebullets[i]->getX(), bluebullets[i]->getY())){  
			firebullet = false;
			hit = true;
			orangeshipV = false;
			bluebulletV= false;
			explosion->setX(orangeship->getX());
			explosion->setY(orangeship->getY());
			explosion->playOnce();
		}
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

	

    if (!hit && firebullet){
        float xpos = bluebullet->getX();
        xpos +=0.005;
        bluebullet->setX(xpos);
		float ypos = blueship->getY() - blueship->getH()/2;
		bluebullet->setY(ypos);

        if (orangeship->contains(bluebullet->getX(), bluebullet->getY())){  
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
        explosion->setX(explosion->getX()-0.0001);
    }
}

void Game::draw() const{ 
    background->draw(0);
    secondbg->draw(0);
    thirdbg->draw(0);


    if (blueshipV){
        blueship->draw(0.2);
    }
    if (orangeshipV){
        orangeship->draw(0.2);
    }

	// if(jellyfishV){
	// 	jellyfish->draw(0.3);
	// }
	if(bluebulletV){
		bluebullet->draw(0.3);
	}

	for (int i = 0; i < bluebullets.size(); i++){
		bluebullets[i]->draw(0.3);
	}
	// if(orangebulletV){
	// 	orangebullet->draw(0.2);
	// }

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
		//bluebulletV = true;
        //firebullet = true;
		bluebullets.push_back(new TexRect(bluebulletfile, blueship->getX() + blueship->getW(), blueship->getY() - blueship->getH()/2 + 0.025, 0.1, 0.05));
    }
    else if (key == 'p'){
        stop();
    }
    else if (key == 'r'){
        start();
    }
	if (key == 'w'){
		bprojleft=false;
		bprojright=false;
		bprojdown = false;

		bprojup = true;
	}
	if (key == 'a'){
		bprojup = false;
		bprojdown = false;
		bprojright = false;

		bprojleft = true;

	}
	if (key == 's'){
		bprojup = false;
		bprojleft = false;
		bprojright = false;

		bprojdown = true;
	}
	if (key == 'd'){
		bprojup = false;
		bprojleft = false;
		bprojdown = false;

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
	// delete jellyfish;

	delete bluebullet;
	// delete orangebullet;
}
