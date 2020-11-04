#ifndef _SYSCALLS_H
#define _SYSCALLS_H
#include <stdint.h>
#include "../../drivers/keyboard/include/kb_driver.h"
#include "../../drivers/shell/include/shell.h"
#define _STDIN 0x1
typedef uint64_t syscall(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
typedef unsigned int size_t;

enum file_descriptors {
    _FD_STD_OUT = 0,
    _FD_STD_IN  = 1,
    _FD_STD_ERR = 2
};

enum syscall_numbers {
    _SYSCALL_READ = 0,
	_SYSCALL_WRITE,
    _SYSCALL_TIME,
    _SYSCALL_SET_BG_COLOR,
    _SYSCALL_SET_TEXT_COLOR,
    _SYSCALL_SET_TEXT_SIZE,
    _SYSCALL_SET_CURSOR_STATE,
    _SYSCALL_INFOREG,
    _SYSCALL_PRINT_MEM,
    _SYSCALL_DRAW_MATRIX,
    _SYSCALL_DRAW_SQUARE,
    _SYSCALL_SET_CURSOR_POS,
    _SYSCALL_GET_CURSOR_POS,
    _SYSCALL_CLEAR_SCREEN,
    _SYSCALL_DRAW_CHARACTER,
    _SYSCALL_SET_NEWLINE_SCROLL_STATE,
    _SYSCALL_CLEAR_LINE

};

#define _SYSCALLS_LAST _SYSCALL_CLEAR_LINE
#define _SYSCALLS_SIZE (_SYSCALLS_LAST + 1)

syscall syscall_read;
syscall syscall_write;
syscall syscall_time;
syscall syscall_set_bg_color;
syscall syscall_set_text_color;
syscall syscall_set_text_size;
syscall syscall_set_cursor_state;
syscall syscall_inforeg;
syscall syscall_print_mem;
syscall syscall_draw_matrix;
syscall syscall_draw_square;
syscall syscall_set_cursor_pos;
syscall syscall_get_cursor_pos;
syscall syscall_clear_screen;
syscall syscall_draw_character;
syscall syscall_set_newline_scroll_state;
syscall syscall_clear_line;

extern syscall * syscalls_table[_SYSCALLS_SIZE];

int read(unsigned int fd, char * buffer, size_t count);
int write(unsigned int fd, char * buffer, size_t count);
void copy_mem(char* from,char* buffer);

#endif