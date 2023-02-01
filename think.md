cow!
le plan:

so first, within fork, you have to change uvmcopy()

add mapping, change permission

so what then?

if that fails, you got to freeproc(), which involves freewalk(), which has to check whether one phy page is not referenced by no one. so you need an array recording that.

where to put that array? say char is enough. sin there aren't many processses in xv6. we need to initialize it when we first 

kfree(): for user pages, must ensure count = 0;
				 for kernel pages? does'nt care, cuz no cow there.
	
when userunmap, phy page shall 
