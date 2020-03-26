#ifndef __keyboard_h__
#define __keyboard_h__

#include <cstdio>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>

class KbdWindow : public Fl_Window 
{
    public:
        KbdWindow(int w, int h, const char *t = NULL ) 
        : Fl_Window( w, h, t ) 
        { 
            // do nothing.
        }

    protected:
        int handle(int);
};

#endif /// of __keyboard_h__
