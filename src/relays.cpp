#include "relays.h"

void relay_manager::clear_flag(uint8_t flag){
    cback_type cback = timer_1_cback;

    switch(flag){
        case relay_1_btn_green_1:
            cback = timer_1_cback;
            break;

        case relay_2_btn_yellow_1:
            cback = timer_2_cback;
            break;

        case relay_1_btn_green_2:
            cback = timer_3_cback;
            break;

        case relay_2_btn_yellow_2:
            cback = timer_4_cback;
            break;
    }

    timers[flag].set_timer(timer_period, cback);
    flags &= ~(1 << flag);
}

void relay_manager::set_flag(uint8_t flag){
    if((1 << flag) & flags){

    }
    else{
        flags |= (1 << flag);
    }
}

bool relay_manager::is_flag_set(uint8_t flag){
    return (1 << flag) & flags;
}

void relay_manager::timer_1_cback(){
    set_flag(relay_1_btn_green_1);
    Serial.println("Green button 1 ready");
    timers[relay_1_btn_green_1].stop_timer();
}
void relay_manager::timer_2_cback(){
    set_flag(relay_2_btn_yellow_1);
    Serial.println("Yellow button 1 ready");
    timers[relay_2_btn_yellow_1].stop_timer();
}
void relay_manager::timer_3_cback(){
    set_flag(relay_1_btn_green_2);
    Serial.println("Green button 2 ready");
    timers[relay_1_btn_green_2].stop_timer();
}
void relay_manager::timer_4_cback(){
    set_flag(relay_2_btn_yellow_2);
    Serial.println("Yellow button 2 ready");
    timers[relay_2_btn_yellow_2].stop_timer();
}

bool relay_manager::turn_on_relay_1(){
    if(relay_1_in_use){
        return false;
    }
    else{
        relay_1_in_use = true;
        relay_outputs[relay_1_enum]->write(true);
        relay_timers[relay_1_enum].set_timer(relay_1_delay, relay_1_callback);
        return true;
    }
}
bool relay_manager::turn_on_relay_2(){
    if(relay_2_in_use){
        return false;
    }
    else{
        relay_2_in_use = true;
        relay_outputs[relay_2_enum]->write(true);
        relay_timers[relay_2_enum].set_timer(relay_2_delay, relay_2_callback);
        
        return true;
    }
}

void relay_manager::get_button_timers(long *array, uint8_t len){
    for(uint8_t i = 0; i < len; ++i){
        array[i] = timers[i].get_elapsed();
    }
}

void relay_manager::main(){
    for(uint8_t i = 0; i < timer_count; ++i){
        timers[i].update();
    }

    for(uint8_t i = 0; i < output_count; ++i){
        relay_timers[i].update();
    }
}