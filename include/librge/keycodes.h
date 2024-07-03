#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum
    {
        rgeKEY_NULL = 0, // Key: NULL, used for no key pressed
        // Alphanumeric keys
        rgeKEY_APOSTROPHE = 39,    // Key: '
        rgeKEY_COMMA = 44,         // Key: ,
        rgeKEY_MINUS = 45,         // Key: -
        rgeKEY_PERIOD = 46,        // Key: .
        rgeKEY_SLASH = 47,         // Key: /
        rgeKEY_ZERO = 48,          // Key: 0
        rgeKEY_ONE = 49,           // Key: 1
        rgeKEY_TWO = 50,           // Key: 2
        rgeKEY_THREE = 51,         // Key: 3
        rgeKEY_FOUR = 52,          // Key: 4
        rgeKEY_FIVE = 53,          // Key: 5
        rgeKEY_SIX = 54,           // Key: 6
        rgeKEY_SEVEN = 55,         // Key: 7
        rgeKEY_EIGHT = 56,         // Key: 8
        rgeKEY_NINE = 57,          // Key: 9
        rgeKEY_SEMICOLON = 59,     // Key: ;
        rgeKEY_EQUAL = 61,         // Key: =
        rgeKEY_A = 65,             // Key: A | a
        rgeKEY_B = 66,             // Key: B | b
        rgeKEY_C = 67,             // Key: C | c
        rgeKEY_D = 68,             // Key: D | d
        rgeKEY_E = 69,             // Key: E | e
        rgeKEY_F = 70,             // Key: F | f
        rgeKEY_G = 71,             // Key: G | g
        rgeKEY_H = 72,             // Key: H | h
        rgeKEY_I = 73,             // Key: I | i
        rgeKEY_J = 74,             // Key: J | j
        rgeKEY_K = 75,             // Key: K | k
        rgeKEY_L = 76,             // Key: L | l
        rgeKEY_M = 77,             // Key: M | m
        rgeKEY_N = 78,             // Key: N | n
        rgeKEY_O = 79,             // Key: O | o
        rgeKEY_P = 80,             // Key: P | p
        rgeKEY_Q = 81,             // Key: Q | q
        rgeKEY_R = 82,             // Key: R | r
        rgeKEY_S = 83,             // Key: S | s
        rgeKEY_T = 84,             // Key: T | t
        rgeKEY_U = 85,             // Key: U | u
        rgeKEY_V = 86,             // Key: V | v
        rgeKEY_W = 87,             // Key: W | w
        rgeKEY_X = 88,             // Key: X | x
        rgeKEY_Y = 89,             // Key: Y | y
        rgeKEY_Z = 90,             // Key: Z | z
        rgeKEY_LEFT_BRACKET = 91,  // Key: [
        rgeKEY_BACKSLASH = 92,     // Key: '\'
        rgeKEY_RIGHT_BRACKET = 93, // Key: ]
        rgeKEY_GRAVE = 96,         // Key: `
        // Function keys
        rgeKEY_SPACE = 32,          // Key: Space
        rgeKEY_ESCAPE = 256,        // Key: Esc
        rgeKEY_ENTER = 257,         // Key: Enter
        rgeKEY_TAB = 258,           // Key: Tab
        rgeKEY_BACKSPACE = 259,     // Key: Backspace
        rgeKEY_INSERT = 260,        // Key: Ins
        rgeKEY_DELETE = 261,        // Key: Del
        rgeKEY_RIGHT = 262,         // Key: Cursor right
        rgeKEY_LEFT = 263,          // Key: Cursor left
        rgeKEY_DOWN = 264,          // Key: Cursor down
        rgeKEY_UP = 265,            // Key: Cursor up
        rgeKEY_PAGE_UP = 266,       // Key: Page up
        rgeKEY_PAGE_DOWN = 267,     // Key: Page down
        rgeKEY_HOME = 268,          // Key: Home
        rgeKEY_END = 269,           // Key: End
        rgeKEY_CAPS_LOCK = 280,     // Key: Caps lock
        rgeKEY_SCROLL_LOCK = 281,   // Key: Scroll down
        rgeKEY_NUM_LOCK = 282,      // Key: Num lock
        rgeKEY_PRINT_SCREEN = 283,  // Key: Print screen
        rgeKEY_PAUSE = 284,         // Key: Pause
        rgeKEY_F1 = 290,            // Key: F1
        rgeKEY_F2 = 291,            // Key: F2
        rgeKEY_F3 = 292,            // Key: F3
        rgeKEY_F4 = 293,            // Key: F4
        rgeKEY_F5 = 294,            // Key: F5
        rgeKEY_F6 = 295,            // Key: F6
        rgeKEY_F7 = 296,            // Key: F7
        rgeKEY_F8 = 297,            // Key: F8
        rgeKEY_F9 = 298,            // Key: F9
        rgeKEY_F10 = 299,           // Key: F10
        rgeKEY_F11 = 300,           // Key: F11
        rgeKEY_F12 = 301,           // Key: F12
        rgeKEY_LEFT_SHIFT = 340,    // Key: Shift left
        rgeKEY_LEFT_CONTROL = 341,  // Key: Control left
        rgeKEY_LEFT_ALT = 342,      // Key: Alt left
        rgeKEY_LEFT_SUPER = 343,    // Key: Super left
        rgeKEY_RIGHT_SHIFT = 344,   // Key: Shift right
        rgeKEY_RIGHT_CONTROL = 345, // Key: Control right
        rgeKEY_RIGHT_ALT = 346,     // Key: Alt right
        rgeKEY_RIGHT_SUPER = 347,   // Key: Super right
        rgeKEY_KB_MENU = 348,       // Key: KB menu
        // Keypad keys
        rgeKEY_KP_0 = 320,        // Key: Keypad 0
        rgeKEY_KP_1 = 321,        // Key: Keypad 1
        rgeKEY_KP_2 = 322,        // Key: Keypad 2
        rgeKEY_KP_3 = 323,        // Key: Keypad 3
        rgeKEY_KP_4 = 324,        // Key: Keypad 4
        rgeKEY_KP_5 = 325,        // Key: Keypad 5
        rgeKEY_KP_6 = 326,        // Key: Keypad 6
        rgeKEY_KP_7 = 327,        // Key: Keypad 7
        rgeKEY_KP_8 = 328,        // Key: Keypad 8
        rgeKEY_KP_9 = 329,        // Key: Keypad 9
        rgeKEY_KP_DECIMAL = 330,  // Key: Keypad .
        rgeKEY_KP_DIVIDE = 331,   // Key: Keypad /
        rgeKEY_KP_MULTIPLY = 332, // Key: Keypad *
        rgeKEY_KP_SUBTRACT = 333, // Key: Keypad -
        rgeKEY_KP_ADD = 334,      // Key: Keypad +
        rgeKEY_KP_ENTER = 335,    // Key: Keypad Enter
        rgeKEY_KP_EQUAL = 336,    // Key: Keypad =
        // Android key buttons
        rgeKEY_BACK = 4,        // Key: Android back button
        rgeKEY_MENU = 82,       // Key: Android menu button
        rgeKEY_VOLUME_UP = 24,  // Key: Android volume up button
        rgeKEY_VOLUME_DOWN = 25 // Key: Android volume down button
    } rgeKeyboardKey;

#ifdef __cplusplus
}
#endif
