// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "../../drivers/oled/oled_driver.h"
#include <stdio.h>

enum layers {
    BASE,    // Capa base
    FN,      // Capa de funciones
    PAD,
    FLECHAS      // Capa numérica 
};

// Define las teclas personalizadas
enum custom_keycodes {
   OPEN_CHROME, // Asegura que el código de la tecla sea únicO
   OPEN_SPOTIFY,
   OPEN_VSCODE,
};

uint8_t current_layer = BASE;
bool encoder_button_pressed = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base Layer: Default Layer
     * ,-------------------------------------------------------.
     * | CTRLC | CTRLV | OPEN VC | OPEN CHROME | OPEN SPOTIFY |
     * |------------------------------------------------------|
     * | MUTE | PREVIOUS | PLAY | NEXT | DORMIR |
     * `-------------------------------------------------------'
     */
    [BASE] = LAYOUT(
        LCTL(KC_C), LCTL(KC_V), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4),
        KC_AUDIO_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, TO(FN)
    ),

    /* Function Layer: Media/Function Keys
     * ,------------------------------.
     * | F13 | F14 | F15 | F16 | F17  | 
     * |------------------------------|
     * | F18 | F19 | F20 | F21 | CAPA |
     * `------------------------------'
     */
    [FN] = LAYOUT(
        KC_F13, KC_F14, KC_F15, KC_F16, KC_F17,
        KC_F18, KC_F19, KC_F20, KC_F21, TO(PAD)
    ),

    /* Numeric Layer: Numeric Pad
     * ,--------------------------------.
     * | K_0 |  K_1 | K_2 | K_3  | K_4 |
     * |-------------------------------|
     * | K_5 |  K_6 | K_7 | K_8  | K_9 |
     * `--------------------------------'
     */
    [PAD] = LAYOUT(
        KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_4,
        KC_KP_5, KC_KP_6, KC_KP_7, KC_KP_8, TO(FLECHAS)
    ),
    [FLECHAS] = LAYOUT(
        KC_NO, KC_NO, KC_UP, KC_NO, KC_NO,
        KC_NO, KC_LEFT, KC_DOWN, KC_RIGHT, TO(BASE)
    )
};
void keyboard_pre_init_user(void) {
    setPinInputHigh(ENCODER_BUTTON_PIN);  // Activar pull-up interno para evitar estado flotante
}

void check_encoder_button(void) {
    if (!readPin(ENCODER_BUTTON_PIN)) {  // Si el pin está en LOW, el botón está presionado
        if (!encoder_button_pressed) {   // Solo actúa si el botón no estaba presionado antes
            encoder_button_pressed = true;  // Marcar que el botón está presionado
            tap_code(KC_MUTE);  // Enviar el código de mute
        }
    } else {
        // Cuando se suelta el botón, se resetea el estado
        encoder_button_pressed = false;
    }
}

void matrix_scan_user(void) {
    check_encoder_button();  // Verificar continuamente el estado del botón
}

// // Manejo de la rotación del encoder para controlar el volumen
// bool encoder_update_user(uint8_t index, bool clockwise) {
//     if (index == 0) { /* First encoder */
//         if (clockwise) {
//             tap_code(KC_VOLU);
//         } else {
//             tap_code(KC_VOLD);
//         }
//     } 
//     return false;
// }

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    
    [BASE]    = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }, // como tenías
    [FN]      = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [PAD]     = { ENCODER_CCW_CW(KC_KP_MINUS, KC_KP_PLUS) },
    [FLECHAS] = { ENCODER_CCW_CW(KC_LEFT, KC_RIGHT) },
};

// 'pixil-frame-0', 128x32px
// 'pixil-frame-0 (1)', 64x32px
static const char mi_logo[] PROGMEM = {
    
   // 'pixil-frame-0 (1)', 64x32px
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 
    0x00, 0x00, 0x3f, 0x3f, 0x3f, 0xc7, 0xc7, 0xc7, 0xf8, 0xf8, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xc7, 0xc7, 0xc7, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xc7, 0xc7, 0xc7, 
    0xff, 0xff, 0xff, 0xc7, 0xc7, 0xc7, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xc7, 0xc7, 0xc7, 0xff, 
    0x80, 0x80, 0x80, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0xff, 0xff, 0xff, 0x80, 
    0x80, 0x80, 0xfe, 0xfe, 0xfe, 0xf1, 0xf1, 0xf1, 0x8f, 0x8f, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xf1, 0xf1, 0xf1, 0x8e, 0x8e, 0x8e, 0x8e, 0x8e, 0x8e, 0xf1, 0xf1, 0xf1, 
    0xff, 0xff, 0xff, 0xf1, 0xf1, 0xf1, 0x8e, 0x8e, 0x8e, 0x8e, 0x8e, 0x8e, 0xf1, 0xf1, 0xf1, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 272)
// const int epd_bitmap_allArray_LEN = 1;
// const unsigned char* epd_bitmap_allArray[1] = {
// 	epd_bitmap_pixil_frame_0__1_
// };


// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 272
uint8_t last_layer = BASE;

bool oled_task_user() {
    uint8_t current_layer = get_highest_layer(layer_state);

    if (current_layer != last_layer) {
        last_layer = current_layer;
        oled_clear();

        

        oled_set_cursor(4, 1);
        oled_write_raw_P(mi_logo, sizeof(mi_logo));

        oled_set_cursor(0, 1);

        switch (current_layer) {
            case BASE:
                oled_write_ln("Capa: BASE", false);
                oled_write_ln("CPY PSTE VC", false);
                oled_write_ln("CHR SPTY MUTE", false);
                break;
            case FN:
                oled_write_ln("Capa: FN", false);
                oled_write_ln("F13 F14 F15", false);
                oled_write_ln("F16 F17 F18", false);
                break;
            case PAD:
                oled_write_ln("Capa: PAD", false);
                oled_write_ln("0 1 2 3 4", false);
                oled_write_ln("5 6 7 8 9", false);
                break;
            case FLECHAS:
                oled_write_ln("Capa: FLECHAS", false);
                oled_write_ln("   ↑   ", false);
                oled_write_ln("← ↓ →", false);
                break;
            default:
                oled_write_ln("Layer: ???", false);
                break;
        }
    }
    return false;
};


#ifdef VIA_ENABLE
#include "via.h"
#endif


