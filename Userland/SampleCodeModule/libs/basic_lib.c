#include "../include/basic_lib.h"

size_t sys_read(unsigned int fd, char * buffer, size_t length) {
    return (size_t) _syscall(_SYSCALL_READ, fd, (uint64_t) buffer, length, 0, 0);
}

size_t sys_write(unsigned int fd, char * buffer, size_t length) {
    return (size_t) _syscall(_SYSCALL_WRITE, fd, (uint64_t) buffer, length, 0, 0);
}

unsigned int sys_time(char format) {
    return (unsigned int) _syscall(_SYSCALL_TIME, format, 0, 0, 0, 0);
}

void sys_set_bg_color(unsigned int color) {
    _syscall(_SYSCALL_SET_BG_COLOR, color, 0, 0, 0, 0);
}

void sys_set_text_color(unsigned int color) {
    _syscall(_SYSCALL_SET_TEXT_COLOR, color, 0, 0, 0, 0);
}

void sys_set_text_size(unsigned int size) {
    _syscall(_SYSCALL_SET_TEXT_SIZE, size, 0, 0, 0, 0);
}

void sys_set_cursor_status(unsigned char status) {
    _syscall(_SYSCALL_SET_CURSOR_STATE, status, 0, 0, 0, 0);
}

void sys_inforeg( char* data) {
    _syscall(_SYSCALL_INFOREG,(uint64_t)data, 0, 0, 0, 0);
}

void sys_print_mem( char* from, char* buffer) {
    _syscall(_SYSCALL_PRINT_MEM,(uint64_t) from,(uint64_t) buffer, 0, 0, 0);
}

void sys_draw_matrix(int x, int y, int color, char * matrix, int size) {
    _syscall(_SYSCALL_DRAW_MATRIX, x, y, color, (uint64_t) matrix, size);
}

void sys_draw_square(int x, int y, int size, int color) {
    _syscall(_SYSCALL_DRAW_SQUARE, x, y, size, color, 0);
}

void sys_set_cursor_pos(int x, int y) {
    _syscall(_SYSCALL_SET_CURSOR_POS, x, y, 0, 0, 0);
}

void sys_get_cursor_pos(int * x, int * y) {
    _syscall(_SYSCALL_GET_CURSOR_POS, x, y, 0, 0, 0);
}

void sys_clear_screen() {
    _syscall(_SYSCALL_CLEAR_SCREEN, 0, 0, 0, 0, 0);
}

void sys_draw_character(int x, int y, char character, int size, int color) {
    _syscall(_SYSCALL_DRAW_CHARACTER, x, y, character, size, color);
}

void sys_set_newline_scroll_state(int state) {
    _syscall(_SYSCALL_SET_NEWLINE_SCROLL_STATE, state, 0, 0, 0, 0);
}

void sys_clear_line() {
    _syscall(_SYSCALL_CLEAR_LINE, 0, 0, 0, 0, 0);
}

void sys_register_timertick_function(function f, unsigned long ticks) {
    _syscall(_SYSCALL_REGISTER_TIMERTICK_FUNCTION, f, ticks, 0, 0, 0);
}

void sys_unregister_timertick_function(function f) {
    _syscall(_SYSCALL_UNREGISTER_TIMERTICK_FUNCTION, f, 0, 0, 0, 0);
}