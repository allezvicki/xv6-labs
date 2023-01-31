How to implement Alarm?

user call sigalarm with `ticks` and `handler addr`

in sys_sigalar, record some information in proc, then ret;

after / before yield()???
anyway, gotta check if it is time to do handler
if it is, we need switch from kernel to user


that is, we still go to usertrapret(), but with p->alarm->ready = 1. so ret() knows we gonna return to p->alarm->handler, rather than sepc. but!!!!! we have to save the original trapframe somewhere.

in trapret:
what regis of the original we have to save? the 32 user regis, and?
the pc. yep, these are enough.
wait, what about stack pointer?? well, not to worry.

also, should handler be time interrupted??? No, because lab instruction says it should not be reentrant, so we we should intr_off() or something.

124 line: w_sepc(p->handler)

go to userret asembly. restores the trapframe, set pc to handler.

say we returned to handler, 
then it's done 
go to syscall sigreturn.
trap go to syscall.c syscall()

the thing here is, right before we go to syscall, intr_on() is set, sooooo, we might be interrupted while doint sigreturn... but the chance is slim i guess,,, because very quick we are gonna go to usertrapret and the itr is set off.

calls sigreturn
the trapframe here is a mess.
we set alarm->ret = 1;
go to usertrapret(), 
retrieve the saved trapframe from alarm->trapframe, (we shall call it trapsnap!)
then set 



handle alarm(0,0), easy. set alarm.tick = -1.


!!!! remember to clear alarm. in freeproc();
!!!!
// for safety, somewhere you have to check handler is not kernel code and is excutable.
