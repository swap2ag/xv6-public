#include "types.h"
#include "defs.h"
#include "syscall.h"
#include "stdbool.h"

#include "syscall_trace.h"

syscall_info_t syscall_info[NUM_SYSCALLS] = {0};
syscall_trace_state_t syscalls_tracing_state = TRACE_OFF;

static void reset_all_syscall_count();


void syscalltraceinit()
{
    int i = 0;

    syscalls_tracing_state = TRACE_ON;
    reset_all_syscall_count();

    syscall_info[i].num = SYS_fork;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_fork", sizeof(syscall_info[i].name) - 1);

    syscall_info[i].num = SYS_exit;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_exit", sizeof(syscall_info[i].name) - 1);

    syscall_info[i].num = SYS_wait;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_wait", sizeof(syscall_info[i].name) - 1);

    syscall_info[i].num = SYS_pipe;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_pipe", sizeof(syscall_info[i].name) - 1);

    syscall_info[i].num = SYS_read;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_read", sizeof(syscall_info[i].name) - 1);

    syscall_info[i].num = SYS_kill;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_kill", sizeof(syscall_info[i].name) - 1);

    syscall_info[i].num = SYS_exec;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_exec", sizeof(syscall_info[i].name) - 1);

    syscall_info[i].num = SYS_fstat;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_fstat", sizeof(syscall_info[i].name) - 1);

    syscall_info[i].num = SYS_chdir;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_chdir", sizeof(syscall_info[i].name) - 1);

    syscall_info[i].num = SYS_dup;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_dup", sizeof(syscall_info[i].name) - 1);

    syscall_info[i].num = SYS_getpid;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_getpid", sizeof(syscall_info[i].name) - 1);

    syscall_info[i].num = SYS_sbrk;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_sbrk", sizeof(syscall_info[i].name) - 1);

    syscall_info[i].num = SYS_sleep;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_sleep", sizeof(syscall_info[i].name) - 1);

    syscall_info[i].num = SYS_uptime;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_uptime", sizeof(syscall_info[i].name) - 1);

    syscall_info[i].num = SYS_open;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_open", sizeof(syscall_info[i].name) - 1);

    syscall_info[i].num = SYS_write;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_write", sizeof(syscall_info[i].name) - 1);

    syscall_info[i].num = SYS_mknod;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_mknod", sizeof(syscall_info[i].name) - 1);

    syscall_info[i].num = SYS_unlink;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_unlink", sizeof(syscall_info[i].name) - 1);

    syscall_info[i].num = SYS_link;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_link", sizeof(syscall_info[i].name) - 1);

    syscall_info[i].num = SYS_mkdir;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_mkdir", sizeof(syscall_info[i].name) - 1);

    syscall_info[i].num = SYS_close;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_close", sizeof(syscall_info[i].name) - 1);

    syscall_info[i].num = SYS_print_count;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_print_count", sizeof(syscall_info[i].name) - 1);

    syscall_info[i].num = SYS_toggle;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_toggle", sizeof(syscall_info[i].name) - 1);

    syscall_info[i].num = SYS_add;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_add", sizeof(syscall_info[i].name) - 1);

    syscall_info[i].num = SYS_ps;
    syscall_info[i].count = 0;
    strncpy(syscall_info[i++].name, "sys_ps", sizeof(syscall_info[i].name) - 1);

}

int getsyscall_idx(int syscall_num)
{
    int idx = -1;

    for (int i = 0; i < NUM_SYSCALLS; i++)
    {
        if (syscall_info[i].num == syscall_num)
        {
            idx = i;
            break;
        }
    }
    return idx;
}

void print_active_syscalls()
{
    bool found = false;
    for (int i = 0; i < NUM_SYSCALLS; i++)
    {
        if (syscall_info[i].count > 0)
        {
            found = true;
            cprintf("%s %d\n", syscall_info[i].name, syscall_info[i].count);
        }
    }
    if (found == false)
    {
        cprintf("No syscalls executed so far\n");
    }
}

void toggle_syscall_trace_state()
{
    if (syscalls_tracing_state == TRACE_OFF)
    {
        syscalls_tracing_state = TRACE_ON;
    }
    else if (syscalls_tracing_state == TRACE_ON)
    {
        syscalls_tracing_state = TRACE_OFF;
        reset_all_syscall_count();
    }
}

static void reset_all_syscall_count()
{
    for (int i = 0; i < NUM_SYSCALLS; i++)
    {
        syscall_info[i].count = 0;
    }
}

void increment_syscall_count(int syscall_num)
{
    int idx = getsyscall_idx(syscall_num);
    if (idx != -1)
    {
        syscall_info[idx].count++; 
    }
}
