#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <vector>

#include "collider.h"
#include "Game.h"


Game::Game(){

	blueshipfile = "blueship.png";
	orangeshipfile = "orangeship.png";
	// jellyfishfile = "jellyfish.png";
	spacebgfile = "spacebg.png";


	blueship = new TexRect(blueshipfile,-1.5, 0.2, 0.5, 0.25);
	orangeship = new TexRect (orangeshipfile, 1.2, 0.2, 0.25, 0.45);
	// jellyfish = new TexRect (jellyfishfile, 0, 1, 0, 0);

	background = new TexRect(spacebgfile, -4, 1, 4, 2);
    secondbg = new TexRect(spacebgfile, 0, 1, 4, 2);
    thirdbg = new TexRect(spacebgfile, 4, 1, 4, 2);

    blueshipV = true;
	orangeshipV = true;
	jellyfishV = true;
	
	firebullet = false;
	inc = 0.0025;
    hit = false;
    forward = true;

	vector<collider> loadout;
	for (size_t i = 0; i < count; i++)
	{
		/* !colider = false; */
	}
	
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

    //float mx = 0.5;
    //float my = 0;
    

    // if (!hit && firebullet){
    //     float ypos = bluebullet->getY();
    //     ypos +=0.005;
    //     bluebullet->setY(ypos);

    //     if (orangeship->contains(0, ypos-0.005)){
    //         firebullet = false;
    //         hit = true;
    //         orangeshipV = false;
    //         bluebulletV= false;
    //         explosion->setX(orangeship->getX());
    //         explosion->setY(orangeship->getY());
    //         explosion->playOnce();
    //     }
    // }
    
    // if (hit){
    //     explosion->setY(explosion->getY()-0.0001);
    // }
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

	// if(jellyfishV){
	// 	jellyfish->draw(0.3);
	// }
	// if(bluebulletV){
	// 	bluebullet->draw(0.2);
	// }
	// if(orangebulletV){
	// 	orangebullet->draw(0.2);
	// }

    //explosion->draw(0.1);
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
	if (key == 'e'){
		inc += 0.005;
	}
	if (key == 'q'){
		inc -= 0.005;
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

	// delete bluebullet;
	// delete orangebullet;
}
