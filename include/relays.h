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

#define relay_1_delay 2000
#define relay_2_delay 2000

enum{
    relay_1_enum = 0,
    relay_2_enum = 1
};

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

    enum{
        relay_set = 0,
        relay_reset = 1
    };

    static void relay_1_callback(){
        static uint8_t state = relay_manager::relay_set;
        switch(state){
        case relay_manager::relay_set:
            relay_outputs[relay_1_enum]->write(false);
            state = relay_manager::relay_reset;
            break;

        case relay_manager::relay_reset:
            relay_1_in_use = false;
            relay_timers[relay_1_enum].stop_timer();
            state = relay_manager::relay_set;
            break;
        }
    }
    static void relay_2_callback(){
        static uint8_t state = relay_manager::relay_set;
        switch(state){
            case relay_manager::relay_set:
                relay_outputs[relay_2_enum]->write(false);
                state = relay_manager::relay_reset;
                break;

            case relay_manager::relay_reset:
                relay_2_in_use = false;
                relay_timers[relay_2_enum].stop_timer();
                state = relay_manager::relay_set;
                break;
        }
    }

public:
    static void clear_flag(uint8_t flag);
    static void set_flag(uint8_t flag);
    static bool is_flag_set(uint8_t flag);

    static void main();

    static bool turn_on_relay_1();
    static bool turn_on_relay_2();

    static void get_button_timers(long* array, uint8_t len);
};

#endif