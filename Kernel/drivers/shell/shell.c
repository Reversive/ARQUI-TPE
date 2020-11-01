#include "include/shell.h"



int text_size            = 1;
int _cursor_horizontal   = 0;
int _cursor_vertical     = 0;
int bg_color             = 0x00000000;
int text_color           = 0x04C0CC;
int blink                = 0;

#define SCALED_CHAR_WIDTH (text_size * CHAR_WIDTH)
#define SCALED_CHAR_HEIGHT (text_size * CHAR_HEIGHT)

void _tick() {
    if(blink) {
        paint_rectangle(_cursor_horizontal, _cursor_vertical, SCALED_CHAR_WIDTH, SCALED_CHAR_HEIGHT, text_color);
    } else {
        paint_rectangle(_cursor_horizontal, _cursor_vertical, SCALED_CHAR_WIDTH, SCALED_CHAR_HEIGHT, bg_color);
    }
    blink = !blink;
}

void _slide_cursor_backwards() {
    if(_cursor_horizontal <= 64) return;
    if(_cursor_horizontal == 0 && _cursor_vertical == 0) return;
    int new_pos = _cursor_horizontal - SCALED_CHAR_WIDTH;
    if( new_pos >= 0) {
        _cursor_horizontal = new_pos;
    } else {
        _cursor_vertical -= SCALED_CHAR_HEIGHT;
        _cursor_horizontal = WIDTH - SCALED_CHAR_WIDTH;
    }
}
void _slide_cursor_newline() {
    _cursor_horizontal = 0;
    if(_cursor_vertical + SCALED_CHAR_HEIGHT < HEIGHT) {
        _cursor_vertical += SCALED_CHAR_HEIGHT;
    } else {
        scroll(SCALED_CHAR_HEIGHT);
    }
}

void _slide_cursor_forward() {
    int new_pos = _cursor_horizontal + SCALED_CHAR_WIDTH;
    if(new_pos < WIDTH) {
        _cursor_horizontal  = new_pos;
    } else if(_cursor_vertical + SCALED_CHAR_HEIGHT < HEIGHT) {
        _cursor_vertical += SCALED_CHAR_HEIGHT;
        _cursor_horizontal = 0;
    } else {
        int sc = _cursor_vertical + SCALED_CHAR_HEIGHT - HEIGHT;
        scroll(SCALED_CHAR_HEIGHT);
        _cursor_horizontal = 0;
    }
}

void print_char(unsigned char key) {
    switch (key)
    {
    case _NEWLINE:
        paint_character(_cursor_horizontal, _cursor_vertical, ' ', text_size, bg_color, bg_color);
        _slide_cursor_newline();
        break;
    case _BACKSPACE:
        paint_character(_cursor_horizontal, _cursor_vertical, ' ', text_size, bg_color, bg_color);
        _slide_cursor_backwards();
        break;
    default:
        if(key < 0x20 || key > 0x80)
            return;
        paint_character(_cursor_horizontal, _cursor_vertical, key, text_size, text_color, bg_color);
        _slide_cursor_forward();
        break;
    }
    
}

void _enable_cursor() {
    timer_append_function(_tick, 10);
}

void _disable_cursor() {
    timer_remove_function(_tick);
}

void _set_bg_color(int color) {
    bg_color = color;
}

void _set_text_color(int color) {
    text_color = color;
}

void _set_text_size(int size) {
    text_size = size;
}

void _set_cursor_state(char state) {
    if(state == 0x0) {
        _disable_cursor();
    } else {
        _enable_cursor();
    }
}