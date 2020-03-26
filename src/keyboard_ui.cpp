#include "keyboard_ui.h"
#include <fl_imgtk.h>

////////////////////////////////////////////////////////////////////////////////

#define KEYCOL_IMPACT       0xAA3333FF
#define KEYCOL_SPECIAL      0x333366FF
#define KEYCOL_ESTATE       0x336633FF
#define KEYCOL_WHEEL        0x444466FF
#define PUT_XYWH            putX, putY, putW, putH

#define ROW_Y_1             120
#define ROW_Y_2             (120 + 60)
#define ROW_Y_3             (120 + 100)
#define ROW_Y_4             (120 + 140)
#define ROW_Y_5             (120 + 180)
#define ROW_Y_6             (120 + 220)

#define LBLSZ_DEFAULT       14
#define LBLSZ_SMALL         10

////////////////////////////////////////////////////////////////////////////////

KbdWindow*  winKbdr = NULL;
Fl_Dial*    roller_x  = NULL;
Fl_Dial*    roller_y  = NULL;

////////////////////////////////////////////////////////////////////////////////

void btnConfig( Fl_Button* btn, int lblsz, Fl_Callback* cb = NULL, \
                void* prm = NULL, unsigned spcol = 0  )
{
    if ( btn != NULL )
    {
        if ( winKbdr != NULL )
        {
            if ( spcol == 0 )
            {
                btn->color( fl_lighter( winKbdr->color() ) );
            }
            btn->labelfont( winKbdr->labelfont() );
            btn->labelcolor( winKbdr->labelcolor() );
        }

        if ( spcol > 15 )
        {
            btn->color( spcol );
        }

        btn->box( FL_THIN_DOWN_BOX );        
        btn->selection_color( fl_lighter( btn->color() ) );
        btn->labelsize( lblsz );
        btn->align( FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_CLIP );
        btn->callback( cb, prm );
        
    }
}

