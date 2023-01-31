#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
	backtrace(); // traps lab. see printf.c
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// to consider: does interrupt here bother???
// for safety, somewhere you have to check handler is not kernel code and is excutable.
uint64 sys_sigalarm(void) {
	uint ticks;
	argint(0, (int*)&ticks);
	uint64 handler;
	argaddr(1, &handler);
	struct proc* p = myproc();
	if(ticks == 0 && handler == 0) {
		p->alarm.ticks = 0;
		return 0;
	}
	if(ticks < 1) {
		return -1;
	}
	p->alarm.ticks = ticks;
	p->alarm.handler = handler;
	return 0;
	
}

uint64 sys_sigreturn(void) {
	myproc()->alarm.ret = 1;
	return 0;
}
