#ifndef Game_hpp
#define Game_hpp

#include "AppComponent.h"
#include "AnimatedRect.h"
#include "Timer.h"
#include <vector>

class Game: public AppComponent, private Timer{
	
	const char* blueshipfile;
	const char* orangeshipfile;
	const char* jellyfishfile;
	const char* spacebgfile;
	const char* bluebulletfile;
	const char* orangebulletfile;

	const char* fireballfile;

    TexRect* blueship; //mushroom
	TexRect* orangeship;
	TexRect* jellyfish;

	std::vector<TexRect*> bluebullets;
	std::vector<TexRect*> orangebullets;
    
	TexRect* background;
    TexRect* secondbg;
    TexRect* thirdbg;



	float ox;
	float oy;
	float bx;
	float by;

    bool blueshipV;
    bool orangeshipV;
	bool jellyfishV;
	bool bluebulletV;
	bool orangebulletV;
    bool firebullet;
	bool hit;
	bool forward;
	bool oprojup;
	bool bprojup;
	bool bprojdown;
	bool bprojleft;
	bool bprojright;

	float inc;

	
public:
    AnimatedRect* explosion;
    Game();
    
    void draw() const; // removed const
    void handleKeyDown(unsigned char, float, float);
	void handleKeyUp(unsigned char, float, float);
    void action();
	
	//friend void timer(int);

    ~Game();


};

#endif 
