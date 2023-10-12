#include "system.h"
#include "relays.h"

void button_callbacks::green_btn_1_cback(){
    if(relay_manager::is_flag_set(relay_1_btn_green_1)){
        if(relay_manager::turn_on_relay_1()){
            Serial.println("Green 1 action");
            relay_manager::clear_flag(relay_1_btn_green_1);
        }
    }
}
void button_callbacks::yellow_btn_1_cback(){
    if (relay_manager::is_flag_set(relay_2_btn_yellow_1)){
        if (relay_manager::turn_on_relay_2()){
            Serial.println("Yellow 1 action");
            relay_manager::clear_flag(relay_2_btn_yellow_1);
        }
    }
}
void button_callbacks::white_btn_1_cback(){

}
void button_callbacks::green_btn_2_cback(){
    if (relay_manager::is_flag_set(relay_1_btn_green_2)){
        if(relay_manager::turn_on_relay_1()){
            Serial.println("Green 2 action");
            relay_manager::clear_flag(relay_1_btn_green_2);
        }
    }
}
void button_callbacks::yellow_btn_2_cback(){
    if (relay_manager::is_flag_set(relay_2_btn_yellow_2)){
        if(relay_manager::turn_on_relay_2()){
            Serial.println("Yellow 2 action");
            relay_manager::clear_flag(relay_2_btn_yellow_2);
        }
    }
}
void button_callbacks::white_btn_2_cback(){

}
void button_callbacks::reset_btn_cback(){
    asm("jmp 0x0000");
}