KbdWindow* make_window() 
{
    winKbdr = new KbdWindow( 945, 395, "RaphK's KEYBOARDER !" );
    
    if ( winKbdr != NULL )
    {
        winKbdr->box(FL_FLAT_BOX);
        winKbdr->color( 0x202020FF );
        winKbdr->selection_color( 0xAACC99FF );
        winKbdr->labeltype( FL_NO_LABEL );
        winKbdr->labelfont( FL_HELVETICA );
        winKbdr->labelsize( LBLSZ_DEFAULT );
        winKbdr->labelcolor( 0xFFFFFFFF );
        winKbdr->align( Fl_Align(FL_ALIGN_TOP) );
        winKbdr->when( FL_WHEN_RELEASE );
        
        Fl_Box* boxBG = new Fl_Box( 0, 0, winKbdr->w(), winKbdr->h() );
        if ( boxBG != NULL )
        {
            boxBG->box( FL_FLAT_BOX );
            
            Fl_RGB_Image* imgBack = fl_imgtk::makegradation_h( boxBG->w(),
                                                               boxBG->h(),
                                                               0x333333FF,
                                                               0x151515FF,
                                                               true );
            boxBG->image( imgBack );
        }
        
        int putW = 40;
        int putH = 40;
        int putX = 15;
        int putY = ROW_Y_1;
        
        // ========= First Line : ESC, F1 .... Pause , numberics ===============

        Fl_Button* btnESC = new Fl_Button( PUT_XYWH, "ESC" );
        if ( btnESC != NULL )
        {
            btnConfig( btnESC, LBLSZ_DEFAULT, (Fl_Callback*)key_cb, 
                       (void*)(FL_Escape), KEYCOL_IMPACT );
            putX += putW + 30;
        }
        
        const char* refFuncStr[] = 
        {
            "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", 
            "F11", "F12" 
        };
        
        Fl_Button* btnFunc[12] = { NULL };
                
        for( unsigned cnt=0; cnt<12; cnt++ )
        {
            btnFunc[cnt] = new Fl_Button( PUT_XYWH, refFuncStr[cnt] );
            if ( btnFunc[cnt] != NULL )
            {
                btnConfig( btnFunc[cnt], LBLSZ_DEFAULT, \
                           (Fl_Callback*)key_cb, (void*)((uchar)(FL_F+(cnt+1))) );
                putX += putW;
                if ( ( cnt>0 ) && ( ( cnt + 1 )%4 == 0 ) )
                {
                    putX += 20;
                }
            }
        }
        
        putX = 625;
        putY = ROW_Y_1;
        
        Fl_Button* btnPrtSc = new Fl_Button( PUT_XYWH, "PrtSc" );
        if ( btnPrtSc != NULL )
        {
            btnConfig( btnPrtSc, LBLSZ_SMALL, (Fl_Callback*)key_cb, 
                       (void*)(FL_Print), KEYCOL_SPECIAL );
            putX += putW;
        }
        
        Fl_Button* btnScrLk = new Fl_Button( PUT_XYWH, "ScrLk" );
        if ( btnScrLk != NULL )
        {
            btnConfig( btnScrLk, LBLSZ_SMALL, (Fl_Callback*)key_cb, 
                       (void*)(FL_Scroll_Lock), KEYCOL_SPECIAL );
            putX += putW;
        }
        
        
        Fl_Button* btnPause = new Fl_Button( PUT_XYWH, "Pause" );
        if ( btnPause != NULL )
        {
            btnConfig( btnPause, LBLSZ_SMALL, (Fl_Callback*)key_cb, 
                       (void*)(FL_Pause), KEYCOL_SPECIAL );
            putX += putW;
        }

        putX = 15;
        putY = ROW_Y_2;
        
        const char* refNumK[] =
        {
            "`", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=" 
        };
        
        Fl_Button* btnNumK[13] = {NULL};
        
        for( unsigned cnt=0; cnt<13; cnt++ )
        {
            btnNumK[cnt] = new Fl_Button( PUT_XYWH, refNumK[cnt] );
            if ( btnNumK[cnt] != NULL )
            {
                btnConfig( btnNumK[cnt], LBLSZ_DEFAULT, (Fl_Callback*)key_cb );
                putX += putW;
            }
        }
                
        putW = 70;
        
        Fl_Button* btnBS = new Fl_Button( PUT_XYWH, "BkSpc.");
        if ( btnBS != NULL )
        {
            btnConfig( btnBS, LBLSZ_SMALL, (Fl_Callback*)key_cb, 
                       (void*)(FL_BackSpace), KEYCOL_IMPACT );
        }
        
        putX = 625;
        putW = 40;
        
        Fl_Button* btnIns = new Fl_Button( PUT_XYWH, "Ins ");
        if ( btnIns != NULL )
        {
            btnConfig( btnIns, LBLSZ_SMALL, (Fl_Callback*)key_cb, 
                       (void*)(FL_Insert), KEYCOL_SPECIAL );
            putX += putW;
        }
        
        Fl_Button* btnHome = new Fl_Button( PUT_XYWH, "Home");
        if ( btnHome != NULL )
        {
            btnConfig( btnHome, LBLSZ_SMALL, (Fl_Callback*)key_cb, 
                       (void*)(FL_Home), KEYCOL_SPECIAL );
            putX += putW;
        }
        
        Fl_Button* btnPgUp = new Fl_Button( PUT_XYWH, "PgUp ");
        if ( btnPgUp != NULL )
        {
            btnConfig( btnPgUp, LBLSZ_SMALL, (Fl_Callback*)key_cb, 
                      (void*)(FL_Page_Up), KEYCOL_SPECIAL );
            putX += putW;
        } // Fl_Button* o
        
        putX = 765;
        
        Fl_Button* btnNumL = new Fl_Button( PUT_XYWH, "Num");
        if ( btnNumL != NULL )
        {
            btnConfig( btnNumL, LBLSZ_SMALL, (Fl_Callback*)key_cb, 
                       (void*)(FL_Num_Lock), KEYCOL_SPECIAL );
            putX += putW;
        }

        Fl_Button* btnSlash = new Fl_Button( PUT_XYWH, "/");
        if ( btnSlash != NULL )
        {
            btnConfig( btnSlash, LBLSZ_DEFAULT, (Fl_Callback*)key_cb, 
                       (void*)(FL_KP+'/'), KEYCOL_SPECIAL );
            putX += putW;
        }
        
        Fl_Button* btnAster = new Fl_Button( PUT_XYWH, "*");
        if ( btnAster != NULL )
        {
            btnConfig( btnAster, LBLSZ_DEFAULT, (Fl_Callback*)key_cb, 
                       (void*)(FL_KP+'*'), KEYCOL_SPECIAL );
            putX += putW;
        }
            
        Fl_Button* btnMinus = new Fl_Button( PUT_XYWH, "-");
        if ( btnMinus != NULL )
        {
            btnConfig( btnMinus, LBLSZ_DEFAULT, (Fl_Callback*)key_cb, 
                       (void*)(FL_KP+'-'), KEYCOL_SPECIAL );
            putX += putW;            
        }
        
        // =============== Third line ==========================================
        
        putX = 15;
        putY = ROW_Y_3;
        putW = 54;
        
        Fl_Button* btnTab = new Fl_Button( PUT_XYWH, "Tab" );
        if ( btnTab != NULL )
        {
            btnConfig( btnTab, LBLSZ_SMALL, (Fl_Callback*)key_cb, 
                       (void*)(FL_Tab), KEYCOL_SPECIAL );  
            putX += putW;
        }
        
        putW = 40;
        
        const char* refK3line[] =
        {
            "Q","W","E","R","T","Y","U","I","O","P","[","]"
        };

        Fl_Button* btnK3[12] = {NULL};
        
        for ( unsigned cnt=0; cnt<12; cnt++ )
        {
            btnK3[cnt] = new Fl_Button( PUT_XYWH, refK3line[cnt] );
            if ( btnK3[cnt] != NULL )
            {
                btnConfig( btnK3[cnt], LBLSZ_DEFAULT, (Fl_Callback*)key_cb );
                putX += putW;
            }
        }

        putW = 56;
        
        Fl_Button* btnInvSlash = new Fl_Button( PUT_XYWH, "\\");
        if ( btnInvSlash != NULL )
        {
            btnConfig( btnInvSlash, LBLSZ_DEFAULT, (Fl_Callback*)key_cb, NULL,
                       KEYCOL_SPECIAL );
        }
        
        putX = 625;
        putW = 40;
        
        Fl_Button* btnDel = new Fl_Button( PUT_XYWH, "Del ");
        if ( btnDel != NULL )
        {
            btnConfig( btnDel, LBLSZ_SMALL, (Fl_Callback*)key_cb, 
                       (void*)(FL_Delete), KEYCOL_SPECIAL );
            putX += putW;
        }
        
        Fl_Button* btnEnd = new Fl_Button( PUT_XYWH, "End ");
        if ( btnEnd != NULL )
        {
            btnConfig( btnEnd, LBLSZ_SMALL, (Fl_Callback*)key_cb, 
                       (void*)(FL_End), KEYCOL_SPECIAL );
            putX += putW;
        }
        
        Fl_Button* btnPgDn = new Fl_Button( PUT_XYWH, "PgDn ");
        if ( btnPgDn != NULL )
        {
            btnConfig( btnPgDn, LBLSZ_SMALL, (Fl_Callback*)key_cb, 
                       (void*)(FL_Page_Down), KEYCOL_SPECIAL );
            putX += putW;
        }
        
        putX = 765;
        Fl_Button* btnKp7 = new Fl_Button( PUT_XYWH, "7");
        if ( btnKp7 != NULL )
        {
            btnConfig( btnKp7, LBLSZ_DEFAULT, (Fl_Callback*)key_cb, 
                      (void*)(FL_KP+'7') );
            putX += putW;
        }
        
        Fl_Button* btnKp8 = new Fl_Button( PUT_XYWH, "8");
        if ( btnKp8 != NULL )
        {
            btnConfig( btnKp8, LBLSZ_DEFAULT, (Fl_Callback*)key_cb, 
                       (void*)(FL_KP+'8') );
            putX += putW;            
        }
        
        Fl_Button* btnKp9 = new Fl_Button( PUT_XYWH, "9");
        if ( btnKp9 != NULL )
        {
            btnConfig( btnKp9, LBLSZ_DEFAULT, (Fl_Callback*)key_cb, 
                       (void*)(FL_KP+'9') );
            putX += putW;            
        }
        
        Fl_Button* btnKpPlus = new Fl_Button( PUT_XYWH * 2, "+");
        if ( btnKpPlus != NULL )
        {
            btnConfig( btnKpPlus, LBLSZ_DEFAULT, (Fl_Callback*)key_cb, 
                       (void*)(FL_KP+'+'), KEYCOL_SPECIAL );
            putX += putW;                        
        }
        
        // ============= Forth line, CapsLock, A to L, and ; ' ENTER ===========
 
        putX = 15;
        putY = ROW_Y_4;
        putW = 72;
        
        Fl_Button* btnCapsLk = new Fl_Button( PUT_XYWH, "CapsLk");
        if ( btnCapsLk != NULL )
        {
            btnConfig( btnCapsLk, LBLSZ_SMALL, (Fl_Callback*)key_cb, 
                       (void*)(FL_Caps_Lock), KEYCOL_SPECIAL );
            putX += putW;
        }
        
        putW = 40;
        
        const char* refK4line[] =
        {
            "A","S","D","F","G","H","J","K","L",";","\'"
        };

        Fl_Button* btnK4[11] = {NULL};
        
        for( unsigned cnt=0; cnt<11; cnt++ )
        {
            btnK4[cnt] = new Fl_Button( PUT_XYWH, refK4line[cnt] );
            if ( btnK4[cnt] != NULL )
            {
                btnConfig( btnK4[cnt], LBLSZ_DEFAULT, (Fl_Callback*)key_cb );
                putX += putW;                
            }
        }
        
        putW = 78;
        
        Fl_Button* btnEnter = new Fl_Button( PUT_XYWH, "Enter");
        if ( btnEnter != NULL )
        {
            btnConfig( btnEnter, LBLSZ_SMALL, (Fl_Callback*)key_cb, 
                       (void*)(FL_Enter), KEYCOL_SPECIAL );
            putX += putW;
        }
        
        putX = 765;
        putW = 40;
        
        Fl_Button* btnKp4 = new Fl_Button( PUT_XYWH, "4");
        if ( btnKp4 != NULL )
        {
            btnConfig( btnKp4, LBLSZ_DEFAULT, (Fl_Callback*)key_cb, (void*)(FL_KP+'4') );
            putX += putW;            
        }
                    
        Fl_Button* btnKp5 = new Fl_Button( PUT_XYWH, "5");
        if ( btnKp5 != NULL )
        {
            btnConfig( btnKp5, LBLSZ_DEFAULT, (Fl_Callback*)key_cb, (void*)(FL_KP+'5') );
            putX += putW;            
        }

        Fl_Button* btnKp6 = new Fl_Button( PUT_XYWH, "6");
        if ( btnKp6 != NULL )
        {
            btnConfig( btnKp6, LBLSZ_DEFAULT, (Fl_Callback*)key_cb, (void*)(FL_KP+'6') );
            putX += putW;            
        }
        
        // ============= Fifth line, Shifts, Z to M, <>? ... ===================
 
        putX = 15;
        putY = ROW_Y_5;
        putW = 90;
        
        Fl_Button* btnShfL = new Fl_Button( PUT_XYWH, "Shift");
        if ( btnShfL != NULL )
        {
            btnConfig( btnShfL, LBLSZ_SMALL, (Fl_Callback*)key_cb, 
                       (void*)(FL_Shift_L), KEYCOL_SPECIAL );
            putX += putW;
        }
        
        putW = 40;
        
        const char* refK5line[] =
        {
            "Z","X","C","V","B","N","M",",",".","/"
        };

        Fl_Button* btnK5[10] = {NULL};
        
        for (unsigned cnt=0; cnt<10; cnt++ )
        {
            btnK5[cnt] = new Fl_Button( PUT_XYWH, refK5line[cnt] );
            if ( btnK5[cnt] != NULL )
            {
                btnConfig( btnK5[cnt], LBLSZ_DEFAULT, (Fl_Callback*)key_cb );
                putX += putW;                
            }
        }
        
        putW = 100;

        Fl_Button* btnShfR = new Fl_Button( PUT_XYWH, "Shift");
        if ( btnShfR != NULL )
        {
            btnConfig( btnShfR, LBLSZ_SMALL, (Fl_Callback*)key_cb, 
                       (void*)(FL_Shift_R), KEYCOL_SPECIAL );            
        }
                
        putX = 665;
        putW = 40;
        
        Fl_Button* btnUp = new Fl_Button( PUT_XYWH, "@8->");
        if ( btnUp != NULL )
        {
            btnConfig( btnUp, LBLSZ_DEFAULT, (Fl_Callback*)key_cb, (void*)(FL_Up) );            
        }
        
        putX = 765;
        
        Fl_Button* btnKp1 = new Fl_Button( PUT_XYWH, "1");
        if ( btnKp1 != NULL )
        {
            btnConfig( btnKp1, LBLSZ_DEFAULT, (Fl_Callback*)key_cb, (void*)(FL_KP+'1') );
            putX += putW;
        }
        
        Fl_Button* btnKp2 = new Fl_Button( PUT_XYWH, "2");
        if ( btnKp2 != NULL )
        {
            btnConfig( btnKp2, LBLSZ_DEFAULT, (Fl_Callback*)key_cb, (void*)(FL_KP+'2') );
            putX += putW;
        }
        
        Fl_Button* btnKp3 = new Fl_Button( PUT_XYWH, "3");
        if ( btnKp3 != NULL )
        {
            btnConfig( btnKp3, LBLSZ_DEFAULT, (Fl_Callback*)key_cb, (void*)(FL_KP+'3') );
            putX += putW;
        }
        
        Fl_Button* btnKpEnter = new Fl_Button( putX, putY, putW, putH*2, \
                                               "@returnarrow" );
        if ( btnKpEnter != NULL )
        {
            btnConfig( btnKpEnter, LBLSZ_DEFAULT, (Fl_Callback*)key_cb, 
                       (void*)(FL_KP_Enter), KEYCOL_SPECIAL );
        } 
        
        // ============= Sixth line, Ctrls, Alts, Spaces ... ===================
        
        putX = 15;
        putY = ROW_Y_6;
        putW = 60;
        
        Fl_Button* btnCtL = new Fl_Button( PUT_XYWH, "Ctrl");
        if ( btnCtL != NULL )
        {
            btnConfig( btnCtL, LBLSZ_SMALL, (Fl_Callback*)key_cb, (void*)(FL_Control_L),
                       KEYCOL_SPECIAL );
            putX += putW;
        }
        
        Fl_Button* btnMetaL = new Fl_Button( PUT_XYWH, "Meta ");
        if ( btnMetaL != NULL )
        {
            btnConfig( btnMetaL, LBLSZ_SMALL, (Fl_Callback*)key_cb, (void*)(FL_Meta_L),
                       KEYCOL_SPECIAL );
            putX += putW;            
        }
        
        Fl_Button* btnAltL = new Fl_Button( PUT_XYWH, "Alt ");
        if ( btnAltL != NULL )
        {
            btnConfig( btnAltL, LBLSZ_SMALL, (Fl_Callback*)key_cb, (void*)(FL_Alt_L),
                       KEYCOL_SPECIAL );
            putX += putW;            
        }

        putW = 170;
        
        Fl_Button* btnSpace = new Fl_Button( PUT_XYWH, " " );
        if ( btnSpace != NULL )
        {
            btnConfig( btnSpace, LBLSZ_SMALL, (Fl_Callback*)key_cb, (void*)(' ') );
            putX += putW;
        }
        
        putW = 60;

        Fl_Button* btnAltR = new Fl_Button( PUT_XYWH, "Alt ");
        if ( btnAltR != NULL )
        {
            btnConfig( btnAltR, LBLSZ_SMALL, (Fl_Callback*)key_cb, (void*)(FL_Alt_R),
                       KEYCOL_SPECIAL );
            putX += putW;
        }
        
        Fl_Button* btnMetaR = new Fl_Button( PUT_XYWH, "Meta ");
        if ( btnMetaR != NULL )
        {
            btnConfig( btnMetaR, LBLSZ_SMALL, (Fl_Callback*)key_cb, 
                       (void*)(FL_Meta_R), KEYCOL_SPECIAL );
            putX += putW;
        }
        
        Fl_Button* btnMenu = new Fl_Button( PUT_XYWH, "Menu ");
        if ( btnMenu != NULL )
        {
            btnConfig( btnMenu, LBLSZ_SMALL, (Fl_Callback*)key_cb, 
                       (void*)(FL_Menu), KEYCOL_SPECIAL );
            putX += putW;
        }
        
        Fl_Button* btnCtR = new Fl_Button( PUT_XYWH, "Ctrl");
        if ( btnCtR != NULL )
        {
            btnConfig( btnCtR, LBLSZ_SMALL, (Fl_Callback*)key_cb, 
                       (void*)(FL_Control_R), KEYCOL_SPECIAL );
            putX += putW;
        }

        putX = 625;
        putW = 40;
        
        Fl_Button* btnLeft = new Fl_Button( PUT_XYWH, "@4->");
        if ( btnLeft != NULL )
        {
            btnConfig( btnLeft, LBLSZ_DEFAULT, (Fl_Callback*)key_cb, 
                       (void*)(FL_Left) );
            putX += putW;
        }
        
        Fl_Button* btnDown = new Fl_Button( PUT_XYWH, "@2->");
        if ( btnDown != NULL )
        {
            btnConfig( btnDown, LBLSZ_DEFAULT, (Fl_Callback*)key_cb, 
                       (void*)(FL_Down) );
            putX += putW;
        }

        Fl_Button* btnRight = new Fl_Button( PUT_XYWH, "@6->");
        if ( btnRight != NULL )
        {
            btnConfig( btnRight, LBLSZ_DEFAULT, (Fl_Callback*)key_cb, 
                       (void*)(FL_Right) );
            putX += putW;
        }
        
        putX = 765;
        putW = 80;
        
        Fl_Button* btnKp0 = new Fl_Button( PUT_XYWH, "0");
        if ( btnKp0 != NULL )
        {
            btnConfig( btnKp0, LBLSZ_DEFAULT, (Fl_Callback*)key_cb, 
                       (void*)(FL_KP+'0') );
            putX += putW;
        }
        
        putW = 40;
        
        Fl_Button* btnKpDot = new Fl_Button( PUT_XYWH, ".");
        if ( btnKpDot != NULL )
        {
            btnConfig( btnKpDot, LBLSZ_DEFAULT, (Fl_Callback*)key_cb, 
                       (void*)(FL_KP+'.') );
            putX += putW;
        }
                    
        // ============ Event key info =========================================
        
        putX = 765;
        putY = 15;
        putW = 160;
        putH = 80;
        
        Fl_Box* boxEventState = new Fl_Box( PUT_XYWH, "Event states:");
        if ( boxEventState != NULL )
        {
            boxEventState->labelcolor( 0xFF5555FF );
            boxEventState->labelsize(LBLSZ_SMALL);
            boxEventState->align(Fl_Align(FL_ALIGN_TOP_LEFT));
        }
        
        putW = 40;
        putH = 20;
        
        Fl_Button* btnESshift = new Fl_Button( PUT_XYWH, "shift ");
        if ( btnESshift != NULL )
        {
            btnConfig( btnESshift, LBLSZ_SMALL, (Fl_Callback*)shift_cb, 
                       (void*)(FL_SHIFT), KEYCOL_ESTATE );
            putX += putW;
        }

        Fl_Button* btnESlock = new Fl_Button( PUT_XYWH, "lock ");
        if ( btnESlock != NULL )
        {
            btnConfig( btnESlock, LBLSZ_SMALL, (Fl_Callback*)shift_cb,
                       (void*)(FL_CAPS_LOCK), KEYCOL_ESTATE );
            putX += putW;
        }
        
        Fl_Button* btnESctrl = new Fl_Button( PUT_XYWH, "ctrl");
        if ( btnESctrl != NULL )
        {
            btnConfig( btnESctrl, LBLSZ_SMALL, (Fl_Callback*)shift_cb, 
                       (void*)(FL_CTRL), KEYCOL_ESTATE );
            putX += putW;
        }

        Fl_Button* btnESalt = new Fl_Button( PUT_XYWH, "alt");
        if ( btnESalt != NULL )
        {
            btnConfig( btnESalt, LBLSZ_SMALL, (Fl_Callback*)shift_cb, 
                       (void*)(FL_ALT), KEYCOL_ESTATE );
            putX += putW;
        }
            
        putX = 765;
        putY += putH;
        
        Fl_Button* btnESnumlock = new Fl_Button( PUT_XYWH, "num");
        if ( btnESnumlock != NULL )
        {
            btnConfig( btnESnumlock, LBLSZ_SMALL, (Fl_Callback*)shift_cb, 
                       (void*)(FL_NUM_LOCK), KEYCOL_ESTATE );
            putX += putW;
        }
        
        Fl_Button* btnESspc = new Fl_Button( PUT_XYWH, "spc");
        if ( btnESspc != NULL )
        {
            btnConfig( btnESspc, LBLSZ_SMALL, (Fl_Callback*)shift_cb, (void*)(0x20), 
                       KEYCOL_ESTATE );
            putX += putW;
        }
            
        Fl_Button* btnESmeta = new Fl_Button( PUT_XYWH, "meta ");
        if ( btnESmeta != NULL )
        {
            btnConfig( btnESmeta, LBLSZ_SMALL, (Fl_Callback*)shift_cb, (void*)(FL_META), 
                       KEYCOL_ESTATE );
            putX += putW;
        }
            
        Fl_Button* btnESsclk = new Fl_Button( PUT_XYWH, "sclk");
        if ( btnESsclk != NULL )
        {
            btnConfig( btnESsclk, LBLSZ_SMALL, (Fl_Callback*)shift_cb, 
                       (void*)(FL_SCROLL_LOCK), KEYCOL_ESTATE );
            putX += putW;
        }
                
        putX = 765;
        putY += putH;
        
        Fl_Button* btnESmouse1 = new Fl_Button( PUT_XYWH, "m.b1");
        if ( btnESmouse1 != NULL )
        {
            btnConfig( btnESmouse1, LBLSZ_SMALL, (Fl_Callback*)shift_cb, 
                       (void*)(FL_BUTTON1), KEYCOL_ESTATE );
            putX += putW;
        }
        
        Fl_Button* btnESmouse2 = new Fl_Button( PUT_XYWH, "m.b2");
        if ( btnESmouse2 != NULL )
        {
            btnConfig( btnESmouse2, LBLSZ_SMALL, (Fl_Callback*)shift_cb, 
                       (void*)(FL_BUTTON2), KEYCOL_ESTATE );
            putX += putW;
        }

        Fl_Button* btnESmouse3 = new Fl_Button( PUT_XYWH, "m.b3");
        if ( btnESmouse3 != NULL )
        {
            btnConfig( btnESmouse3, LBLSZ_SMALL, (Fl_Callback*)shift_cb, 
                       (void*)(FL_BUTTON3), KEYCOL_ESTATE );
            putX += putW;
        }
            

        Fl_Button* btnESmousewh = new Fl_Button( PUT_XYWH, "whl");
        if ( btnESmousewh != NULL )
        {
            btnConfig( btnESmousewh, LBLSZ_SMALL, (Fl_Callback*)shift_cb, 
                       (void*)(0x800), KEYCOL_ESTATE );
            putX += putW;
        }
        
        putX = 765;
        putY += putH;
        
        Fl_Button* btnU1 = new Fl_Button( PUT_XYWH, "u1");
        if ( btnU1 != NULL )
        {
            btnConfig( btnU1, LBLSZ_SMALL, (Fl_Callback*)shift_cb, 
                       (void*)(0x1000), KEYCOL_ESTATE );
            putX += putW;
        }
        
        Fl_Button* btnU2 = new Fl_Button( PUT_XYWH, "u2");
        if ( btnU2 != NULL )
        {
            btnConfig( btnU2, LBLSZ_SMALL, (Fl_Callback*)shift_cb, 
                       (void*)(0x2000), KEYCOL_ESTATE );
            putX += putW;
        }
        
        Fl_Button* btnU3 = new Fl_Button( PUT_XYWH, "u3");
        if ( btnU3 != NULL )
        {
            btnConfig( btnU3, LBLSZ_SMALL, (Fl_Callback*)shift_cb, 
                       (void*)(0x4000), KEYCOL_ESTATE );
            putX += putW;
        }

        Fl_Button* btnU4 = new Fl_Button( PUT_XYWH, "u4");
        if ( btnU4 != NULL )
        {
            btnConfig( btnU4, LBLSZ_SMALL, (Fl_Callback*)shift_cb, 
                       (void*)(0x8000), KEYCOL_ESTATE );
            putX += putW;
        }

        putX = 765;
        putY = ROW_Y_1;
        putH = 40;
        putW = 40;

        Fl_Button* btnHelp = new Fl_Button( PUT_XYWH, "Help");
        if ( btnHelp != NULL )
        {
            btnConfig( btnHelp, LBLSZ_SMALL, (Fl_Callback*)key_cb, 
                       (void*)(FL_Help), KEYCOL_SPECIAL );
            putX += putW;
        }

        Fl_Button* btnEqual = new Fl_Button( PUT_XYWH, "=");
        if ( btnEqual != NULL )
        {
            btnConfig( btnEqual, LBLSZ_DEFAULT, (Fl_Callback*)key_cb, 
                       (void*)(FL_KP+'='), KEYCOL_SPECIAL );
            putX += putW;
        }

        
        roller_x = new Fl_Dial( PUT_XYWH, "X:");
        if ( roller_x != NULL )
        {
            roller_x->color( KEYCOL_WHEEL );
            roller_x->selection_color( KEYCOL_SPECIAL );
            roller_x->labelcolor( winKbdr->labelcolor() );
            roller_x->labelsize(LBLSZ_DEFAULT);
            roller_x->step(0.1);
            roller_x->callback((Fl_Callback*)wheel_cb);
            roller_x->align(Fl_Align(FL_ALIGN_TOP_LEFT));
            putX += putW;
        }
        
        roller_y = new Fl_Dial( PUT_XYWH, "Y:");
        if ( roller_y != NULL )
        {
            roller_y->color( KEYCOL_WHEEL );
            roller_y->selection_color( KEYCOL_SPECIAL );
            roller_y->labelcolor( winKbdr->labelcolor() );
            roller_y->labelsize(LBLSZ_DEFAULT);
            roller_y->step(0.1);
            roller_y->callback((Fl_Callback*)wheel_cb);
            roller_y->align(Fl_Align(FL_ALIGN_TOP_LEFT));
            putX += putW;
        }
        
        winKbdr->end();
    }

    return winKbdr;
}
