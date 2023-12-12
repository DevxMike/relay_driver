Relay Control System

Overview:
This Arduino-based system integrates introduces relay control to perform actions based on user input. The code includes functionalities for button handling, relay management, and LED animations.

Components:

    animation.h: Defines the animation manager class for controlling LED animations.
    button.h: Implements button classes for push and hold buttons.
    system.h: Manages the overall system, including button callbacks and global variables.
    timer.h: Defines a timer class for managing time-related operations.
    relays.h: Handles relay-related functionalities.

Button Handling:
The system supports both push and hold buttons. Buttons are assigned to specific pins, and their states are updated in the button_manager::main function. Callbacks are triggered based on button events, such as short presses or long holds.

Relay Management:
The relay manager (relays.h) controls two relays (relay_1 and relay_2). Relay actions are triggered by button events, such as button presses, and are subject to timer delays. The system ensures that relays are not activated simultaneously.

Time elapsed animation:
It is implemented in the animation_manager class. LED animations are controlled based on button states. The system uses NeoPixel strips (strip1 and strip2) for visual feedback.

System Initialization:
The setup function initializes components, including buttons, relays, and LED strips. Serial communication is also initialized for debugging purposes.

Main Loop:
The loop function runs the main system loop, where button, relay, and animation updates occur. The system continuously checks for button events, updates relay states, and manages LED animations.

Button Callbacks:
Button callbacks (button_callbacks) define actions triggered by button events. For example, when both users are ready (users_ready), pressing the green button for user 1 (green_btn_1_cback) activates relay_1 after a predefined delay.

Reset Functionality:
A reset button (reset_btn_cback) is included to reset the system, causing the program to jump to the beginning.

Readme Instructions:

    Connect buttons to the specified pins (green, yellow, white, and reset).
    Connect relays to the designated relay pins (relay_1_pin and relay_2_pin).
    Ensure proper wiring for LED strips (strip1 and strip2).
    Upload the code to an Arduino board using the Arduino IDE.
    Monitor serial output for system status and debugging.
