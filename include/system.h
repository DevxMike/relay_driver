#ifndef sys_h
#define sys_h

#include "Arduino.h"
#include "timer.h"

class button_callbacks{
public:
    static void green_btn_1_cback();
    static void yellow_btn_1_cback();
    static void white_btn_1_cback();
    static void green_btn_2_cback();
    static void yellow_btn_2_cback();
    static void white_btn_2_cback();
    static void reset_btn_cback();
    static bool users_ready();
    static bool is_user_1_ready();
    static bool is_user_2_ready();
};

#endif