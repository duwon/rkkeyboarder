#ifndef __keyboard_ui_h__
#define __keyboard_ui_h__

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Dial.H>

#include "keyboard.h"

extern KbdWindow* my_window;
extern void key_cb(Fl_Button*, void*);
extern void shift_cb(Fl_Button*, void*);
extern void wheel_cb(Fl_Dial*, void*);
extern Fl_Dial* roller_x;
extern Fl_Dial* roller_y;

KbdWindow* make_window();

#endif /// of __keyboard_ui_h__
