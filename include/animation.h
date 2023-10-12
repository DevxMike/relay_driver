#ifndef animation_h
#define animation_h

#include "relays.h"
#include "timer.h"
#include "Adafruit_NeoPixel.h"

#define STRIP_1_PIN 9
#define STRIP_2_PIN 12

constexpr unsigned long animation_timer_period = 500;

class animation_manager{
private:
    static timer animation_timer;
    static long buffer[timer_count];
    
    static void on_elapsed_handler(){
        relay_manager::get_button_timers(buffer, timer_count);
    }

public:
    static Adafruit_NeoPixel strip1;
    static Adafruit_NeoPixel strip2;

    static void main();
};

#endif