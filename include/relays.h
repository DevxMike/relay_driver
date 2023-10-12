#ifndef relay_h
#define relay_h

#include "timer.h"
#include "dig_output.h"

#define relay_1_btn_green_1 0
#define relay_2_btn_yellow_1 1
#define relay_1_btn_green_2 2
#define relay_2_btn_yellow_2 3

#define relay_1_pin 10
#define relay_2_pin 11

#define relay_1_delay 1000
#define relay_2_delay 2000

constexpr uint8_t timer_count = 4;
constexpr unsigned long timer_period = 12000;
constexpr uint8_t output_count = 2;

class relay_manager{
private:
    static uint8_t flags;
    static timer timers[timer_count];

    static digital_output* relay_outputs[output_count];

    static void timer_1_cback();
    static void timer_2_cback();
    static void timer_3_cback();
    static void timer_4_cback();

    static bool relay_1_in_use;
    static bool relay_2_in_use;
    
    static timer relay_timers[output_count];

    static void relay_1_callback(){
        relay_1_in_use = false;
        relay_timers[0].stop_timer();
        relay_outputs[0]->write(false);
    }
    static void relay_2_callback(){
        relay_2_in_use = false;
        relay_timers[1].stop_timer();
        relay_outputs[1]->write(false);
    }

public:
    static void clear_flag(uint8_t flag);
    static void set_flag(uint8_t flag);
    static bool is_flag_set(uint8_t flag);

    static void main();

    static bool turn_on_relay_1();
    static bool turn_on_relay_2();
};

#endif