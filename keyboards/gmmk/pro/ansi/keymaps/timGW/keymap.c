/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum custom_layers {
    _BASE,
    _FN1,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // default first layer
    //      ESC      F1       F2       F3       F4       F5           F6       F7       F8       F9       F10      F11      F12      Prt           Rotary(Mute)
    //      ~        1        2        3        4        5            6        7        8        9        0         -       (=)      BackSpc           Del
    //      Tab      Q        W        E        R        T            Y        U        I        O        P        [        ]        \                 PgUp
    //      Caps     A        S        D        F        G            H        J        K        L        ;        "                 Enter             PgDn
    //      Sh_L              Z        X        C        V            B        N        M        ,        .        ?                 Sh_R     Up       End
    //      Ct_L     Win_L    Alt_L                                SPACE                               Alt_R    FN       Ct_R     Left     Down     Right
	[_BASE] = LAYOUT(
	        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   SCMD(KC_R), KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  SCMD(KC_4),       KC_MUTE,
	        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,     KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
	        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
	        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,     KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                    KC_PGDN,
	        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,     KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT, KC_UP,   KC_END,
	        KC_LCTL, KC_LALT, KC_LGUI,                             KC_SPC,                                KC_RGUI, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
	),


    // Second layer when Fn is pressed
    //      RBG_tog  bright-  bright+  Hue-    Hue+      ▼         ▼        ▼        ▼        ▼        ▼        ▼        ▼        ▼                 Rotary(play)
    //      ▼        ▼        ▼        ▼        ▼        ▼         ▼        ▼        ▼        ▼        ▼        ▼        ▼        ▼                 ▼
    //      ▼        ▼        ▼        ▼        ▼        ▼         ▼        ▼        ▼        ▼        ▼        ▼        ▼        Reset             ▼
    //      ▼        ▼        ▼        ▼        ▼        ▼         ▼        ▼        ▼        ▼        ▼        ▼                 ▼                 ▼
    //      ▼                 ▼        ▼        ▼        ▼         ▼        ▼        ▼        ▼        ▼        ▼                 ▼      Play       ▼
    //      ▼        ▼        ▼                                    ▼                                   ▼        ▼        ▼        Prev    ▼       Next
    [_FN1] = LAYOUT(
            RGB_TOG, RGB_VAD, RGB_VAI, RGB_HUD, RGB_HUI, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_MPLY,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,             KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, NK_TOGG,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, RGB_MOD,  KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS,                             KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, RGB_SPD, RGB_RMOD, RGB_SPI
    )
};

#ifdef ENCODER_ENABLE       // Rotary knob Functionality

    bool encoder_update_user(uint8_t index, bool clockwise) {

		switch(get_highest_layer(layer_state)) {
			case _FN1:
			if (clockwise) {
				tap_code16(KC_MNXT);
			} else {
				tap_code16(KC_MPRV);
			}
			break;

			case _BASE:
			default:
			if (clockwise) {
				tap_code(KC_VOLU);
			} else {
				tap_code(KC_VOLD);
			}
			break;
		}
        return true;
    }
#endif
