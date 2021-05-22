#include "./include/test_prio.h"

uint64_t my_getpid(){
  return sys_getpid();
}

uint64_t my_nice(uint64_t pid, uint64_t newPrio){
  return sys_set_niceness(pid, newPrio);
}

uint64_t my_kill(uint64_t pid){
  return sys_kill_process(pid);
}

uint64_t my_block(uint64_t pid){
  return sys_block(pid);
}

uint64_t my_unblock(uint64_t pid){
  return sys_block(pid);
}

void bussy_wait(uint64_t n){
  uint64_t i;
  for (i = 0; i < n; i++);
}

int prio_endless_loop(int argc, char **argv){
  uint64_t pid = my_getpid();

  while(1){
    printf("%d ",pid);
    bussy_wait(MINOR_WAIT);
  }
  return 0;
}

#define TOTAL_PROCESSES 3

void test_prio(){
  uint64_t pids[TOTAL_PROCESSES];
  uint64_t i;

  for(i = 0; i < TOTAL_PROCESSES; i++)
    pids[i] = execv("endless_loop", prio_endless_loop, (char*[]){NULL});

  bussy_wait(WAIT);
  printf("\nCHANGING PRIORITIES...\n");

  for(i = 0; i < TOTAL_PROCESSES; i++){
    switch (i % 3){
      case 0:
        my_nice(pids[i], 0); //lowest priority 
        break;
      case 1:
        my_nice(pids[i], 2); //medium priority
        break;
      case 2:
        my_nice(pids[i], 5); //highest priority
        break;
    }
  }

  bussy_wait(WAIT);
  printf("\nBLOCKING...\n");

  for(i = 0; i < TOTAL_PROCESSES; i++)
    my_block(pids[i]);

  printf("CHANGING PRIORITIES WHILE BLOCKED...\n");
  for(i = 0; i < TOTAL_PROCESSES; i++){
    switch (i % 3){
      case 0:
        my_nice(pids[i], 1); //medium priority 
        break;
      case 1:
        my_nice(pids[i], 1); //medium priority
        break;
      case 2:
        my_nice(pids[i], 1); //medium priority
        break;
    }
  }

  printf("UNBLOCKING...\n");

  for(i = 0; i < TOTAL_PROCESSES; i++)
    my_unblock(pids[i]);

  bussy_wait(WAIT);
  printf("\nKILLING...\n");

  for(i = 0; i < TOTAL_PROCESSES; i++)
    my_kill(pids[i]);
}

int main_test_prio(int argc, char **argv) {
  test_prio();
  return 0;
}
