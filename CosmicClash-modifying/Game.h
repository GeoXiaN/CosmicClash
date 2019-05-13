#ifndef Game_hpp
#define Game_hpp

#include "AppComponent.h"
#include "AnimatedRect.h"
#include "Timer.h"

class Game: public AppComponent, private Timer{
	
	const char* blueshipfile;
	const char* orangeshipfile;
	const char* jellyfishfile;
	const char* spacebgfile;
	const char* bluebulletfile;
	const char* orangebulletfile;

    TexRect* blueship; //mushroom
	TexRect* orangeship;
	TexRect* jellyfish;

	TexRect* bluebullet;
	TexRect* orangebullet;
    
	TexRect* background;
    TexRect* secondbg;
    TexRect* thirdbg;

    bool blueshipV;
    bool orangeshipV;
	bool jellyfishV;
	bool bluebulletV;
	bool orangebulletV;
    bool firebullet;
	bool hit;
	bool forward;

	float inc;

	
public:
    AnimatedRect* explosion;
    Game();
    
    void draw() const; // removed const
    void handleKeyDown(unsigned char, float, float);
    void action();
	
	//friend void timer(int);

    ~Game();


};

#endif 
