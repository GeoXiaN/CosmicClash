#ifndef App_h
#define App_h

#include "GlutApp.h"
#include "AnimatedRect.h"


class App: public GlutApp {
    
    TexRect* ship;
    TexRect* background;
    TexRect* secondbg;
    TexRect* thirdbg;
    float inc;
    bool forward;
public:
    
    App(int argc, char** argv, int width, int height, const char* title);
    
    void draw();
    
    void keyDown(unsigned char key, float x, float y);
    void rightMouseDown(float, float);
    
    void keyUp(unsigned char, float, float);
    
    void specialKeyUp(int, float, float);
    
    void drag(float, float);
    
    void idle();
    
    ~App();
    
    friend void timer(int);
    
};

#endif
