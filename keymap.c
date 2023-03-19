/* Copyright 2021 Jay Greco
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum layers {
    _NUMP = 0,
    _UTIL = 1,
    _MEDI = 2,
    _MOD1 = 3,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_NUMP] = LAYOUT(
                                        KC_NO,      KC_NUM,     KC_PSLS,
    KC_VOLU,    KC_VOLD,    KC_P7,      KC_P8,      KC_P9,      KC_PAST,
    KC_NO,      KC_NO,      KC_P4,      KC_P5,      KC_P6,      KC_PMNS,
    KC_NO,      KC_NO,      KC_P1,      KC_P2,      KC_P3,      KC_PPLS,
    KC_NO,      KC_NO,      KC_P0,      KC_P0,      KC_PDOT,    LT(_MOD1,KC_PENT)
    ),

    [_UTIL] = LAYOUT(
                                        KC_NO,      KC_NO,      KC_NO,
    KC_WH_D,    KC_WH_U,    KC_NO,      KC_NO,      KC_NO,      KC_NO,
    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
    KC_NO,      KC_NO,      LGUI(LSFT(KC_PSCR)),KC_NO,KC_PSCR,  LT(_MOD1,KC_PENT)
    ),

    [_MEDI] = LAYOUT(
                                        KC_NO,      HYPR(KC_M), KC_NO,
    KC_VOLU,    KC_VOLD,    KC_NO,      KC_VOLU,    KC_NO,      KC_NO,
    KC_NO,      KC_NO,      KC_MPRV,    KC_MPLY,    KC_MNXT,    KC_NO,
    KC_NO,      KC_NO,      KC_NO,      KC_VOLD,    KC_NO,      KC_NO,
    KC_NO,      KC_NO,      HYPR(KC_N),HYPR(KC_N),  KC_MUTE,    LT(_MOD1,KC_PENT)
    ),

    [_MOD1] = LAYOUT(
                                        QK_BOOT,    KC_NO,      TO(_NUMP),
    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      TO(_UTIL),
    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      TO(_MEDI),
    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      LT(_MOD1,KC_PENT)
    ),
};

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Text
    oled_write_ln_P(PSTR("Layer:    Lock:     "), false);

    // Host Keyboard Layer Status
    //oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _NUMP:
            oled_write_P(PSTR("NUMP      "), false);
            break;
        case _UTIL:
            oled_write_P(PSTR("UTIL      "), false);
            break;
        case _MEDI:
            oled_write_P(PSTR("MEDI      "), false);
            break;
        case _MOD1:
            oled_write_P(PSTR("MOD1"), true);
            oled_write_P(PSTR("      "), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined "), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR") : PSTR("  "), false);
    oled_write_P(PSTR("\n"), true);

    //uint8_t bright = oled_get_brightness();

    // Text
    oled_write_ln_P(PSTR("--------------------"), false);
    //oled_write_ln_P(printf(bright), false);


    return false;

}
#endif
