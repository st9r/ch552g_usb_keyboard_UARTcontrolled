#include "configuration.h"
#include "src/userUsbHidKeyboardMouse/USBHIDKeyboardMouse.h"

const keyboard_configuration_t configurations[NUM_CONFIGURATION] = {
    {
        .button = { // Custom configuration
            [BTN_1] = {
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {KEY_TAB}, // TAB
                    .length = 1,
                    .delay = 0
                }
            },
            [BTN_2] = { 
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {KEY_ESC}, // ESC
                    .length = 1,
                    .delay = 0
                }
            },
            [BTN_3] = {
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {KEY_DOWN_ARROW}, // 
                    .length = 1,
                    .delay = 0
                }
            },
            [ENC_CW] = { 
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {KEY_RIGHT_ARROW},
                    .length = 1,
                    .delay = 0
                }
            },
            [ENC_CCW] = { 
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {KEY_LEFT_ARROW},
                    .length = 1,
                    .delay = 0
                }
            },
            [BTN_ENC] = { 
                .type = BUTTON_SEQUENCE,
                .function.sequence = {
                    .sequence = {KEY_RETURN},
                    .length = 2,
                    .delay = 0
                }
            },
        }
    }
};
