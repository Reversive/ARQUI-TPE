#ifndef THREAD_H
#define THREAD_H
#include "../../mem/include/mm.h"
#include "../../mem/include/buddy.h"
#include "../../asm/include/libasm.h"
#include "data_structures.h"

#define MAIN_THREAD 0

#ifndef EMPTY
#define EMPTY 0
#endif

#ifndef PAGE_SIZE
#define PAGE_SIZE 4096
#endif

#ifndef MIN_PAGE_AMOUNT
#define MIN_PAGE_AMOUNT 1
#endif

#ifndef UNAVAILABLE
#define UNAVAILABLE -2
#endif



thread_st *create_thread(address_t main, char **argv, size_t stack_size, thread_st **thread_list, pid_t pid);
size_t calculate_stack_size(size_t size);
size_t get_argv_count(char **argv);
void free_thread(thread_st *t);

#endif