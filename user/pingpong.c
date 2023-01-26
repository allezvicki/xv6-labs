#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  int p[2];
  pipe(p);
  switch (fork()) {
  case 0: {
    char rec;
    if (read(p[0], &rec, 1) <= 0) {
      fprintf(2, "child read error\n");
      exit(1);
    }
    printf("%d: received ping\n", getpid());
		if(write(p[1], &rec, 1) <= 0) {
			fprintf(2,"child write error\n");
			exit(1);
		}
    break;
  }
  default: {
		char snd;
		if (write(p[1], &snd, 1) <= 0 ) {
			fprintf(2, "parent write error\n");
			exit(1);
		}
    if (read(p[0], &snd, 1) <= 0) {
      fprintf(2, "parent read error\n");
      exit(1);
    }
		printf("%d: received pong\n", getpid());
  }
  }
  exit(0);
}
