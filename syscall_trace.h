#ifndef __SYSCALL_TRACE_H__
#define __SYSCALL_TRACE_H__

#define NUM_SYSCALLS 1024

typedef enum
{
    TRACE_OFF,
    TRACE_ON
}syscall_trace_state_t;


typedef struct syscall_info_t
{
    int num;
    char name[32];
    int count;
}syscall_info_t;

extern syscall_info_t syscall_info[NUM_SYSCALLS];
extern syscall_trace_state_t syscalls_tracing_state;

void syscalltraceinit();
int getsyscall_idx(int syscall_num);
void print_active_syscalls();
void toggle_syscall_trace_state();
void increment_syscall_count(int syscall_num);
#endif
