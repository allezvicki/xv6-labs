#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void prime(int pl[]){
	close(pl[1]);
	int p, x;
	if(read(pl[0], &p, 4) < 4) {
		close(pl[0]);
		return;
	}
	printf("prime %d\n", p);
	int pr[2];
	pipe(pr);
	int pid = fork();
	if(pid == 0) {
		prime(pr);
		exit(0);
	}
	close(pr[0]);
	while(read(pl[0], &x, 4) >= 4) {
		if(x % p != 0) {
			write(pr[1], &x, 4);		
		}
	}
	close(pl[0]);
	close(pr[1]);
	wait(&pid);
}

int main(){
	int p[2];
	pipe(p);
	int pid = fork();
	if(pid == 0){
		prime(p);
		exit(0);
	}
	close(p[0]);
	for(int i = 2; i < 36; i++) {
		write(p[1], &i, sizeof(int));
	}
	close(p[1]);
	wait(&pid);
	exit(0);
	
}
