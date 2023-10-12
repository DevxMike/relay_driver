#include <Arduino.h>
#include "button.h"
#include "system.h"
#include "timer.h"
#include "relays.h"
#include "animation.h"


#define button_green_1_pin 8
#define button_yellow_1_pin 2
#define button_white_1_pin 3
#define button_green_2_pin 5
#define button_yellow_2_pin 4
#define button_white_2_pin 6
#define reset_button_pin 7

push_button btn_green_1(button_green_1_pin, button_callbacks::green_btn_1_cback);
push_button btn_yellow_1(button_yellow_1_pin, button_callbacks::yellow_btn_1_cback);
push_button btn_white_1(button_white_1_pin, button_callbacks::white_btn_1_cback);
push_button btn_yellow_2(button_yellow_2_pin, button_callbacks::yellow_btn_2_cback);
push_button btn_green_2(button_green_2_pin, button_callbacks::green_btn_2_cback);
push_button btn_white_2(button_white_2_pin, button_callbacks::white_btn_2_cback);
hold_push_button btn_reset(reset_button_pin, [](){}, button_callbacks::reset_btn_cback);
timer relay_manager::timers[timer_count]{

};

digital_output relay_1(relay_1_pin);
digital_output relay_2(relay_2_pin);

digital_output *relay_manager::relay_outputs[output_count]{
  &relay_1,
  &relay_2
};

// timer test_timer;
// timer test_timer1;

push_button* button_manager::keyboard[interface_size] = {
  &btn_green_1,
  &btn_yellow_1,
  &btn_white_1,
  &btn_green_2,
  &btn_yellow_2,
  &btn_white_2,
  &btn_reset
};

bool relay_manager::relay_1_in_use{ false };
bool relay_manager::relay_2_in_use{ false };

uint8_t relay_manager::flags{ 0xff };

timer relay_manager::relay_timers[output_count]{};

timer animation_manager::animation_timer{};
long animation_manager::buffer[timer_count] { 0 };

Adafruit_NeoPixel animation_manager::strip1(Adafruit_NeoPixel(54, STRIP_1_PIN, NEO_GRB + NEO_KHZ800));
Adafruit_NeoPixel animation_manager::strip2(Adafruit_NeoPixel(54, STRIP_2_PIN, NEO_GRB + NEO_KHZ800));

void setup() {
  Serial.begin(9800);
  
  Serial.println("Booting");

  btn_green_1.init();
  btn_green_2.init();
  btn_yellow_1.init();
  btn_yellow_2.init();
  btn_white_1.init();
  btn_white_2.init();
  btn_reset.init();

  relay_1.init();
  relay_2.init();
  // test_timer1.set_timer(1000, [](){ Serial.println(test_timer.get_time_left()); });
  // test_timer.set_timer(24000, [](){ Serial.println("Main timer callback"); });

  animation_manager::strip1.begin();
  animation_manager::strip2.begin();
}

void loop() {
  button_manager::main();
  relay_manager::main();
  animation_manager::main();
  // test_timer.update();
  // test_timer1.update();
}