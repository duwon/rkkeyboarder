#include <windows.h>
#include <unistd.h>
#include <cstring>
#include <resource.h>

#include <FL/Fl_draw.H>

#include "keyboard_ui.h"

using namespace std;

// these are used to identify which buttons are which:
void key_cb(Fl_Button*, void*)
{
    
}

void shift_cb(Fl_Button*, void*) 
{
    
}

void wheel_cb(Fl_Dial*, void*) 
{
    
}

// this is used to stop Esc from exiting the program:
int handle(int e) 
{
    return (e == FL_SHORTCUT); // eat all keystrokes
}

int KbdWindow::handle( int msg ) 
{
    if ( msg==FL_MOUSEWHEEL )
    {
        roller_x->value( roller_x->value() + Fl::e_dx * roller_x->step() );
        roller_y->value( roller_y->value() + Fl::e_dy * roller_y->step() );
        
        return 1;
    }
    return 0;
}

struct keycode_table{int n; const char* text;} table[] = 
{
    {FL_Escape, "FL_Escape"},
    {FL_BackSpace, "FL_BackSpace"},
    {FL_Tab, "FL_Tab"},
    {FL_Iso_Key, "FL_Iso_Key"},
    {FL_Enter, "FL_Enter"},
    {FL_Print, "FL_Print"},
    {FL_Scroll_Lock, "FL_Scroll_Lock"},
    {FL_Pause, "FL_Pause"},
    {FL_Insert, "FL_Insert"},
    {FL_Home, "FL_Home"},
    {FL_Page_Up, "FL_Page_Up"},
    {FL_Delete, "FL_Delete"},
    {FL_End, "FL_End"},
    {FL_Page_Down, "FL_Page_Down"},
    {FL_Left, "FL_Left"},
    {FL_Up, "FL_Up"},
    {FL_Right, "FL_Right"},
    {FL_Down, "FL_Down"},
    {FL_Shift_L, "FL_Shift_L"},
    {FL_Shift_R, "FL_Shift_R"},
    {FL_Control_L, "FL_Control_L"},
    {FL_Control_R, "FL_Control_R"},
    {FL_Caps_Lock, "FL_Caps_Lock"},
    {FL_Alt_L, "FL_Alt_L"},
    {FL_Alt_R, "FL_Alt_R"},
    {FL_Meta_L, "FL_Meta_L"},
    {FL_Meta_R, "FL_Meta_R"},
    {FL_Menu, "FL_Menu"},
    {FL_Help, "FL_Help"},
    {FL_Num_Lock, "FL_Num_Lock"},
    {FL_KP_Enter, "FL_KP_Enter"}
};

int main( int argc, char** argv )
{
    Fl::add_handler(handle);
    Fl::scheme( "flat" );
    Fl_Window::default_xclass( "rkkbdrr" );
    
    KbdWindow* window = make_window();
    if ( window != NULL )
    {
        window->show();
        
        HICON \
        hIconWindowLarge = (HICON)LoadImage( fl_display,
                                             MAKEINTRESOURCE( IDC_ICON_A ),
                                             IMAGE_ICON,
                                             128,
                                             128,
                                             LR_SHARED );

        HICON \
        hIconWindowSmall = (HICON)LoadImage( fl_display,
                                             MAKEINTRESOURCE( IDC_ICON_A ),
                                             IMAGE_ICON,
                                             16,
                                             16,
                                             LR_SHARED );

        SendMessage( fl_xid( window ),
                     WM_SETICON,
                     ICON_BIG,
                     (LPARAM)hIconWindowLarge );

        SendMessage( fl_xid( window ),
                     WM_SETICON,
                     ICON_SMALL,
                     (LPARAM)hIconWindowSmall );        
        
        while ( Fl::wait() ) 
        {
            const char *str = NULL;

            // update all the buttons with the current key and shift state:
            for (int i = 0; i < window->children(); i++) 
            {
                Fl_Widget* b = window->child(i);
                if (b->callback() == (Fl_Callback*)key_cb) 
                {
                    int i = b->argument();
                    if (!i) 
                        i = b->label()[0];
                    
                    Fl_Button *btn = ((Fl_Button*)b);
                    
                    int state = Fl::event_key(i);
                    if (btn->value()!=state)
                        btn->value(state);
                } 
                else 
                if ( b->callback() == (Fl_Callback*)shift_cb ) 
                {
                    int i = b->argument();
                    Fl_Button *btn = ((Fl_Button*)b);
                    
                    int state = Fl::event_state(i);
                    if (btn->value()!=state)
                        btn->value(state);
                }
            }
        }
    }
    
    return 0;
}